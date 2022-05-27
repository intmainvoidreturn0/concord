#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "carray.h"
#include "threadpool.h"

#include "discord.h"
#include "discord-internal.h"

CCORDcode
discord_rest_perform(struct discord_rest *rest)
{
    CCORDcode code;

    pthread_mutex_lock(rest->g_lock);
    discord_requestor_info_read(&rest->requestor);
    code = discord_requestor_start_pending(&rest->requestor);
    pthread_mutex_unlock(rest->g_lock);

    io_poller_wakeup(CLIENT(rest, rest)->io_poller);

    return code;
}

static void
_discord_rest_manager(void *p_rest)
{
    struct discord *client = CLIENT(p_rest, rest);
    struct discord_rest *rest = p_rest;

    struct discord_timers *const timers[] = { &rest->timers };
    int64_t now, trigger;
    int poll_result;

    discord_rest_perform(rest);

    now = (int64_t)discord_timestamp_us(client);

    trigger = discord_timers_get_next_trigger(timers, 1, now, 60000000);
    poll_result = io_poller_poll(rest->io_poller, (int)(trigger / 1000));

    now = (int64_t)discord_timestamp_us(client);
    if (0 == poll_result) {
        trigger = discord_timers_get_next_trigger(timers, 1, now, 1000);
        if (trigger > 0 && trigger < 1000) cog_sleep_us((long)trigger);
    }
    discord_timers_run(client, &rest->timers);
    io_poller_perform(rest->io_poller);

    threadpool_add(rest->tpool, _discord_rest_manager, rest, 0);
}

void
discord_rest_init(struct discord_rest *rest,
                  struct logconf *conf,
                  struct ccord_szbuf_readonly *token)
{
    if (!token->size)
        logconf_branch(&rest->conf, conf, "DISCORD_WEBHOOK");
    else
        logconf_branch(&rest->conf, conf, "DISCORD_HTTP");

    rest->io_poller = io_poller_create();
    rest->g_lock = malloc(sizeof *rest->g_lock);
    ASSERT_S(!pthread_mutex_init(rest->g_lock, NULL),
             "Couldn't initialize REST manager mutex");
    rest->tpool = threadpool_create(1, 1024, 0);
    ASSERT_S(!threadpool_add(rest->tpool, &_discord_rest_manager, rest, 0),
             "Couldn't initialize REST managagement thread");

    discord_timers_init(&rest->timers);
    discord_requestor_init(&rest->requestor, &rest->conf, token);
}

void
discord_rest_cleanup(struct discord_rest *rest)
{
    /* cleanup REST managing thread and its global lock */
    threadpool_destroy(rest->tpool, threadpool_graceful);
    pthread_mutex_destroy(rest->g_lock);
    free(rest->g_lock);
    /* cleanup discovered buckets */
    discord_timers_cleanup(CLIENT(rest, rest), &rest->timers);
    /* cleanup requests */
    discord_requestor_cleanup(&rest->requestor);
    /* cleanup REST poller */
    io_poller_destroy(rest->io_poller);
}

/* template function for performing requests */
CCORDcode
discord_rest_run(struct discord_rest *rest,
                 struct discord_attributes *attr,
                 struct ccord_szbuf *body,
                 enum http_method method,
                 char endpoint_fmt[],
                 ...)
{
    char endpoint[DISCORD_ENDPT_LEN], key[DISCORD_ROUTE_LEN];
    va_list args;
    int len;

    /* have it point somewhere */
    if (!attr) {
        static struct discord_attributes blank = { 0 };
        attr = &blank;
    }
    if (!body) {
        static struct ccord_szbuf blank = { 0 };
        body = &blank;
    }

    /* build the endpoint string */
    va_start(args, endpoint_fmt);
    len = vsnprintf(endpoint, sizeof(endpoint), endpoint_fmt, args);
    ASSERT_NOT_OOB(len, sizeof(endpoint));
    va_end(args);

    /* build the bucket's key */
    va_start(args, endpoint_fmt);
    discord_ratelimiter_build_key(method, key, endpoint_fmt, args);
    va_end(args);

    return discord_request_begin(&rest->requestor, attr, body, method,
                                 endpoint, key);
}
