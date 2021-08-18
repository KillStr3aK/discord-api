public int DiscordBot_CreateReaction(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);
    DiscordEmoji emoji = GetNativeCell(4);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));
	CreateReaction(bot, channelID, messageID, emoji);
}

public int DiscordBot_DeleteOwnReaction(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);
    DiscordEmoji emoji = GetNativeCell(4);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));
    DeleteReaction(bot, channelID, messageID, emoji, null);
}

public int DiscordBot_DeleteReaction(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);
    DiscordEmoji emoji = GetNativeCell(4);
    DiscordUser user = GetNativeCell(5);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));
    DeleteReaction(bot, channelID, messageID, emoji, user);
}

public int DiscordBot_CreateReactionID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
	char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));

    DiscordEmoji emoji = GetNativeCell(4);
	CreateReaction(bot, channelID, messageID, emoji);
}

public int DiscordBot_DeleteOwnReactionID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));

    DiscordEmoji emoji = GetNativeCell(4);
    DeleteReaction(bot, channelID, messageID, emoji, null);
}

public int DiscordBot_DeleteReactionID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));

    DiscordEmoji emoji = GetNativeCell(4);
    DiscordUser user = GetNativeCell(5);
    DeleteReaction(bot, channelID, messageID, emoji, user);
}

public int DiscordBot_DeleteAllReactions(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordChannel channel = GetNativeCell(2);
    DiscordMessage message = GetNativeCell(3);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));

    DeleteAllReactions(bot, channelID, messageID, null);
}

public int DiscordBot_DeleteAllReactionsID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);

    char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));

    DeleteAllReactions(bot, channelID, messageID, null);
}

public int DiscordBot_DeleteAllReactionsEmoji(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordChannel channel = GetNativeCell(2);
    DiscordMessage message = GetNativeCell(3);
    DiscordEmoji emoji = GetNativeCell(4);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));

    DeleteAllReactions(bot, channelID, messageID, emoji);
}

public int DiscordBot_DeleteAllReactionsEmojiID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordEmoji emoji = GetNativeCell(4);

    char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));

    DeleteAllReactions(bot, channelID, messageID, emoji);
}

static void CreateReaction(DiscordBot bot, const char[] channelid, const char[] messageid, DiscordEmoji emoji)
{
    char emojiName[48];
    emoji.GetName(emojiName, sizeof(emojiName));

	char route[128];
	Format(route, sizeof(route), "channels/%s/messages/%s/reactions/%s/@me", channelid, messageid, emojiName);
	SendRequest(bot, route, _, k_EHTTPMethodPUT);
}

static void DeleteReaction(DiscordBot bot, const char[] channelid, const char[] messageid, DiscordEmoji emoji, DiscordUser user)
{
    char emojiName[48];
    emoji.GetName(emojiName, sizeof(emojiName));

    char route[128];
    if(user == null) //null => delete own reaction
	    Format(route, sizeof(route), "channels/%s/messages/%s/reactions/%s/@me", channelid, messageid, emojiName);
    else {
        char userID[32];
        user.GetID(userID, sizeof(userID));
        Format(route, sizeof(route), "channels/%s/messages/%s/reactions/%s/%s", channelid, messageid, emojiName, userID);
    }

	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}

static void DeleteAllReactions(DiscordBot bot, const char[] channelid, const char[] messageid, DiscordEmoji emoji)
{
    char route[128];
    if(emoji == null)
    {
        Format(route, sizeof(route), "channels/%s/messages/%s/reactions", channelid, messageid);
    } else {
        char emojiName[48];
        emoji.GetName(emojiName, sizeof(emojiName));
        Format(route, sizeof(route), "channels/%s/messages/%s/reactions/%s", channelid, messageid, emojiName);
    }

    SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}