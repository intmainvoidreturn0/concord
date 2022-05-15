#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include "carray.h"

#include "discord.h"
#include "discord-internal.h"

static void
setopt_cb(struct ua_conn *conn, void *p_token)
{
    struct ccord_szbuf *token = p_token;
    char auth[128];
    int len;

    len = snprintf(auth, sizeof(auth), "Bot %.*s", (int)token->size,
                   token->start);
    ASSERT_NOT_OOB(len, sizeof(auth));

    ua_conn_add_header(conn, "Authorization", auth);

#ifdef CCORD_DEBUG_ADAPTER
    curl_easy_setopt(ua_conn_get_easy_handle(conn), CURLOPT_VERBOSE, 1L);
#endif
}

void
discord_adapter_init(struct discord_adapter *adapter,
                     struct logconf *conf,
                     struct ccord_szbuf_readonly *token)
{
    struct ua_attr attr = { 0 };

    attr.conf = conf;
    adapter->ua = ua_init(&attr);
    ua_set_url(adapter->ua, DISCORD_API_BASE_URL);

    if (!token->size) {
        /* no token means a webhook-only client */
        logconf_branch(&adapter->conf, conf, "DISCORD_WEBHOOK");
    }
    else {
        /* bot client */
        logconf_branch(&adapter->conf, conf, "DISCORD_HTTP");
        ua_set_opt(adapter->ua, token, &setopt_cb);
    }

    discord_async_init(&adapter->async, &adapter->conf);
    adapter->ratelimiter = discord_ratelimiter_init(&adapter->conf);

    adapter->retry_limit = 3; /* FIXME: shouldn't be a hard limit */
}

void
discord_adapter_cleanup(struct discord_adapter *adapter)
{
    /* cleanup User-Agent handle */
    ua_cleanup(adapter->ua);
    /* move pending requests to idle_contexts */
    discord_adapter_stop_buckets(adapter);
    /* cleanup idle requests queue */
    discord_async_cleanup(&adapter->async);
    /* cleanup discovered buckets */
    discord_ratelimiter_cleanup(adapter->ratelimiter);
}

static CCORDcode _discord_adapter_run_sync(struct discord_adapter *adapter,
                                           struct discord_request *req,
                                           struct ccord_szbuf *body,
                                           enum http_method method,
                                           char endpoint[DISCORD_ENDPT_LEN],
                                           char key[DISCORD_ROUTE_LEN]);

static CCORDcode _discord_adapter_run_async(struct discord_adapter *adapter,
                                            struct discord_request *req,
                                            struct ccord_szbuf *body,
                                            enum http_method method,
                                            char endpoint[DISCORD_ENDPT_LEN],
                                            char key[DISCORD_ROUTE_LEN]);

/* template function for performing requests */
CCORDcode
discord_adapter_run(struct discord_adapter *adapter,
                    struct discord_request *req,
                    struct ccord_szbuf *body,
                    enum http_method method,
                    char endpoint_fmt[],
                    ...)
{
    char endpoint[DISCORD_ENDPT_LEN];
    char key[DISCORD_ROUTE_LEN];
    va_list args;
    int len;

    /* have it point somewhere */
    if (!req) {
        static struct discord_request blank = { 0 };
        req = &blank;
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

    if (req->dispatch.sync) { /* perform blocking request */
        if (req->dispatch.has_type && req->dispatch.sync != DISCORD_SYNC_FLAG)
            req->response.data = req->dispatch.sync;

        return _discord_adapter_run_sync(adapter, req, body, method, endpoint,
                                         key);
    }

    /* enqueue asynchronous request */
    return _discord_adapter_run_async(adapter, req, body, method, endpoint,
                                      key);
}

/* return true if there should be a retry attempt */
static bool
_discord_adapter_get_info(struct discord_adapter *adapter,
                          struct ua_info *info,
                          int64_t *wait_ms)
{
    if (info->code != CCORD_HTTP_CODE) {
        /* CCORD_OK or internal error */
        return false;
    }

    switch (info->httpcode) {
    case HTTP_FORBIDDEN:
    case HTTP_NOT_FOUND:
    case HTTP_BAD_REQUEST:
        info->code = CCORD_DISCORD_JSON_CODE;
        return false;
    case HTTP_UNAUTHORIZED:
        logconf_fatal(
            &adapter->conf,
            "UNAUTHORIZED: Please provide a valid authentication token");
        info->code = CCORD_DISCORD_BAD_AUTH;
        return false;
    case HTTP_METHOD_NOT_ALLOWED:
        logconf_fatal(&adapter->conf,
                      "METHOD_NOT_ALLOWED: The server couldn't recognize the "
                      "received HTTP method");
        return false;
    case HTTP_TOO_MANY_REQUESTS: {
        struct ua_szbuf_readonly body = ua_info_get_body(info);
        struct jsmnftok message = { 0 };
        double retry_after = 1.0;
        bool is_global = false;
        jsmn_parser parser;
        jsmntok_t tokens[16];

        jsmn_init(&parser);
        if (0 < jsmn_parse(&parser, body.start, body.size, tokens,
                           sizeof(tokens) / sizeof *tokens))
        {
            jsmnf_loader loader;
            jsmnf_pair pairs[16];

            jsmnf_init(&loader);
            if (0 < jsmnf_load(&loader, body.start, tokens, parser.toknext,
                               pairs, sizeof(pairs) / sizeof *pairs))
            {
                jsmnf_pair *f;

                if ((f = jsmnf_find(pairs, body.start, "global", 6)))
                    is_global = ('t' == body.start[f->v.pos]);
                if ((f = jsmnf_find(pairs, body.start, "message", 7)))
                    message = f->v;
                if ((f = jsmnf_find(pairs, body.start, "retry_after", 11)))
                    retry_after = strtod(body.start + f->v.pos, NULL);
            }
        }

        *wait_ms = (int64_t)(1000 * retry_after);
        if (*wait_ms < 0) *wait_ms = 0;

        logconf_warn(&adapter->conf,
                     "429 %s RATELIMITING (wait: %" PRId64 " ms) : %.*s",
                     is_global ? "GLOBAL" : "", *wait_ms, message.len,
                     body.start + message.pos);

        return true;
    }
    default:
        if (info->httpcode >= 500) { /* Server Error */
            return true;
        }
        return false;
    }
}

/*
 * data is a `void *[2]`, where the first element is a
 * `struct discord_attachment` and the second element is a
 * `struct ccord_szbuf` containing the request body */
static void
_discord_adapter_request_to_multipart(curl_mime *mime, void *data)
{
    struct discord_attachments *atchs = ((void **)data)[0];
    struct ccord_szbuf *body = ((void **)data)[1];
    curl_mimepart *part;
    char name[64];

    /* json part */
    if (body->start && body->size) {
        part = curl_mime_addpart(mime);
        curl_mime_data(part, body->start, body->size);
        curl_mime_type(part, "application/json");
        curl_mime_name(part, "payload_json");
    }

    /* attachment part */
    for (int i = 0; i < atchs->size; ++i) {
        int len = snprintf(name, sizeof(name), "files[%d]", i);
        ASSERT_NOT_OOB(len, sizeof(name));

        if (atchs->array[i].content) {
            part = curl_mime_addpart(mime);
            curl_mime_data(part, atchs->array[i].content,
                           atchs->array[i].size ? atchs->array[i].size
                                                : CURL_ZERO_TERMINATED);
            curl_mime_filename(part, !atchs->array[i].filename
                                         ? "a.out"
                                         : atchs->array[i].filename);
            curl_mime_type(part, !atchs->array[i].content_type
                                     ? "application/octet-stream"
                                     : atchs->array[i].content_type);
            curl_mime_name(part, name);
        }
        else if (atchs->array[i].filename) {
            CURLcode code;

            /* fetch local file by the filename */
            part = curl_mime_addpart(mime);
            code = curl_mime_filedata(part, atchs->array[i].filename);
            if (code != CURLE_OK) {
                char errbuf[256];
                snprintf(errbuf, sizeof(errbuf), "%s (file: %s)",
                         curl_easy_strerror(code), atchs->array[i].filename);
                perror(errbuf);
            }
            curl_mime_type(part, !atchs->array[i].content_type
                                     ? "application/octet-stream"
                                     : atchs->array[i].content_type);
            curl_mime_name(part, name);
        }
    }
}

/* SYNCHRONOUS REQUEST LOGIC */

/* perform a blocking request */
static CCORDcode
_discord_adapter_run_sync(struct discord_adapter *adapter,
                          struct discord_request *req,
                          struct ccord_szbuf *body,
                          enum http_method method,
                          char endpoint[DISCORD_ENDPT_LEN],
                          char key[DISCORD_ROUTE_LEN])
{
    void *data[2] = { &req->attachments, body };
    struct discord_bucket *b;
    struct ua_conn *conn;
    int retry_attempt = 0;
    bool retry;
    CCORDcode code;

    b = discord_bucket_get(adapter->ratelimiter, key);
    conn = ua_conn_start(adapter->ua);

    if (HTTP_MIMEPOST == method) {
        ua_conn_add_header(conn, "Content-Type", "multipart/form-data");
        ua_conn_set_mime(conn, data, &_discord_adapter_request_to_multipart);
    }
    else {
        ua_conn_add_header(conn, "Content-Type", "application/json");
    }

    ua_conn_setup(conn, &(struct ua_conn_attr){
                            .method = method,
                            .body = body->start,
                            .body_size = body->size,
                            .endpoint = endpoint,
                            .base_url = NULL,
                        });

    pthread_mutex_lock(&b->lock);
    do {
        discord_bucket_try_sleep(adapter->ratelimiter, b);

        /* perform blocking request, and check results */
        switch (code = ua_conn_easy_perform(conn)) {
        case CCORD_OK: {
            struct discord *client = CLIENT(adapter, adapter);
            struct ua_szbuf_readonly resp;
            struct ua_info info = { 0 };
            int64_t wait_ms = 0;

            ua_info_extract(conn, &info);
            retry = _discord_adapter_get_info(adapter, &info, &wait_ms);

            resp = ua_info_get_body(&info);
            if (info.code != CCORD_OK) {
                logconf_error(&client->conf, "%.*s", (int)resp.size,
                              resp.start);
            }
            else if (req->response.data) {
                /* initialize ret */
                if (req->response.init) req->response.init(req->response.data);

                /* populate ret */
                if (req->response.from_json)
                    req->response.from_json(resp.start, resp.size,
                                            req->response.data);
            }

            code = info.code;

            /* in the off-chance of having consecutive blocking calls, update
             *        timestamp used for ratelimiting
             * TODO: redundant for REST-only clients
             * TODO: create discord_timestamp_update() */
            ws_timestamp_update(client->gw.ws);

            discord_ratelimiter_build(adapter->ratelimiter, b, key, &info);
            cog_sleep_ms(wait_ms);

            ua_info_cleanup(&info);
        } break;
        case CCORD_CURLE_INTERNAL:
            logconf_error(&adapter->conf,
                          "Curl internal error, will retry again");
            retry = true;
            break;
        default:
            logconf_error(&adapter->conf, "CCORD code: %d", code);
            retry = false;
            break;
        }

        ua_conn_reset(conn);

    } while (retry && retry_attempt++ < adapter->retry_limit);
    pthread_mutex_unlock(&b->lock);

    /* reset conn and mark it as free to use */
    ua_conn_stop(conn);

    return code;
}

/* ASYNCHRONOUS REQUEST LOGIC */

/* enqueue a request to be executed asynchronously */
static CCORDcode
_discord_adapter_run_async(struct discord_adapter *adapter,
                           struct discord_request *req,
                           struct ccord_szbuf *body,
                           enum http_method method,
                           char endpoint[DISCORD_ENDPT_LEN],
                           char key[DISCORD_ROUTE_LEN])
{
    struct discord_context *cxt = discord_async_start_context(
        &adapter->async, req, body, method, endpoint, key);

    discord_context_bucket_insert(cxt, cxt->b, req->dispatch.high_p);

    /* FIXME: redundant return value (constant) */
    return CCORD_OK;
}

static void
_discord_context_to_multipart(curl_mime *mime, void *p_cxt)
{
    struct discord_context *cxt = p_cxt;
    void *data[2] = { &cxt->attachments, &(struct ccord_szbuf){
                                             cxt->body.start,
                                             cxt->body.size,
                                         } };

    _discord_adapter_request_to_multipart(mime, data);
}

/* add a request to libcurl's multi handle */
static CCORDcode
_discord_adapter_add_request(struct discord_adapter *adapter,
                             struct discord_bucket *b)
{
    struct discord_context *cxt = discord_context_bucket_remove(b);
    struct ua_conn *conn = ua_conn_start(adapter->ua);

    if (HTTP_MIMEPOST == cxt->method) {
        ua_conn_add_header(conn, "Content-Type", "multipart/form-data");
        ua_conn_set_mime(conn, cxt, &_discord_context_to_multipart);
    }
    else {
        ua_conn_add_header(conn, "Content-Type", "application/json");
    }

    ua_conn_setup(conn, &(struct ua_conn_attr){
                            .method = cxt->method,
                            .body = cxt->body.start,
                            .body_size = cxt->body.size,
                            .endpoint = cxt->endpoint,
                            .base_url = NULL,
                        });

    return discord_async_add_request(&adapter->async, cxt, conn);
}

static void
_discord_adapter_try_add_request(struct discord_adapter *adapter,
                                 struct discord_bucket *b)
{
    /* skip if bucket is busy performing */
    if (b->busy) return;

    if (!b->remaining)
        discord_bucket_try_timeout(adapter, b);
    else if (!QUEUE_EMPTY(&b->pending_queue))
        _discord_adapter_add_request(adapter, b);
}

static CCORDcode
_discord_adapter_check_pending(struct discord_adapter *adapter)
{
    discord_ratelimiter_foreach_bucket(adapter->ratelimiter, adapter,
                                       &_discord_adapter_try_add_request);
    /* FIXME: redundant return value (constant) */
    return CCORD_OK;
}

static CCORDcode
_discord_adapter_check_action(struct discord_adapter *adapter,
                              struct CURLMsg *msg)
{
    struct discord *client = CLIENT(adapter, adapter);
    struct discord_context *cxt;
    int64_t wait_ms = 0LL;
    CCORDcode code;
    bool retry;

    curl_easy_getinfo(msg->easy_handle, CURLINFO_PRIVATE, &cxt);

    switch (msg->data.result) {
    case CURLE_OK: {
        struct ua_info info = { 0 };
        struct ua_szbuf_readonly body;

        ua_info_extract(cxt->conn, &info);
        retry = _discord_adapter_get_info(adapter, &info, &wait_ms);

        body = ua_info_get_body(&info);
        if (info.code != CCORD_OK) {
            logconf_error(&client->conf, "%.*s", (int)body.size, body.start);

            if (cxt->dispatch.fail)
                cxt->dispatch.fail(client, info.code, cxt->dispatch.data);
        }
        else if (cxt->dispatch.done.typed) {
            void *ret = calloc(1, cxt->response.size);

            /* initialize ret */
            if (cxt->response.init) cxt->response.init(ret);

            /* populate ret */
            if (cxt->response.from_json)
                cxt->response.from_json(body.start, body.size, ret);

            if (cxt->dispatch.has_type)
                cxt->dispatch.done.typed(client, cxt->dispatch.data, ret);
            else
                cxt->dispatch.done.typeless(client, cxt->dispatch.data);

            /* cleanup ret */
            if (cxt->response.cleanup) cxt->response.cleanup(ret);
            free(ret);
        }

        code = info.code;

        discord_ratelimiter_build(adapter->ratelimiter, cxt->b, cxt->key,
                                  &info);
        ua_info_cleanup(&info);
    } break;
    case CURLE_READ_ERROR:
        logconf_warn(&adapter->conf, "Read error, will retry again");
        retry = true;

        code = CCORD_CURLE_INTERNAL;

        break;
    default:
        logconf_error(&adapter->conf, "(CURLE code: %d)", msg->data.result);
        retry = false;

        code = CCORD_CURLE_INTERNAL;

        if (cxt->dispatch.fail)
            cxt->dispatch.fail(client, code, cxt->dispatch.data);

        break;
    }

    /* enqueue request for retry or recycle */
    cxt->b->busy = NULL;
    if (!retry || !discord_async_retry_context(&adapter->async, cxt, wait_ms))
        discord_async_recycle_context(&adapter->async, cxt);

    return code;
}

CCORDcode
discord_adapter_async_perform(struct discord_adapter *adapter)
{
    CURLMcode mcode;
    CCORDcode code;
    int alive = 0;

    if (CCORD_OK != (code = _discord_adapter_check_pending(adapter)))
        return code;

    if (CURLM_OK
        != (mcode = curl_multi_socket_all(adapter->async.mhandle, &alive)))
        return CCORD_CURLM_INTERNAL;

    /* ask for any messages/informationals from the individual transfers */
    while (1) {
        int msgq = 0;
        struct CURLMsg *msg =
            curl_multi_info_read(adapter->async.mhandle, &msgq);

        if (!msg) break;
        if (CURLMSG_DONE != msg->msg) continue;

        /* check for request action */
        _discord_adapter_check_action(adapter, msg);
    }

    return CCORD_OK;
}

static void
_discord_adapter_stop_bucket(struct discord_adapter *adapter,
                             struct discord_bucket *b)
{
    /* cancel busy transfer */
    if (b->busy && b->busy != DISCORD_BUCKET_TIMEOUT) {
        struct discord_context *cxt = b->busy;

        b->busy = NULL;
        discord_async_recycle_context(&adapter->async, cxt);
    }

    /* cancel pending tranfers */
    QUEUE_ADD(adapter->async.idle_contexts, &b->pending_queue);
    QUEUE_INIT(&b->pending_queue);
}

void
discord_adapter_stop_buckets(struct discord_adapter *adapter)
{
    discord_ratelimiter_foreach_bucket(adapter->ratelimiter, adapter,
                                       &_discord_adapter_stop_bucket);
}
