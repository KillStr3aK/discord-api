public int DiscordBot_SendMessageToChannel(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);

	char szID[32];
	channel.GetID(szID, sizeof(szID));
	SendMessage(bot, szID, message);
}

public int DiscordBot_SendMessageToChannelID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	char channel[32];
	GetNativeString(2, channel, sizeof(channel));
	DiscordMessage message = GetNativeCell(3);
	SendMessage(bot, channel, message);
}

public int DiscordBot_DeleteMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

    char messageID[32];
    message.GetID(messageID, sizeof(messageID));
	DeleteMessage(bot, channelID, messageID);
}

public int DiscordBot_DeleteMessageID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

    char messageID[32];
    GetNativeString(3, messageID, sizeof(messageID));
	DeleteMessage(bot, channelID, messageID);
}

public int DiscordBot_DeleteMessagesBulk(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	char channelID[32];
    GetNativeString(2, channelID, sizeof(channelID));

	JSON_Array messages = GetNativeCell(3);

	char route[64];
	Format(route, sizeof(route), "channels/%s/messages/bulk-delete", channelID);
	SendRequest(bot, route, messages, k_EHTTPMethodPOST);
}

static void SendMessage(DiscordBot bot, const char[] channel, DiscordMessage message)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages", channel);
	SendRequest(bot, route, message, k_EHTTPMethodPOST);
}

static void DeleteMessage(DiscordBot bot, const char[] channel, const char[] messageid)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages/%s", channel, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}