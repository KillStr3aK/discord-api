#if defined _DiscordBot_included_
  #endinput
#endif
#define _DiscordBot_included_

#include <discord/DiscordIdentifyProperties>

enum DiscordGatewayIntents
{
    /*
    - GUILD_CREATE
    - GUILD_UPDATE
    - GUILD_DELETE
    - GUILD_ROLE_CREATE
    - GUILD_ROLE_UPDATE
    - GUILD_ROLE_DELETE
    - CHANNEL_CREATE
    - CHANNEL_UPDATE
    - CHANNEL_DELETE
    - CHANNEL_PINS_UPDATE
    - THREAD_CREATE
    - THREAD_UPDATE
    - THREAD_DELETE
    - THREAD_LIST_SYNC
    - THREAD_MEMBER_UPDATE
    - THREAD_MEMBERS_UPDATE *
    - STAGE_INSTANCE_CREATE
    - STAGE_INSTANCE_UPDATE
    - STAGE_INSTANCE_DELETE
    */
    GUILDS = (1 << 0),

    /*
    - GUILD_MEMBER_ADD
    - GUILD_MEMBER_UPDATE
    - GUILD_MEMBER_REMOVE
    - THREAD_MEMBERS_UPDATE *
    */
    GUILD_MEMBERS = (1 << 1),

    /*
    - GUILD_BAN_ADD
    - GUILD_BAN_REMOVE
    */
    GUILD_BANS = (1 << 2),

    /*
    - GUILD_EMOJIS_UPDATE
    */
    GUILD_EMOJIS = (1 << 3),

    /*
    - GUILD_INTEGRATIONS_UPDATE
    - INTEGRATION_CREATE
    - INTEGRATION_UPDATE
    - INTEGRATION_DELETE
    */
    GUILD_INTEGRATIONS = (1 << 4),

    /*
    - WEBHOOKS_UPDATE
    */
    GUILD_WEBHOOKS = (1 << 5),

    /*
    - INVITE_CREATE
    - INVITE_DELETE
    */
    GUILD_INVITES = (1 << 6),

    /*
    - VOICE_STATE_UPDATE
    */
    GUILD_VOICE_STATES = (1 << 7),

    /*
    - PRESENCE_UPDATE
    */
    GUILD_PRESENCES = (1 << 8),

    /*
    - MESSAGE_CREATE
    - MESSAGE_UPDATE
    - MESSAGE_DELETE
    - MESSAGE_DELETE_BULK
    */
    GUILD_MESSAGES = (1 << 9),

    /*
    - MESSAGE_REACTION_ADD
    - MESSAGE_REACTION_REMOVE
    - MESSAGE_REACTION_REMOVE_ALL
    - MESSAGE_REACTION_REMOVE_EMOJI
    */
    GUILD_MESSAGE_REACTIONS = (1 << 10),

    /*
    - TYPING_START
    */
    GUILD_MESSAGE_TYPING = (1 << 11),

    /*
    - MESSAGE_CREATE
    - MESSAGE_UPDATE
    - MESSAGE_DELETE
    - CHANNEL_PINS_UPDATE
    */
    DIRECT_MESSAGES = (1 << 12),

    /*
    - MESSAGE_REACTION_ADD
    - MESSAGE_REACTION_REMOVE
    - MESSAGE_REACTION_REMOVE_ALL
    - MESSAGE_REACTION_REMOVE_EMOJI
    */
    DIRECT_MESSAGE_REACTIONS = (1 << 13),

    /*
    - TYPING_START
    */
    DIRECT_MESSAGE_TYPING = (1 << 14)
} 

methodmap DiscordBot < JSON_Object
{
    property bool Compress
    {
        public get() { return this.GetBool("compress"); }
        public set(bool value) { this.SetBool("compress", value); }
    }

    property int Threshold
    {
        public get() { return this.GetInt("large_threshold"); }
    }

    property DiscordGatewayIntents Intents
    {
        public get() { return view_as<DiscordGatewayIntents>(this.GetInt("intents")); }
        public set(DiscordGatewayIntents value) { this.SetInt("intents", view_as<int>(value)); }
    }

    public DiscordBot(const char[] token/*, DiscordPresence presence, DiscordGatewayPayload payload = null*/)
    {
        JSON_Object obj = new JSON_Object();
        obj.SetString("token", token);
        //obj.SetObject("properties", payload);
        //obj.SetObject("presence", presence);
        return view_as<DiscordBot>(obj);
    }
}