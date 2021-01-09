#ifndef LIBDISCORD_H_
#define LIBDISCORD_H_

/* This is the version number of the package from which this header
 *  file originates */
#define LIBDISCORD_VERSION "0.0.0-DEV"

/* The numeric version number is also available "in parts" by using
 *  these defines: */
#define LIBDISCORD_VERSION_MAJOR 0
#define LIBDISCORD_VERSION_MINOR 0
#define LIBDISCORD_VERSION_PATCH 0


//forward declaration. see discord-common.h for full definition
typedef struct discord_s discord_t;

/* CHANNEL TYPES
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-types */
enum discord_channel_types {
  GUILD_TEXT      = 0,
  DM              = 1,
  GUILD_VOICE     = 2,
  GROUP_DM        = 3,
  GUILD_CATEGORY  = 4,
  GUILD_NEWS      = 5,
  GUILD_STORE     = 6,
};

/* CHANNEL OBJECT
 * https://discord.com/developers/docs/resources/channel#channel-object-channel-structure */
typedef struct discord_channel_s {
  char *id;
  int type;
  char *guild_id;
  int position;
  //struct discord_overwrite_s **permission_overwrites;
  char *name;
  char *topic;
  _Bool nsfw;
  char *last_message_id;
  int bitrate;
  int user_limit;
  int rate_limit_per_user;
  struct discord_user_s **recipients;
  char *icon;
  char *owner_id;
  char *application_id;
  char *parent_id;
  char *last_pin_timestamp;
  struct discord_message_s **messages;
} discord_channel_t;

/* DISCORD MESSAGE OBJECT
 * https://discord.com/developers/docs/resources/channel#message-object*/
typedef struct discord_message_s {
  char *id;
  char *channel_id;
  char *guild_id;
  struct discord_user_s *author;
  //struct discord_guildmember_s *member;
  char *content;
  char *timestamp;
  char *edited_timestamp;
  _Bool tts;
  _Bool mention_everyone;
  struct discord_user_s **mentions;
  //struct discord_role_t **mention_roles;
  //struct discord_channelmention_s **mention_channels;
  //struct discord_attachment_s **attachments;
  //struct discord_embed_s **embeds;
  //strict discord_reaction_s **reactions;
  char *nonce;
  _Bool pinned;
  char *webhook_id;
  int type;
  //struct discord_messageactivity_s *activity;
  //struct discord_messageapplication_s *application;
  //struct discord_messagereference_s *message_reference;
  int flags;
  //struct discord_sticker_s **stickers;
  struct discord_message_s *referenced_message;
} discord_message_t;

/* GUILD OBJECT
 * https://discord.com/developers/docs/resources/guild#guild-object-guild-structure */
typedef struct discord_guild_s {
  char *id;
  char *name;
  char *icon;
  char *splash;
  char *discovery_splash;
  _Bool owner;
  char *owner_id;
  int permissions;
  char *permissions_new;
  char *region;
  char *afk_channel_id;
  int afk_timeout;
  _Bool embed_enabled;
  char *embed_channel_id;
  int verification_level;
  int default_message_notifications;
  int explicit_content_filter;
  //struct discord_role_t **roles;
  //struct discord_emoji_t **emojis;
  char **features;
  int mfa_level;
  char *application_id;
  _Bool widget_enabled;
  char *widget_channel_id;
  char *system_channel_id;
  int system_channel_flags;
  char *rules_channel_id;
  char *joined_at;
  _Bool large;
  _Bool unavailable;
  int member_count;
  //struct discord_voicestate_s **voice_states;
  //struct discord_member_s **members;
  struct discord_channel_s **channels;
  //struct discord_presence_s **presences;
  int max_presences;
  int mas_members;
  char *vanity_url_code;
  char *description;
  char *banner;
  int premium_tier;
  int premium_subscription_count;
  char *preferred_locale;
  char *public_updates_channel_id;
  int max_video_channel_users;
  int approximate_member_count;
  int approximate_presence_count;
} discord_guild_t;

/* USER OBJECT
 * https://discord.com/developers/docs/resources/user#user-object-user-structure */
typedef struct discord_user_s {
  char *id;
  char *username;
  char *discriminator;
  char *avatar;
  _Bool bot;
  _Bool sys;
  _Bool mfa_enabled;
  char *locale;
  _Bool verified;
  char *email;
  int flags;
  int premium_type;
  int public_flags;
  struct discord_guild_s **guilds;
} discord_user_t;

typedef void (discord_onrdy_cb)(struct discord_s *client);
typedef void (discord_onmsg_cb)(struct discord_s *client, struct discord_message_s *message);

/* discord-public.c */

void discord_global_init();
void discord_global_cleanup();

discord_t* discord_init(char token[]);
void discord_cleanup(discord_t *client);

void discord_set_on_ready(discord_t *client, discord_onrdy_cb *user_cb);
void discord_set_on_message(discord_t *client, discord_onmsg_cb *user_cb);

void discord_run(discord_t *client);

/* discord-public-guild.c */

discord_guild_t* discord_guild_init();
void discord_guild_cleanup(discord_guild_t *guild);
void discord_get_guild(discord_t *client, char guild_id[], discord_guild_t **p_guild);

/* discord-public-user.c */

discord_user_t* discord_user_init();
void discord_user_cleanup(discord_user_t *user);
void discord_get_user(discord_t *client, char user_id[], discord_user_t **p_user);
void discord_get_client_user(discord_t *client, discord_user_t **p_user);

/* discord-public-message.c */

discord_message_t* discord_message_init();
void discord_message_cleanup(discord_message_t *message);
void discord_send_message(discord_t *client, char channel_id[], char content[]);

#endif
