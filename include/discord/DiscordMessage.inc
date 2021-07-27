#if defined _DiscordMessage_included_
  #endinput
#endif
#define _DiscordMessage_included_

#include <discord/DiscordMessageReference>
//#include <discord/DiscordMessageComponent>

enum DiscordMessageActivityTypes
{
    JOIN = 1,
    SPECTATE = 2,
    LISTEN = 3,
    JOIN_REQUEST = 4
}

enum DiscordMessageFlags
{
    CROSSPOSTED = (1 << 0), /* this message has been published to subscribed channels (via Channel Following) */
    IS_CROSSPOST = (1 << 1), /* this message originated from a message in another channel (via Channel Following) */
    SUPPRESS_EMBEDS = (1 << 2), /* do not include any embeds when serializing this message */
    SOURCE_MESSAGE_DELETED = (1 << 3), /* the source message for this crosspost has been deleted (via Channel Following) */
    URGENT = (1 << 4), /* this message came from the urgent message system */
    HAS_THREAD = (1 << 5), /* this message has an associated thread, with the same id as the message */
    EPHEMERAL = (1 << 6), /* this message is only visible to the user who invoked the Interaction */
    LOADING = (1 << 7) /* this message is an Interaction Response and the bot is "thinking" */
}

enum DiscordMessageStickerFormat
{
    PNG = 1,
    APNG = 2,
    LOTTIE = 3
}

enum DiscordMessageType
{
    Type_DEFAULT = 0,
    RECIPIENT_ADD = 1,
    RECIPIENT_REMOVE = 2,
    CALL = 3,
    CHANNEL_NAME_CHANGE = 4,
    CHANNEL_ICON_CHANGE = 5,
    CHANNEL_PINNED_MESSAGE = 6,
    GUILD_MEMBER_JOIN = 7,
    USER_PREMIUM_GUILD_SUBSCRIPTION = 8,
    USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_1 = 9,
    USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_2 = 10,
    USER_PREMIUM_GUILD_SUBSCRIPTION_TIER_3 = 11,
    CHANNEL_FOLLOW_ADD = 12,
    GUILD_DISCOVERY_DISQUALIFIED = 14,
    GUILD_DISCOVERY_REQUALIFIED = 15,
    GUILD_DISCOVERY_GRACE_PERIOD_INITIAL_WARNING = 16,
    GUILD_DISCOVERY_GRACE_PERIOD_FINAL_WARNING = 17,
    THREAD_CREATED = 18,
    REPLY = 19,
    APPLICATION_COMMAND = 20,
    THREAD_STARTER_MESSAGE = 21,
    GUILD_INVITE_REMINDER = 22,
}

typedef OnMessageSent = function void (DiscordBot bot, DiscordChannel channel, DiscordMessage message);

methodmap DiscordMessageSticker < DiscordObject
{
    property DiscordMessageStickerFormat Format
    {
        public get() { return view_as<DiscordMessageStickerFormat>(this.GetInt("format_type")); }
    }

    property bool Available
    {
        public get() { return this.GetBool("available"); }
    }

    property int SortValue
    {
        public get() { return this.GetInt("sort_value"); }
    }

    /* the user that uploaded the sticker */
    public DiscordUser GetUser()
    {
        return view_as<DiscordUser>(this.GetObject("user"));
    }

    public bool GetPackID(char[] output, int maxsize)
	{
		return this.GetString("pack_id", output, maxsize);
	}

    public bool GetGuildID(char[] output, int maxsize)
	{
		return this.GetString("guild_id", output, maxsize);
	}

    public bool GetName(char[] output, int maxsize)
	{
		return this.GetString("name", output, maxsize);
	}

    public bool GetDescription(char[] output, int maxsize)
	{
		return this.GetString("description", output, maxsize);
	}

    public bool GetTags(char[] output, int maxsize)
	{
		return this.GetString("tags", output, maxsize);
	}

    public bool GetAsset(char[] output, int maxsize)
	{
		return this.GetString("asset", output, maxsize);
	}
}

methodmap DiscordMessage < DiscordObject
{
    property bool MentionsEveryone
    {
        public get() { return this.GetBool("mention_everyone"); }
    }

    property bool TTS
    {
        public get() { return this.GetBool("tts"); }
    }

    property bool Pinned
    {
        public get() { return this.GetBool("pinned"); }
    }

    property DiscordMessageType Type
    {
        public get() { return view_as<DiscordMessageType>(this.GetInt("type")); }
    }

    property DiscordUser Author
    {
        public get() { return view_as<DiscordUser>(this.GetObject("author")); }
    }

    property DiscordGuildUser Member
    {
        public get() { return view_as<DiscordGuildUser>(this.GetObject("member")); }
    }

    public DiscordMessage(const char[] content = "", DiscordEmbed embed = null)
    {
        JSON_Object obj = new JSON_Object();
        obj.SetString("content", content);
        
        if(embed != null)
        {
            JSON_Array embeds = new JSON_Array();
            embeds.PushObject(embed);
            obj.SetObject("embeds", embeds);
        }
            
        return view_as<DiscordMessage>(obj);
    }

    public bool GetWebhookID(char[] output, int maxsize)
	{
		return this.GetString("webhook_id", output, maxsize);
	}

    public bool GetChannelID(char[] output, int maxsize)
	{
		return this.GetString("channel_id", output, maxsize);
	}

    public bool GetGuildID(char[] output, int maxsize)
	{
		return this.GetString("guild_id", output, maxsize);
	}

    public DiscordUser GetAuthor()
	{
		return this.Author;
	}

    public DiscordGuildUser GetMember()
	{
		return this.Member;
	}

    public bool GetContent(char[] output, int maxsize)
	{
		return this.GetString("content", output, maxsize);
	}

    public bool GetTimestamp(char[] buffer, int maxsize)
    {
        return this.GetString("timestamp", buffer, maxsize);
    }

    public bool GetTimestampDateTime(DateTime& out)
    {
        char szDate[DATE_LENGTH];
        this.GetString("timestamp", szDate, sizeof(szDate));
        return DateTime.TryParse(szDate, out);
    }

    public bool GetEditedTimestamp(char[] buffer, int maxsize)
    {
        return this.GetString("edited_timestamp", buffer, maxsize);
    }

    public bool GetEditedTimestampDateTime(DateTime& out)
    {
        char szDate[DATE_LENGTH];
        this.GetString("edited_timestamp", szDate, sizeof(szDate));
        return DateTime.TryParse(szDate, out);
    }

    public JSON_Array GetMentionedUsers()
    {
        return view_as<JSON_Array>(this.GetObject("mentions"));
    }

    public JSON_Array GetMentionedRoles()
    {
        return view_as<JSON_Array>(this.GetObject("mention_roles"));
    }

    /* Array of DiscordChannelMention */
    public JSON_Array GetMentionedChannels()
    {
        return view_as<JSON_Array>(this.GetObject("mention_channels"));
    }

    public JSON_Array GetEmbeds()
    {
        return view_as<JSON_Array>(this.GetObject("embeds"));
    }

    public JSON_Array GetReactions()
    {
        return view_as<JSON_Array>(this.GetObject("reactions"));
    }

    /* Array of DiscordMessageSticker but only with id, name and format_type fields */
    public JSON_Array GetStickerItems()
    {
        return view_as<JSON_Array>(this.GetObject("sticker_items"));
    }

    /* Array of DiscordMessageSticker */
    public JSON_Array GetStickers()
    {
        return view_as<JSON_Array>(this.GetObject("stickers"));
    }

    public DiscordMessageReference GetReference()
    {
        return view_as<DiscordMessageReference>(this.GetObject("message_reference"));
    }

    public DiscordMessage GetReferencedMessage()
    {
        return view_as<DiscordMessage>(this.GetObject("referenced_message"));
    }

    public void Embed(DiscordEmbed embed)
    {
        if(!this.HasKey("embeds"))
            this.SetObject("embeds", new JSON_Array());

        JSON_Array embeds = this.GetEmbeds();
        embeds.PushObject(embed);
        this.SetObject("embeds", embeds);
    }
}