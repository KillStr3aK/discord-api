#if defined _DiscordChannel_included_
  #endinput
#endif
#define _DiscordChannel_included_

enum DiscordChannelType
{
	GUILD_TEXT = 0, /* a text channel within a server */
	DM, /* a direct message between users */
	GUILD_VOICE, /* a voice channel within a server */
	GROUP_DM, /* a direct message between multiple users */
	GUILD_CATEGORY, /* an organizational category that contains up to 50 channels. for further info: https://support.discord.com/hc/en-us/articles/115001580171-Channel-Categories-101 */
	GUILD_NEWS, /* a channel that users can follow and crosspost into their own server. for further info: https://support.discord.com/hc/en-us/articles/360032008192 */
	GUILD_STORE, /* a channel in which game developers can sell their game on Discord. for further info: https://discord.com/developers/docs/game-and-server-management/special-channels */
	GUILD_NEWS_THREAD = 10, /* a temporary sub-channel within a GUILD_NEWS channel */
	GUILD_PUBLIC_THREAD, /* a temporary sub-channel within a GUILD_TEXT channel */
	GUILD_PRIVATE_THREAD, /* a temporary sub-channel within a GUILD_TEXT channel that is only viewable by those invited and those with the MANAGE_THREADS permission */
	GUILD_STAGE_VOICE /* a voice channel for hosting events with an audience. for further info: https://support.discord.com/hc/en-us/articles/1500005513722 */
}

enum DiscordChannelVideoQualityMode
{
	AUTO = 1, /* Discord chooses the quality for optimal performance */
	FULL /* 720p */
}

/* Represents a guild or DM channel within Discord. */
methodmap DiscordChannel < DiscordObject
{
	property DiscordChannelType Type
	{
		public get() { return view_as<DiscordChannelType>(this.GetInt("type")); }
	}

	property bool IsNSFW
	{
		public get() { return this.GetBool("nsfw"); }
	}

	property int Bitrate
	{
		public get() { return this.GetInt("bitrate"); }
	}

	property int UserLimit
	{
		public get() { return this.GetInt("user_limit"); }
	}

	property DiscordChannelVideoQualityMode VideoQualityMode
	{
		public get() { return view_as<DiscordChannelVideoQualityMode>(this.GetInt("video_quality_mode")); }
	}

	/* an approximate count of users in a thread, stops counting at 50 */
	property int MemberCount
	{
		public get() { return this.GetInt("member_count"); }
	}

	/* 	an approximate count of messages in a thread, stops counting at 50 */
	property int MessageCount
	{
		public get() { return this.GetInt("message_count"); }
	}

	public bool GetIcon(char[] output, int maxsize)
    {
        return this.GetString("icon", output, maxsize);
    }

	public bool GetName(char[] output, int maxsize)
    {
        return this.GetString("name", output, maxsize);
    }

	public bool GetTopic(char[] output, int maxsize)
    {
        return this.GetString("topic", output, maxsize);
    }

	public bool GetRtcRegion(char[] output, int maxsize)
    {
        return this.GetString("rtc_region", output, maxsize);
    }
}