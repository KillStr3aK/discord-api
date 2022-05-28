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

public int DiscordBot_EditMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage from = GetNativeCell(3);
	DiscordMessage to = GetNativeCell(4);

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

	char messageID[32];
	from.GetID(messageID, sizeof(messageID));
	EditMessage(bot, channelID, messageID, to);
}

public int DiscordBot_EditMessageID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordMessage to = GetNativeCell(4);
	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	char messageID[32];
	GetNativeString(3, messageID, sizeof(messageID));
	EditMessage(bot, channelID, messageID, to);
}

public int DiscordBot_PinMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

	char messageID[32];
	message.GetID(messageID, sizeof(messageID));
	PinMessage(bot, channelID, messageID);
}

public int DiscordBot_PinMessageID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	char messageID[32];
	GetNativeString(3, messageID, sizeof(messageID));
	PinMessage(bot, channelID, messageID);
}

public int DiscordBot_UnpinMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

	char messageID[32];
	message.GetID(messageID, sizeof(messageID));
	UnpinMessage(bot, channelID, messageID);
}

public int DiscordBot_UnpinMessageID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	char messageID[32];
	GetNativeString(3, messageID, sizeof(messageID));
	UnpinMessage(bot, channelID, messageID);
}

public int DiscordBot_GetChannelMessages(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);

	char around[32];
	GetNativeString(3, around, sizeof(around));

	char before[32];
	GetNativeString(4, before, sizeof(before));

	char after[32];
	GetNativeString(5, after, sizeof(after));

	int limit = GetNativeCell(6);

	OnGetDiscordChannelMessages cb = view_as<OnGetDiscordChannelMessages>(GetNativeFunction(7));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(8));
	pack.WriteCell(GetNativeCell(9));

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));
	GetChannelMessages(bot, channelID, around, before, after, limit, pack);
}

public int DiscordBot_GetChannelMessagesID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	char around[32];
	GetNativeString(3, around, sizeof(around));

	char before[32];
	GetNativeString(4, before, sizeof(before));

	char after[32];
	GetNativeString(5, after, sizeof(after));

	int limit = GetNativeCell(6);

	OnGetDiscordChannelMessages cb = view_as<OnGetDiscordChannelMessages>(GetNativeFunction(7));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(8));
	pack.WriteCell(GetNativeCell(9));
	GetChannelMessages(bot, channelID, around, before, after, limit, pack);
}

public int DiscordBot_GetChannelMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);

	char messageID[32];
	GetNativeString(3, messageID, sizeof(messageID));

	OnGetDiscordChannelMessage cb = view_as<OnGetDiscordChannelMessage>(GetNativeFunction(4));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(5));
	pack.WriteCell(GetNativeCell(6));

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));
	GetChannelMessage(bot, channelID, messageID, pack);
}

public int DiscordBot_GetChannelMessageID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	char messageID[32];
	GetNativeString(3, messageID, sizeof(messageID));

	OnGetDiscordChannelMessage cb = view_as<OnGetDiscordChannelMessage>(GetNativeFunction(4));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(5));
	pack.WriteCell(GetNativeCell(6));
	GetChannelMessage(bot, channelID, messageID, pack);
}

public int DiscordBot_GetPinnedMessages(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	OnGetDiscordChannelPinnedMessages cb = view_as<OnGetDiscordChannelPinnedMessages>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(4));
	pack.WriteCell(GetNativeCell(5));

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));
	GetPinnedMessages(bot, channelID, pack);
}

public int DiscordBot_GetPinnedMessagesID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	OnGetDiscordChannelPinnedMessages cb = view_as<OnGetDiscordChannelPinnedMessages>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(4));
	pack.WriteCell(GetNativeCell(5));
	GetPinnedMessages(bot, channelID, pack);
}

public int DiscordBot_CrosspostMessage(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	DiscordMessage message = GetNativeCell(3);

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));

	char messageID[32];
	message.GetID(messageID, sizeof(messageID));

	CrosspostMessage(bot, channelID, messageID);
}

static void SendMessage(DiscordBot bot, const char[] channelid, DiscordMessage message)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages", channelid);
	SendRequest(bot, route, message, k_EHTTPMethodPOST);
}

static void DeleteMessage(DiscordBot bot, const char[] channelid, const char[] messageid)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages/%s", channelid, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}

static void EditMessage(DiscordBot bot, const char[] channelid, const char[] messageid, DiscordMessage message)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages/%s", channelid, messageid);
	SendRequest(bot, route, message, k_EHTTPMethodPATCH);
}

static void PinMessage(DiscordBot bot, const char[] channelid, const char[] messageid)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/pins/%s", channelid, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodPUT);
}

static void UnpinMessage(DiscordBot bot, const char[] channelid, const char[] messageid)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/pins/%s", channelid, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}

static void GetChannelMessages(DiscordBot bot, const char[] channelid, const char[] around, const char[] before, const char[] after, int limit, DataPack pack)
{
	char route[256];
	Format(route, sizeof(route), "channels/%s/messages?around=%s&before=%s&after=%s&limit=%i", channelid, around, before, after, limit);
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnDiscordDataReceived, _, pack);
}

static void GetChannelMessage(DiscordBot bot, const char[] channelid, const char[] messageid, DataPack pack)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/messages/%s", channelid, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnDiscordDataReceived, _, pack);
}

static void GetPinnedMessages(DiscordBot bot, const char[] channelid, DataPack pack)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s/pins", channelid);
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnDiscordDataReceived, _, pack);
}

static void CrosspostMessage(DiscordBot bot, const char[] channelid, const char[] messageid)
{
	char route[128];
	Format(route, sizeof(route), "channels/%s/messages/%s/crosspost", channelid, messageid);
	SendRequest(bot, route, _, k_EHTTPMethodPOST);
}