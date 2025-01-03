# Discord API Roadmap

This document outlines the Discord API currently supported by Concord.

## Reference

### Authentication

- [x] [Bot Token Authentication](https://discord.com/developers/docs/reference#authentication-example-bot-token-authorization-header)
- [ ] [Bearer Token Authentication](https://discord.com/developers/docs/reference#authentication-example-bearer-token-authorization-header)

## Interactions

### Application Commands

- [x] [Application Command Structure](https://discord.com/developers/docs/interactions/application-commands#application-command-object)
- [x] [Application Command Types](https://discord.com/developers/docs/interactions/application-commands#application-command-types)
- [x] [Application Command Option](https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-structure)
- [x] [Application Command Option Type](https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-type)
- [x] [Application Command Option Choice](https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-option-choice)
- [x] [Application Command Interaction Data Option](https://discord.com/developers/docs/interactions/application-commands#application-command-object-application-command-interaction-data-option-structure)
- [x] [Application Command Permissions Structure](https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object)
- [x] [Application Command Permission Type](https://discord.com/developers/docs/interactions/application-commands#application-command-permissions-object-application-command-permission-type)
- [ ] [Autocomplete](https://discord.com/developers/docs/interactions/application-commands#autocomplete)
- [ ] [Localization](https://discord.com/developers/docs/interactions/application-commands#localization)
- [x] [Get Global Application Commands](https://discord.com/developers/docs/interactions/application-commands#get-global-application-commands)
- [x] [Create Global Application Command](https://discord.com/developers/docs/interactions/application-commands#create-global-application-command)
- [x] [Get Global Application Command](https://discord.com/developers/docs/interactions/application-commands#get-global-application-command)
- [x] [Edit Global Application Command](https://discord.com/developers/docs/interactions/application-commands#edit-global-application-command)
- [x] [Delete Global Application Command](https://discord.com/developers/docs/interactions/application-commands#delete-global-application-command)
- [x] [Bulk Overwrite Global Application Commands](https://discord.com/developers/docs/interactions/application-commands#bulk-overwrite-global-application-commands)
- [x] [Get Guild Application Commands](https://discord.com/developers/docs/interactions/application-commands#get-guild-application-commands)
- [x] [Create Guild Application Command](https://discord.com/developers/docs/interactions/application-commands#create-guild-application-command)
- [x] [Get Guild Application Command](https://discord.com/developers/docs/interactions/application-commands#get-guild-application-command)
- [x] [Edit Guild Application Command](https://discord.com/developers/docs/interactions/application-commands#edit-guild-application-command)
- [x] [Delete Guild Application Command](https://discord.com/developers/docs/interactions/application-commands#delete-guild-application-command)
- [x] [Bulk Overwrite Guild Application Commands](https://discord.com/developers/docs/interactions/application-commands#bulk-overwrite-guild-application-commands)
- [x] [Get Guild Application Command Permissions](https://discord.com/developers/docs/interactions/application-commands#get-guild-application-command-permissions)
- [x] [Get Application Command Permissions](https://discord.com/developers/docs/interactions/application-commands#get-application-command-permissions)
- [x] [Edit Application Command Permissions](https://discord.com/developers/docs/interactions/application-commands#edit-application-command-permissions)
- [x] [Batch Edit Application Command Permissions](https://discord.com/developers/docs/interactions/application-commands#batch-edit-application-command-permissions)

### Message Components

- [x] [Component Structure](https://discord.com/developers/docs/interactions/message-components#component-object-component-structure)
- [x] [Component Types](https://discord.com/developers/docs/interactions/message-components#component-object-component-types)
- [x] [Button Structure](https://discord.com/developers/docs/interactions/message-components#button-object-button-structure)
- [x] [Button Styles](https://discord.com/developers/docs/interactions/message-components#button-object-button-styles)
- [x] [Select Menu Structure](https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-menu-structure)
- [x] [Select Option Structure](https://discord.com/developers/docs/interactions/message-components#select-menu-object-select-option-structure)

### Receiving and Responding

- [x] [Interaction Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-structure)
- [x] [Interaction Type](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-type)
- [x] [Interaction Data Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-interaction-data-structure)
- [x] [Resolved Data Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-object-resolved-data-structure)
- [x] [Message Interaction Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#message-interaction-object-message-interaction-structure)
- [x] [Interaction Response Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-response-structure)
- [x] [Interaction Callback Type](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-type)
- [x] [Interaction Callback Data Structure](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-structure)
- [x] [Interaction Callback Data Flags](https://discord.com/developers/docs/interactions/receiving-and-responding#interaction-response-object-interaction-callback-data-flags)
- [x] [Create Interaction Response](https://discord.com/developers/docs/interactions/receiving-and-responding#create-interaction-response)
- [x] [Get Original Interaction Response](https://discord.com/developers/docs/interactions/receiving-and-responding#get-original-interaction-response)
- [x] [Edit Original Interaction Response](https://discord.com/developers/docs/interactions/receiving-and-responding#edit-original-interaction-response)
- [x] [Delete Original Interaction Response](https://discord.com/developers/docs/interactions/receiving-and-responding#delete-original-interaction-response)
- [x] [Create Followup Message](https://discord.com/developers/docs/interactions/receiving-and-responding#create-followup-message)
- [x] [Get Followup Message](https://discord.com/developers/docs/interactions/receiving-and-responding#get-followup-message)
- [x] [Edit Followup Message](https://discord.com/developers/docs/interactions/receiving-and-responding#edit-followup-message)
- [x] [Delete Followup Message](https://discord.com/developers/docs/interactions/receiving-and-responding#delete-followup-message)

## Resources

### Application

- [x] [Application Structure](https://discord.com/developers/docs/resources/application#application-object-application-structure)
- [x] [Application Flags](https://discord.com/developers/docs/resources/application#application-object-application-flags)
- [x] [Install Params Structure](https://discord.com/developers/docs/resources/application#install-params-object-install-params-structure)

### Audit Log

- [x] [Audit Log Structure](https://discord.com/developers/docs/resources/audit-log#audit-log-object)
- [x] [Audit Log Entry Structure](https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object)
- [x] [Audit Log Events](https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-audit-log-events)
- [x] [Optional Audit Entry Info](https://discord.com/developers/docs/resources/audit-log#audit-log-entry-object-optional-audit-entry-info)
- [x] [Audit Log Change Structure](https://discord.com/developers/docs/resources/audit-log#audit-log-change-object)
- [x] [Audit Log Change Key](https://discord.com/developers/docs/resources/audit-log#audit-log-change-object-audit-log-change-key)
- [x] [Get Guild Audit Log](https://discord.com/developers/docs/resources/audit-log#get-guild-audit-log)

### Auto Moderation

- [x] [Auto Moderation Rule Structure](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-rule-object-auto-moderation-rule-structure)
- [x] [Trigger Types](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-rule-object-trigger-types)
- [x] [Trigger Metadata Structure](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-rule-object-trigger-metadata)
- [x] [Keyword Preset Types](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-rule-object-keyword-preset-types)
- [x] [Event Types](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-rule-object-event-types)
- [x] [Auto Moderation Action Structure](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-action-object-auto-moderation-action-structure)
- [x] [Action Types](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-action-object-action-types)
- [x] [Action Metadata Structure](https://discord.com/developers/docs/resources/auto-moderation#auto-moderation-action-object-action-metadata)
- [x] [List Auto Moderation Rules for Guild](https://discord.com/developers/docs/resources/auto-moderation#list-auto-moderation-rules-for-guild)
- [x] [Get Auto Moderation Rule](https://discord.com/developers/docs/resources/auto-moderation#get-auto-moderation-rule)
- [x] [Create Auto Moderation Rule](https://discord.com/developers/docs/resources/auto-moderation#create-auto-moderation-rule)
- [x] [Modify Auto Moderation Rule](https://discord.com/developers/docs/resources/auto-moderation#modify-auto-moderation-rule)
- [x] [Delete Auto Moderation Rule](https://discord.com/developers/docs/resources/auto-moderation#delete-auto-moderation-rule)

### Channels

- [x] [Channel Structure](https://discord.com/developers/docs/resources/channel#channel-object)
- [x] [Channel Types](https://discord.com/developers/docs/resources/channel#channel-object-channel-types)
- [x] [Message Structure](https://discord.com/developers/docs/resources/channel#message-object)
- [x] [Message Types](https://discord.com/developers/docs/resources/channel#message-object-message-types)
- [x] [Message Activity Structure](https://discord.com/developers/docs/resources/channel#message-object-message-activity-structure)
- [x] [Message Application Structure](https://discord.com/developers/docs/resources/channel#message-object-message-application-structure)
- [x] [Message Reference Structure](https://discord.com/developers/docs/resources/channel#message-object-message-reference-structure)
- [x] [Message Activity Types](https://discord.com/developers/docs/resources/channel#message-object-message-activity-types)
- [x] [Message Flags](https://discord.com/developers/docs/resources/channel#message-object-message-flags)
- [x] [Message Sticker Structure](https://discord.com/developers/docs/resources/channel#message-object-message-sticker-structure)
- [x] [Message Sticker Format Types](https://discord.com/developers/docs/resources/channel#message-object-message-sticker-format-types)
- [x] [Followed Channel Structure](https://discord.com/developers/docs/resources/channel#followed-channel-object)
- [x] [Reaction Structure](https://discord.com/developers/docs/resources/channel#reaction-object)
- [x] [Overwrite Structure](https://discord.com/developers/docs/resources/channel#overwrite-object)
- [x] [Embed Structure](https://discord.com/developers/docs/resources/channel#embed-object)
- [x] [Embed Types](https://discord.com/developers/docs/resources/channel#embed-object-embed-types)
- [x] [Embed Thumbnail Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-thumbnail-structure)
- [x] [Embed Video Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-video-structure)
- [x] [Embed Image Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-image-structure)
- [x] [Embed Provider Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-provider-structure)
- [x] [Embed Author Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-author-structure)
- [x] [Embed Footer Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-footer-structure)
- [x] [Embed Field Structure](https://discord.com/developers/docs/resources/channel#embed-object-embed-field-structure)
- [x] [Attachment Structure](https://discord.com/developers/docs/resources/channel#attachment-object)
- [x] [Channel Mention Structure](https://discord.com/developers/docs/resources/channel#channel-mention-object)
- [x] [Allowed Mentions Structure](https://discord.com/developers/docs/resources/channel#allowed-mentions-object)
- [x] [Embed Limits](https://discord.com/developers/docs/resources/channel#embed-limits)
- [x] [Get Channel](https://discord.com/developers/docs/resources/channel#get-channel)
- [x] [Modify Channel](https://discord.com/developers/docs/resources/channel#modify-channel)
- [x] [Delete/Close Channel](https://discord.com/developers/docs/resources/channel#deleteclose-channel)
- [x] [Get Channel Messages](https://discord.com/developers/docs/resources/channel#get-channel-messages)
- [x] [Get Channel Message](https://discord.com/developers/docs/resources/channel#get-channel-message)
- [x] [Create Message](https://discord.com/developers/docs/resources/channel#create-message)
- [x] [Crosspost Message](https://discord.com/developers/docs/resources/channel#crosspost-message)
- [x] [Create Reaction](https://discord.com/developers/docs/resources/channel#create-reaction)
- [x] [Delete Own Reaction](https://discord.com/developers/docs/resources/channel#delete-own-reaction)
- [x] [Delete User Reaction](https://discord.com/developers/docs/resources/channel#delete-user-reaction)
- [x] [Get Reactions](https://discord.com/developers/docs/resources/channel#get-reactions)
- [x] [Delete All Reactions](https://discord.com/developers/docs/resources/channel#delete-all-reactions)
- [x] [Delete All Reactions for Emoji](https://discord.com/developers/docs/resources/channel#delete-all-reactions-for-emoji)
- [x] [Edit Message](https://discord.com/developers/docs/resources/channel#edit-message)
- [x] [Delete Message](https://discord.com/developers/docs/resources/channel#delete-message)
- [x] [Bulk Delete Messages](https://discord.com/developers/docs/resources/channel#bulk-delete-messages)
- [x] [Edit Channel Permissions](https://discord.com/developers/docs/resources/channel#edit-channel-permissions)
- [x] [Get Channel Invites](https://discord.com/developers/docs/resources/channel#get-channel-invites)
- [x] [Create Channel Invite](https://discord.com/developers/docs/resources/channel#create-channel-invite)
- [x] [Delete Channel Permission](https://discord.com/developers/docs/resources/channel#delete-channel-permission)
- [x] [Follow News Channels](https://discord.com/developers/docs/resources/channel#follow-news-channel)
- [x] [Trigger Typing Indicator](https://discord.com/developers/docs/resources/channel#trigger-typing-indicator)
- [x] [Get Pinned Messages](https://discord.com/developers/docs/resources/channel#get-pinned-messages)
- [x] [Add Pinned Channel Message](https://discord.com/developers/docs/resources/channel#add-pinned-channel-message)
- [x] [Delete Pinned Channel Message](https://discord.com/developers/docs/resources/channel#delete-pinned-channel-message)
- [x] [Group DM Add Recipient](https://discord.com/developers/docs/resources/channel#group-dm-add-recipient)
- [x] [Group DM Remove Recipient](https://discord.com/developers/docs/resources/channel#group-dm-remove-recipient)
- [x] [Start Thread with Message](https://discord.com/developers/docs/resources/channel#start-thread-with-message)
- [x] [Start Thread without Message](https://discord.com/developers/docs/resources/channel#start-thread-without-message)
- [x] [Join Thread](https://discord.com/developers/docs/resources/channel#join-thread)
- [x] [Add Thread Member](https://discord.com/developers/docs/resources/channel#add-thread-member)
- [x] [Leave Thread](https://discord.com/developers/docs/resources/channel#leave-thread)
- [x] [Remove Thread Member](https://discord.com/developers/docs/resources/channel#remove-thread-member)
- [x] [List Thread Members](https://discord.com/developers/docs/resources/channel#list-thread-members)
- [x] [List Active Threads](https://discord.com/developers/docs/resources/channel#list-active-threads)
- [x] [List Public Archived Threads](https://discord.com/developers/docs/resources/channel#list-public-archived-threads)
- [x] [List Private Archived Threads](https://discord.com/developers/docs/resources/channel#list-private-archived-threads)
- [x] [List Joined Private Arhived Threads](https://discord.com/developers/docs/resources/channel#list-joined-private-archived-threads)

### Emoji

- [x] [Emoji Structure](https://discord.com/developers/docs/resources/emoji#emoji-object)
- [x] [List Guild Emojis](https://discord.com/developers/docs/resources/emoji#list-guild-emojis)
- [x] [Get Guild Emoji](https://discord.com/developers/docs/resources/emoji#get-guild-emoji)
- [x] [Create Guild Emoji](https://discord.com/developers/docs/resources/emoji#create-guild-emoji)
- [x] [Modify Guild Emoji](https://discord.com/developers/docs/resources/emoji#modify-guild-emoji)
- [x] [Delete Guild Emoji](https://discord.com/developers/docs/resources/emoji#delete-guild-emoji)

### Guild

- [x] [Guild Structure](https://discord.com/developers/docs/resources/guild#guild-object)
- [x] [Default Message Notification Level](https://discord.com/developers/docs/resources/guild#guild-object-default-message-notification-level)
- [x] [Explicit Content Filter Level](https://discord.com/developers/docs/resources/guild#guild-object-explicit-content-filter-level)
- [x] [MFA Level](https://discord.com/developers/docs/resources/guild#guild-object-mfa-level)
- [x] [Verification Level](https://discord.com/developers/docs/resources/guild#guild-object-verification-level)
- [x] [Premium Tier](https://discord.com/developers/docs/resources/guild#guild-object-premium-tier)
- [x] [System Channel Flags](https://discord.com/developers/docs/resources/guild#guild-object-system-channel-flags)
- [x] [Guild Features](https://discord.com/developers/docs/resources/guild#guild-object-guild-features)
- [x] [Unavailable Guild Structure](https://discord.com/developers/docs/resources/guild#unavailable-guild-object)
- [x] [Guild Preview Structure](https://discord.com/developers/docs/resources/guild#guild-preview-object)
- [x] [Guild Widget Structure](https://discord.com/developers/docs/resources/guild#guild-widget-object)
- [x] [Guild Member Structure](https://discord.com/developers/docs/resources/guild#guild-member-object)
- [x] [Integration Structure](https://discord.com/developers/docs/resources/guild#integration-object)
- [x] [Integration Expire Behaviors](https://discord.com/developers/docs/resources/guild#integration-object-integration-expire-behaviors)
- [x] [Integration Account Structure](https://discord.com/developers/docs/resources/guild#integration-account-object)
- [x] [Integration Application Structure](https://discord.com/developers/docs/resources/guild#integration-application-object)
- [x] [Ban Structure](https://discord.com/developers/docs/resources/guild#ban-object)
- [x] [Welcome Screen Structure](https://discord.com/developers/docs/resources/guild#welcome-screen-object)
- [x] [Create Guild](https://discord.com/developers/docs/resources/guild#create-guild)
- [x] [Get Guild](https://discord.com/developers/docs/resources/guild#get-guild)
- [x] [Get Guild Preview](https://discord.com/developers/docs/resources/guild#get-guild-preview)
- [x] [Modify Guild](https://discord.com/developers/docs/resources/guild#modify-guild)
- [x] [Delete Guild](https://discord.com/developers/docs/resources/guild#delete-guild)
- [x] [Get Guild Channels](https://discord.com/developers/docs/resources/guild#get-guild-channels)
- [x] [Modify Guild Channel Position](https://discord.com/developers/docs/resources/guild#modify-guild-channel-positions)
- [x] [Get Guild Member](https://discord.com/developers/docs/resources/guild#get-guild-member)
- [x] [List Guild Members](https://discord.com/developers/docs/resources/guild#list-guild-members)
- [x] [Search Guild Member](https://discord.com/developers/docs/resources/guild#search-guild-members)
- [x] [Add Guild Member](https://discord.com/developers/docs/resources/guild#add-guild-member)
- [x] [Modify Guild Member](https://discord.com/developers/docs/resources/guild#modify-guild-member)
- [x] [Modify Current User Nick](https://discord.com/developers/docs/resources/guild#modify-current-user-nick)
- [x] [Add Guild Member Role](https://discord.com/developers/docs/resources/guild#add-guild-member-role)
- [x] [Remove Guild Member Role](https://discord.com/developers/docs/resources/guild#remove-guild-member-role)
- [x] [Get Guild Bans](https://discord.com/developers/docs/resources/guild#get-guild-bans)
- [x] [Get Guild Ban](https://discord.com/developers/docs/resources/guild#get-guild-ban)
- [x] [Create Guild Ban](https://discord.com/developers/docs/resources/guild#create-guild-ban)
- [x] [Remove Guild Ban](https://discord.com/developers/docs/resources/guild#remove-guild-ban)
- [x] [Get Guild Roles](https://discord.com/developers/docs/resources/guild#get-guild-roles)
- [x] [Create Guild Role](https://discord.com/developers/docs/resources/guild#create-guild-role)
- [x] [Modify Guild Role Positions](https://discord.com/developers/docs/resources/guild#modify-guild-role-positions)
- [x] [Modify Guild Role](https://discord.com/developers/docs/resources/guild#modify-guild-role)
- [x] [Delete Guild Role](https://discord.com/developers/docs/resources/guild#delete-guild-role)
- [x] [Get Guild Prune Count](https://discord.com/developers/docs/resources/guild#get-guild-prune-count)
- [x] [Begin Guild Prune](https://discord.com/developers/docs/resources/guild#begin-guild-prune)
- [x] [Get Guild Voice Regions](https://discord.com/developers/docs/resources/guild#get-guild-voice-regions)
- [x] [Get Guild Invites](https://discord.com/developers/docs/resources/guild#get-guild-invites)
- [x] [Get Guild Integrations](https://discord.com/developers/docs/resources/guild#get-guild-integrations)
- [x] [Delete Guild Integration](https://discord.com/developers/docs/resources/guild#delete-guild-integration)
- [x] [Get Guild Widget Settings](https://discord.com/developers/docs/resources/guild#get-guild-widget-settings)
- [x] [Modify Guild Widget](https://discord.com/developers/docs/resources/guild#modify-guild-widget)
- [x] [Get Guild Widget](https://discord.com/developers/docs/resources/guild#get-guild-widget)
- [x] [Get Guild Vanity URL](https://discord.com/developers/docs/resources/guild#get-guild-vanity-url)
- [ ] [Get Guild Widget Image](https://discord.com/developers/docs/resources/guild#get-guild-widget-image)
- [x] [Get Guild Welcome Screen](https://discord.com/developers/docs/resources/guild#get-guild-welcome-screen)
- [x] [Modify Guild Welcome Screen](https://discord.com/developers/docs/resources/guild#modify-guild-welcome-screen)
- [x] [Modify Current User Voice State](https://discord.com/developers/docs/resources/guild#modify-current-user-voice-state)
- [x] [Modify User Voice State](https://discord.com/developers/docs/resources/guild#modify-user-voice-state)

### Guild Scheduled Event

- [x] [Guild Scheduled Event Structure](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-structure)
- [x] [Guild Scheduled Event Privacy Level](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-privacy-level)
- [x] [Guild Scheduled Event Entity Types](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-entity-types)
- [x] [Guild Scheduled Event Status](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-status)
- [x] [Guild Scheduled Event Entity Metadata](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-object-guild-scheduled-event-entity-metadata)
- [x] [Guild Scheduled Event User](https://discord.com/developers/docs/resources/guild-scheduled-event#guild-scheduled-event-user-object-guild-scheduled-event-user-structure)
- [x] [List Scheduled Events for Guild](https://discord.com/developers/docs/resources/guild-scheduled-event#list-scheduled-events-for-guild)
- [x] [Create Guild Scheduled Event](https://discord.com/developers/docs/resources/guild-scheduled-event#create-guild-scheduled-event)
- [x] [Get Guild Scheduled Event](https://discord.com/developers/docs/resources/guild-scheduled-event#get-guild-scheduled-event)
- [x] [Modify Guild Scheduled Event](https://discord.com/developers/docs/resources/guild-scheduled-event#modify-guild-scheduled-event)
- [x] [Delete Guild Scheduled Event](https://discord.com/developers/docs/resources/guild-scheduled-event#delete-guild-scheduled-event)
- [x] [Get Guild Scheduled Event Users](https://discord.com/developers/docs/resources/guild-scheduled-event#get-guild-scheduled-event-users)

### Guild Template

- [x] [Guild Template Structure](https://discord.com/developers/docs/resources/guild-template#guild-template-object)
- [x] [Get Guild Template](https://discord.com/developers/docs/resources/guild-template#get-guild-template)
- [x] [Create Guild from Guild Template](https://discord.com/developers/docs/resources/guild-template#create-guild-from-guild-template)
- [x] [Get Guild Templates](https://discord.com/developers/docs/resources/guild-template#get-guild-templates)
- [x] [Create Guild Template](https://discord.com/developers/docs/resources/guild-template#create-guild-template)
- [x] [Sync Guild Template](https://discord.com/developers/docs/resources/guild-template#sync-guild-template)
- [x] [Modify Guild Template](https://discord.com/developers/docs/resources/guild-template#modify-guild-template)
- [x] [Delete Guild Template](https://discord.com/developers/docs/resources/guild-template#delete-guild-template)

### Invite

- [x] [Invite Structure](https://discord.com/developers/docs/resources/invite#invite-object)
- [x] [Target User Types](https://discord.com/developers/docs/resources/invite#invite-object-target-user-types)
- [x] [Invite Metadata Structure](https://discord.com/developers/docs/resources/invite#invite-metadata-object)
- [x] [Get Invite](https://discord.com/developers/docs/resources/invite#get-invite)
- [x] [Delete Invite](https://discord.com/developers/docs/resources/invite#delete-invite)

### Stage Instance

- [x] [Stage Instance Structure](https://discord.com/developers/docs/resources/stage-instance#stage-instance-object-stage-instance-structure)
- [x] [Privacy Level](https://discord.com/developers/docs/resources/stage-instance#stage-instance-object-privacy-level)
- [x] [Create Stage Instance](https://discord.com/developers/docs/resources/stage-instance#create-stage-instance)
- [x] [Get Stage Instance](https://discord.com/developers/docs/resources/stage-instance#get-stage-instance)
- [x] [Modify Stage Instance](https://discord.com/developers/docs/resources/stage-instance#modify-stage-instance)
- [x] [Delete Stage Instance](https://discord.com/developers/docs/resources/stage-instance#delete-stage-instance)

### Sticker

- [x] [Sticker Structure](https://discord.com/developers/docs/resources/sticker#sticker-object-sticker-structure)
- [x] [Sticker Types](https://discord.com/developers/docs/resources/sticker#sticker-object-sticker-types)
- [x] [Sticker Format Types](https://discord.com/developers/docs/resources/sticker#sticker-object-sticker-format-types)
- [x] [Sticker Item Structure](https://discord.com/developers/docs/resources/sticker#sticker-item-object-sticker-item-structure)
- [x] [Sticker Pack Structure](https://discord.com/developers/docs/resources/sticker#sticker-item-object-sticker-pack-structure)
- [x] [Get Sticker](https://discord.com/developers/docs/resources/sticker#get-sticker)
- [x] [List Nitro Stickers Packs](https://discord.com/developers/docs/resources/sticker#list-nitro-sticker-packs)
- [x] [List Guild Stickers](https://discord.com/developers/docs/resources/sticker#list-guild-stickers)
- [x] [Get Guild Sticker](https://discord.com/developers/docs/resources/sticker#get-guild-sticker)
- [ ] [Create Guild Sticker](https://discord.com/developers/docs/resources/sticker#create-guild-sticker)
- [x] [Modify Guild Sticker](https://discord.com/developers/docs/resources/sticker#modify-guild-sticker)
- [x] [Delete Guild Sticker](https://discord.com/developers/docs/resources/sticker#delete-guild-sticker)

### User

- [x] [User Structure](https://discord.com/developers/docs/resources/user#user-object)
- [x] [User Flags](https://discord.com/developers/docs/resources/user#user-object-user-flags)
- [x] [Premium Types](https://discord.com/developers/docs/resources/user#user-object-premium-types)
- [x] [Connection Structure](https://discord.com/developers/docs/resources/user#connection-object)
- [x] [Visibility Types](https://discord.com/developers/docs/resources/user#connection-object-visibility-types)
- [x] [Get Current User](https://discord.com/developers/docs/resources/user#get-current-user)
- [x] [Get User](https://discord.com/developers/docs/resources/user#get-user)
- [x] [Modify Current User](https://discord.com/developers/docs/resources/user#modify-current-user)
- [x] [Get Current User Guilds](https://discord.com/developers/docs/resources/user#get-current-user-guilds)
- [x] [Leave Guild](https://discord.com/developers/docs/resources/user#leave-guild)
- [x] [Create DM](https://discord.com/developers/docs/resources/user#create-dm)
- [x] [Create Group DM](https://discord.com/developers/docs/resources/user#create-group-dm)
- [x] [Get User Connections](https://discord.com/developers/docs/resources/user#get-user-connections)

### Voice Resouce

- [x] [Voice State Structure](https://discord.com/developers/docs/resources/voice#voice-state-object)
- [x] [Voice Region Structure](https://discord.com/developers/docs/resources/voice#voice-region-object)
- [x] [List Voice Regions](https://discord.com/developers/docs/resources/voice#list-voice-regions)

### Webhook

- [x] [Webhook Structure](https://discord.com/developers/docs/resources/webhook#webhook-object)
- [x] [Webhook Types](https://discord.com/developers/docs/resources/webhook#webhook-object-webhook-types)
- [x] [Create Webhook](https://discord.com/developers/docs/resources/webhook#create-webhook)
- [x] [Get Channel Webhooks](https://discord.com/developers/docs/resources/webhook#get-channel-webhooks)
- [x] [Get Guild Webhooks](https://discord.com/developers/docs/resources/webhook#get-guild-webhooks)
- [x] [Get Webhook](https://discord.com/developers/docs/resources/webhook#get-webhook)
- [x] [Get Webhook with Token](https://discord.com/developers/docs/resources/webhook#get-webhook-with-token)
- [x] [Modify Webhook](https://discord.com/developers/docs/resources/webhook#modify-webhook)
- [x] [Modify Webhook with Token](https://discord.com/developers/docs/resources/webhook#modify-webhook-with-token)
- [x] [Delete Webhook](https://discord.com/developers/docs/resources/webhook#delete-webhook)
- [x] [Delete Webhook with Token](https://discord.com/developers/docs/resources/webhook#delete-webhook-with-token)
- [x] [Execute Webhook](https://discord.com/developers/docs/resources/webhook#execute-webhook)
- [ ] [Execute Slack-Compatible Webhook](https://discord.com/developers/docs/resources/webhook#execute-slackcompatible-webhook)
- [ ] [Execute GitHub-Compatible Webhook](https://discord.com/developers/docs/resources/webhook#execute-githubcompatible-webhook)
- [x] [Edit Webhook Message](https://discord.com/developers/docs/resources/webhook#edit-webhook-message)
- [x] [Delete Webhook Message](https://discord.com/developers/docs/resources/webhook#delete-webhook-message)

## Topics

### Gateway

- [x] [Resuming](https://discord.com/developers/docs/topics/gateway#resuming)
- [ ] [Encoding and Compression](https://discord.com/developers/docs/topics/gateway#encoding-and-compression)
- [x] [Connecting to the Gateway](https://discord.com/developers/docs/topics/gateway#connecting-to-the-gateway)
- [x] [Gateway Intents](https://discord.com/developers/docs/topics/gateway#gateway-intents)
- [x] [Rate Limiting](https://discord.com/developers/docs/topics/gateway#rate-limiting)
- [ ] [Tracking State](https://discord.com/developers/docs/topics/gateway#tracking-state)
- [ ] [Sharding](https://discord.com/developers/docs/topics/gateway#sharding)
- [ ] [Sharding for Very Large Bots](https://discord.com/developers/docs/topics/gateway#sharding-for-very-large-bots)
- [x] [Commands and Events](https://discord.com/developers/docs/topics/gateway#commands-and-events)
- [x] [Get Gateway](https://discord.com/developers/docs/topics/gateway#get-gateway)
- [x] [Get Gateway Bot](https://discord.com/developers/docs/topics/gateway#get-gateway-bot)

### OAuth2

- [x] [Get Current Bot Application Information](https://discord.com/developers/docs/topics/oauth2#get-current-bot-application-information)
- [x] [Get Current Authorization Information](https://discord.com/developers/docs/topics/oauth2#get-current-authorization-information)

### Opcodes and Status Codes

- [x] [Gateway Opcodes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-opcodes)
- [x] [Gateway Close Event Codes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#gateway-gateway-close-event-codes)
- [x] [Voice Opcodes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-opcodes)
- [x] [Voice Close Event Codes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#voice-voice-close-event-codes)
- [x] [HTTP Response Codes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#http-http-response-codes)
- [x] [JSON Error Codes](https://discord.com/developers/docs/topics/opcodes-and-status-codes#json-json-error-codes)

### Permissions

- [x] [Bitwise Permission Flags](https://discord.com/developers/docs/topics/permissions#permissions-bitwise-permission-flags)
- [x] [Role Structure](https://discord.com/developers/docs/topics/permissions#role-object)
- [x] [Role Tags Structure](https://discord.com/developers/docs/topics/permissions#role-object-role-tags-structure)

### RateLimits

- [x] [Exceeding A Rate Limit](https://discord.com/developers/docs/topics/rate-limits#exceeding-a-rate-limit)
- [x] [Invalid Request Limit](https://discord.com/developers/docs/topics/rate-limits#invalid-request-limit)

### Voice Connections
