#if defined _DiscordBot_included_
  #endinput
#endif
#define _DiscordBot_included_

#include <discord/DiscordIdentifyProperties>
#include <discord/DiscordChannel>

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

	property float MessageCheckInterval
	{
		public get() { return this.GetFloat("message_check_interval", 3.0); }
		public set(float value) { this.SetFloat("message_check_interval", value); }
	}

	public DiscordBot(const char[] token/*, DiscordPresence presence, DiscordGatewayPayload payload = null*/)
	{
		JSON_Object obj = new JSON_Object();
		obj.SetString("token", token);
		//obj.SetObject("properties", payload);
		//obj.SetObject("presence", presence);
		return view_as<DiscordBot>(obj);
	}

	public JSON_Array GetListeningChannels()
	{
		return view_as<JSON_Array>(this.GetObject("listening_channels"));
	}

	/**
	* Checks if the bot is listening to channel for messages
	* @param channelid channel id.
	*/
	public bool IsListeningToChannelID(const char[] channelid)
	{
		JSON_Array channels = this.GetListeningChannels();
		if(channels != null)
		{
			for(int i = 0; i < channels.Length; i++)
			{
				static char tempID[32];
				channels.GetString(i, tempID, sizeof(tempID));

				if(StrEqual(channelid, tempID, false))
				{
					return true;
				}
			}
		}

		return false;
	}

	/**
	* Checks if the bot is listening to channel for messages
	* @param channel		channel object.
	*/
	public bool IsListeningToChannel(DiscordChannel channel)
	{
		char channelid[32];
		channel.GetID(channelid, sizeof(channelid));
		return this.IsListeningToChannelID(channelid);
	}

	/**
	* Stops the bot from listening to that channel id for messages
	* @param channelid		channel id.
	*/
	public void StopListeningToChannelID(const char[] channelid)
	{
		JSON_Array channels = this.GetListeningChannels();
		if(channels != null)
		{
			for(int i = 0; i < channels.Length; i++)
			{
				static char tempID[32];
				channels.GetString(i, tempID, sizeof(tempID));

				if(StrEqual(channelid, tempID))
				{
					channels.Remove(i);
					i--;
				}
			}
		}
	}

	public native void StartTimer(DiscordChannel channel, OnDiscordChannelMessage callback);

	/**
	* Stops the bot from listening to that channel id for messages
	* @param channel		channel object.
	*/
	public void StopListeningToChannel(DiscordChannel channel)
	{
		char channelid[32];
		channel.GetID(channelid, sizeof(channelid));
		this.StopListeningToChannelID(channelid);
	}

	/**
	* Start listening to the channel for messages.
	* @param channel		channel object.
	*/
	public void StartListeningToChannel(DiscordChannel channel, OnDiscordChannelMessage callback)
	{
		if(this.IsListeningToChannel(channel))
			return;

		JSON_Array channels = this.GetListeningChannels();
		if(channels == null)
		{
			channels = new JSON_Array();
			this.SetObject("listening_channels", channels);
		}

		char channelid[32];
		channel.GetID(channelid, sizeof(channelid));
		channels.PushString(channelid);
		this.StartTimer(channel, callback);
	}

	/**
	* Get the bot token.
	* @param output			output buffer.
	* @param maxsize		maximum length.
	*/
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

	/**
	* Create a new guild.
	* Fires a Guild Create Gateway event.
	* This endpoint can be used only by bots in less than 10 guilds.
	* 
	* @param guild			guild object with these values: https://discord.com/developers/docs/resources/guild#create-guild-json-params
	* @param callback		a DiscordGuild object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void CreateGuild(DiscordGuild guild, OnDiscordGuildCreated callback, any data = 0, any data2 = 0);

	/**
	* Returns the guild object for the given id.
	* If with_counts is set to true, this will also return approximate_member_count and approximate_presence_count for the guild.
	* 
	* DiscordGuild handle will not be deleted automatically when the callback function returns, it is your responsibility to manage memory.
	* 
	* @param guildid		id of the guild you want to get.
	* @param with_counts	when true, will return approximate member and presence counts for the guild
	* @param callback		a DiscordGuild object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void GetGuild(const char[] guildid, bool with_counts, OnGetDiscordGuild callback, any data = 0, any data2 = 0);

	/**
	* Returns a guild member object for the specified user id.
	*
	* DiscordGuildUser handle will not be deleted automatically when the callback function returns, it is your responsibility to manage memory.
	* 
	* @param guild			DiscordGuild from where you want to get the user.
	* @param user			DiscordUser that you want to get. (DiscordGuildUser object is different than a normal DiscordUser)
	* @param callback		a DiscordGuildUser object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void GetGuildMember(DiscordGuild guild, DiscordUser user, OnGetDiscordGuildUser callback, any data = 0, any data2 = 0);

	/**
	* Returns a guild member object for the specified user id.
	*
	* DiscordGuildUser handle will not be deleted automatically when the callback function returns, it is your responsibility to manage memory.
	* 
	* @param guildid		guild ID from where you want to get the user.
	* @param userid			user ID that you want to get. (DiscordGuildUser object is different than a normal DiscordUser)
	* @param callback		a DiscordGuildUser object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void GetGuildMemberID(const char[] guildid, const char[] userid, OnGetDiscordGuildUser callback, any data = 0, any data2 = 0);

	/**
	* Adds a role to a guild member.
	* Requires the MANAGE_ROLES permission.
	* Returns a 204 empty response on success.
	* Fires a Guild Member Update Gateway event.
	*
	* @param guild			where you want to add the role to the user.
	* @param user			target who get the role.
	* @param role			that will be added to the user.
	*/
	public native void AddRole(DiscordGuild guild, DiscordUser user, DiscordRole role);

	/**
	* Adds a role to a guild member.
	* Requires the MANAGE_ROLES permission.
	* Returns a 204 empty response on success.
	* Fires a Guild Member Update Gateway event.
	*
	* @param guild			ID where you want to add the role to the user.
	* @param user			ID target who get the role.
	* @param role			ID that will be added to the user.
	*/
	public native void AddRoleID(const char[] guildid, const char[] userid, const char[] roleid);
		
	/**
	* Removes a role from a guild member.
	* Requires the MANAGE_ROLES permission.
	* Returns a 204 empty response on success.
	* Fires a Guild Member Update Gateway event.
	*
	* @param guild			where you want to remove the role from the user.
	* @param user			target who lose the role.
	* @param role			that will be removed from the user.
	*/
	public native void RemoveRole(DiscordGuild guild, DiscordUser user, DiscordRole role);

	/**
	* Removes a role from a guild member.
	* Requires the MANAGE_ROLES permission.
	* Returns a 204 empty response on success.
	* Fires a Guild Member Update Gateway event.
	*
	* @param guild			ID where you want to remove the role from the user.
	* @param user			ID target who lose the role.
	* @param role			ID that will be removed from the user.
	*/
	public native void RemoveRoleID(const char[] guildid, const char[] userid, const char[] roleid);

	/**
	* Create a new DM channel with a user.
	* You should not use this endpoint to DM everyone in a server about something. DMs should generally be initiated by a user action. If you open a significant amount of DMs too quickly, your bot may be rate limited or blocked from opening new ones.
	* 
	* @param user			the recipient to open a DM channel with
	* @param callback		a DM channel object.
	*/
	public native void CreateDM(DiscordUser user);

	/**
	* Create a new DM channel with a user.
	* You should not use this endpoint to DM everyone in a server about something. DMs should generally be initiated by a user action. If you open a significant amount of DMs too quickly, your bot may be rate limited or blocked from opening new ones.
	* 
	* @param userid			the recipient user id to open a DM channel with
	* @param callback		a DM channel object.
	*/
	public native void CreateDMID(const char[] userid);

	/** Modify the requester's user account settings.
	* 
	* @param username		user's username, if changed may cause the user's discriminator to be randomized.
	* @param avatar			if passed, modifies the user's avatar
	* @param callback		a user object on success.
	*/
	public native void ModifySelf(const char[] username, const char[] avatar = "");

	/**
	* Get a channel by ID.
	* Returns a channel object.
	* If the channel is a thread, a thread member object is included in the returned result.
	*
	* @param channelid		id of channel you want to get.
	* @param callback		a channel object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void GetChannel(const char[] channelid, OnGetDiscordChannel callback, any data = 0, any data2 = 0);

	/**
	* Delete a channel, or close a private message.
	* Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread.
	*
	* @param channel		channel you want to delete.
	* @param callback		a channel object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void DeleteChannel(DiscordChannel channel, OnDiscordChannelDeleted callback, any data = 0, any data2 = 0);

	/**
	* Delete a channel, or close a private message. Requires the MANAGE_CHANNELS permission for the guild, or MANAGE_THREADS if the channel is a thread.
	*
	* @param channelid		ID of the channel that you want to delete.
	* @param callback		a channel object on success.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void DeleteChannelID(const char[] channelid, OnDiscordChannelDeleted callback, any data = 0, any data2 = 0);

	/**
	* Update a channel's settings.
	* All JSON parameters are optional.
	* 
	* @param from			DiscordChannel the channel you want to modify.
	* @param to				DiscordChannel object with the modifies you want to apply to the channel.
	* @param callback		a channel on success, and a 400 BAD REQUEST on invalid parameters.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void ModifyChannel(DiscordChannel from, DiscordChannel to, OnDiscordChannelModified callback, any data = 0, any data2 = 0);

	/**
	* Update a channel's settings.
	* All JSON parameters are optional.
	* 
	* @param channelid		id of the channel you want to modify.
	* @param to				DiscordChannel object with the modifies you want to apply to the channel.
	* @param callback		a channel on success, and a 400 BAD REQUEST on invalid parameters.
	* @param data			custom data passed through the request to use in the callback
	* @param data2			custom data passed through the request to use in the callback
	*/
	public native void ModifyChannelID(const char[] channelid, DiscordChannel to, OnDiscordChannelModified callback, any data = 0, any data2 = 0);

	/**
	* Post a message to a guild text or DM channel.
	* Fires a Message Create Gateway event.
	* See https://discord.com/developers/docs/reference#message-formatting for more information on how to properly format messages.
	* Files must be attached using a multipart/form-data body as described in Uploading Files. (Not supported yet)
	* 
	* @param channel		DiscordChannel where you want to send the message. (Can be DM)
	* @param message		DiscordMessage object that you want to send.
	* @param callback 		a message object.
	*/
	public native void SendMessageToChannel(DiscordChannel channel, DiscordMessage message);

	/**
	* Post a message to a guild text or DM channel.
	* Fires a Message Create Gateway event.
	* See https://discord.com/developers/docs/reference#message-formatting for more information on how to properly format messages.
	* Files must be attached using a multipart/form-data body as described in Uploading Files. (Not supported yet)
	* 
	* @param channel		id of the channel where you want to send the message.
	* @param message		DiscordMessage object that you want to send.
	* @param callback 		a message object.
	*/
	public native void SendMessageToChannelID(const char[] channel, DiscordMessage message);

	/**
	* Edit a previously sent message. The fields content, embeds, and flags can be edited by the original message author. Other users can only edit flags and only if they have the MANAGE_MESSAGES permission in the corresponding channel. When specifying flags, ensure to include all previously set flags/bits in addition to ones that you are modifying. Only flags documented in the table below may be modified by users (unsupported flag changes are currently ignored without error).
	* When the content field is edited, the mentions array in the message object will be reconstructed from scratch based on the new content. The allowed_mentions field of the edit request controls how this happens. If there is no explicit allowed_mentions in the edit request, the content will be parsed with default allowances, that is, without regard to whether or not an allowed_mentions was present in the request that originally created the message.
	* Fires a Message Update Gateway event.
	* 
	* @param channel		DiscordChannel where the message is located.
	* @param from			DiscordMessage that you want to edit.
	* @param to				DiscordMessage with the modifies you want to apply to the message.
	* @param callback 		a message object.
	*/
	public native void EditMessage(DiscordChannel channel, DiscordMessage from, DiscordMessage to);

	/**
	* Edit a previously sent message. The fields content, embeds, and flags can be edited by the original message author. Other users can only edit flags and only if they have the MANAGE_MESSAGES permission in the corresponding channel. When specifying flags, ensure to include all previously set flags/bits in addition to ones that you are modifying. Only flags documented in the table below may be modified by users (unsupported flag changes are currently ignored without error).
	* When the content field is edited, the mentions array in the message object will be reconstructed from scratch based on the new content. The allowed_mentions field of the edit request controls how this happens. If there is no explicit allowed_mentions in the edit request, the content will be parsed with default allowances, that is, without regard to whether or not an allowed_mentions was present in the request that originally created the message.
	* Fires a Message Update Gateway event.
	* 
	* @param channelid		id of the channel where the message is located.
	* @param messageid		id of the message that you want to edit.
	* @param to				DiscordMessage with the modifies you want to apply to the message.
	* @param callback 		a message object.
	*/
	public native void EditMessageID(const char[] channelid, const char[] messageid, DiscordMessage to);

	public native void PinMessage(DiscordChannel channel, DiscordMessage message);
	public native void PinMessageID(const char[] channelid, const char[] messageid);

	public native void UnpinMessage(DiscordChannel channel, DiscordMessage message);
	public native void UnpinMessageID(const char[] channelid, const char[] messageid);

	/**
	* Delete a message. If operating on a guild channel and trying to delete a message that was not sent by the current user, this endpoint requires the MANAGE_MESSAGES permission.
	*
	* @param channel		channel where the message is.
	* @param message		message you want to delete.
	*/
	public native void DeleteMessage(DiscordChannel channel, DiscordMessage message);

	/**
	* Delete a message. If operating on a guild channel and trying to delete a message that was not sent by the current user, this endpoint requires the MANAGE_MESSAGES permission.
	*
	* @param channelid		channel id where the message is.
	* @param messageid		message id you want to delete.
	*/
	public native void DeleteMessageID(const char[] channelid, const char[] messageid);

	/**
	* Delete multiple messages in a single request. This endpoint can only be used on guild channels and requires the MANAGE_MESSAGES permission.
	*
	* @param channel		channel where the message is.
	* @param messages		an array of message ids to delete (2-100).
	*/
	public native void DeleteMessagesBulk(DiscordChannel channel, JSON_Array messages);

	/**
	* Create a reaction for the message. This endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user. Additionally, if nobody else has reacted to the message using this emoji, this endpoint requires the 'ADD_REACTIONS' permission to be present on the current user.
	*
	* @param channel		channel where the message is.
	* @param message		message that you want to react to.
	* @param emoji			reaction emoji.
	*/
	public native void CreateReaction(DiscordChannel channel, DiscordMessage message, DiscordEmoji emoji);
		
	/**
	* Create a reaction for the message. This endpoint requires the 'READ_MESSAGE_HISTORY' permission to be present on the current user. Additionally, if nobody else has reacted to the message using this emoji, this endpoint requires the 'ADD_REACTIONS' permission to be present on the current user.
	*
	* @param channelid		channel id where the message is.
	* @param messageid		message id that you want to react to.
	* @param emoji			reaction emoji.
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