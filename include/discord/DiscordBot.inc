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
    /* Unused until there is no wss */

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

    /* - - */

    public DiscordBot(const char[] token/*, DiscordPresence presence, DiscordGatewayPayload payload = null*/)
    {
        JSON_Object obj = new JSON_Object();
        obj.SetString("token", token);
        //obj.SetObject("properties", payload);
        //obj.SetObject("presence", presence);
        return view_as<DiscordBot>(obj);
    }

    public bool GetToken(char[] output, int maxsize)
    {
        return this.GetString("token", output, maxsize);
    }

    /**
	* Release resources
	*/
	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}

    /* Documentation & Callbacks will be added later */
    /* TODO
    public native void GetConnections();
    public native void GetGuilds();

    public native void GetUser();
    public native void GetCurrentUser();

    public native void GetChannelMessage();
    public native void GetChannelMessages();
    public native void GetPinnedMessages();

    public native void GetReactions();

    public native void GetGuildEmoji();
    public native void CreateGuildEmoji();
    public native void ModifyGuildEmoji();
    public native void DeleteGuildEmoji();
    */

    /* Callback: Returns a guild object on success. */
    public native void CreateGuild(DiscordGuild guild);

    public native void AddRole(DiscordGuild guild, DiscordUser user, DiscordRole role);
    public native void RemoveRole(DiscordGuild guild, DiscordUser user, DiscordRole role);

    public native void AddRoleID(const char[] guildid, const char[] userid, const char[] roleid);
    public native void RemoveRoleID(const char[] guildid, const char[] userid, const char[] roleid);

    /* Callback: Returns a DM channel object. */
    public native void CreateDM(DiscordUser user);
    public native void CreateDMID(const char[] userid);

    /* Callback: Returns a user object on success. */
    public native void ModifySelf(const char[] username, const char[] avatar = "");

    /* Callback: Returns a channel object on success. */
    /**
    * Delete a channel, or close a private message. Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread.
    *
    * @param channel     channel you want to delete.
    */
    public native void DeleteChannel(DiscordChannel channel);

    /**
    * Delete a channel, or close a private message. Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread.
    *
    * @param channelid     ID of the channel that you want to delete.
    */
    public native void DeleteChannelID(const char[] channelid);

    /* Callback: Returns a channel on success, and a 400 BAD REQUEST on invalid parameters. */
    public native void ModifyChannel(DiscordChannel from, DiscordChannel to);
    public native void ModifyChannelID(const char[] channelid, DiscordChannel to);

    /* Callback: Returns a message object. */
    public native void SendMessageToChannel(DiscordChannel channel, DiscordMessage message);
    public native void SendMessageToChannelID(const char[] channel, DiscordMessage message);

    /* Callbackk: Returns a message object. */
    public native void EditMessage(DiscordChannel channel, DiscordMessage from, DiscordMessage to);
    public native void EditMessageID(const char[] channelid, const char[] messageid, DiscordMessage to);

    public native void PinMessage(DiscordChannel channel, DiscordMessage message);
    public native void PinMessageID(const char[] channelid, const char[] messageid);

    public native void UnpinMessage(DiscordChannel channel, DiscordMessage message);
    public native void UnpinMessageID(const char[] channelid, const char[] messageid);

    /**
    * Delete a message. If operating on a guild channel and trying to delete a message that was not sent by the current user, this endpoint requires the MANAGE_MESSAGES permission.
    *
    * @param channel     channel where the message is.
    * @param message     message you want to delete.
    */
    public native void DeleteMessage(DiscordChannel channel, DiscordMessage message);

    /**
    * Delete a message. If operating on a guild channel and trying to delete a message that was not sent by the current user, this endpoint requires the MANAGE_MESSAGES permission.
    *
    * @param channelid     channel id where the message is.
    * @param messageid     message id you want to delete.
    */
    public native void DeleteMessageID(const char[] channelid, const char[] messageid);

    /**
    * Delete multiple messages in a single request. This endpoint can only be used on guild channels and requires the MANAGE_MESSAGES permission.
    *
    * @param channel        channel where the message is.
    * @param messages       an array of message ids to delete (2-100).
    */
    public native void DeleteMessagesBulk(DiscordChannel channel, JSON_Array messages);

    /**
    * Create a reaction for the message. This endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user. Additionally, if nobody else has reacted to the message using this emoji, this endpoint requires the 'ADD_REACTIONS' permission to be present on the current user.
    *
    * @param channel     channel where the message is.
    * @param message     message that you want to react to.
    * @param emoji       reaction emoji.
    */
    public native void CreateReaction(DiscordChannel channel, DiscordMessage message, DiscordEmoji emoji);
    
    /**
    * Create a reaction for the message. This endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user. Additionally, if nobody else has reacted to the message using this emoji, this endpoint requires the 'ADD_REACTIONS' permission to be present on the current user.
    *
    * @param channelid      channel id where the message is.
    * @param messageid      message id that you want to react to.
    * @param emoji          reaction emoji.
    */
    public native void CreateReactionID(const char[] channelid, const char[] messageid, DiscordEmoji emoji);

    public native void DeleteOwnReaction(DiscordChannel channel, DiscordMessage message, DiscordEmoji emoji);
    public native void DeleteOwnReactionID(const char[] channelid, const char[] messageid, DiscordEmoji emoji);

    public native void DeleteReaction(DiscordChannel channel, DiscordMessage message, DiscordEmoji emoji, DiscordUser user);
    public native void DeleteReactionID(const char[] channelid, const char[] messageid, DiscordEmoji emoji, DiscordUser user);

    public native void DeleteAllReactions(DiscordChannel channel, DiscordMessage message);
    public native void DeleteAllReactionsID(const char[] channelid, const char[] messageid);

    public native void DeleteAllReactionsEmoji(DiscordChannel channel, DiscordMessage message, DiscordEmoji emoji);
    public native void DeleteAllReactionsEmojiID(const char[] channelid, const char[] messageid, DiscordEmoji emoji);
}