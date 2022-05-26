public int DiscordBot_ModifyChannel(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel from = GetNativeCell(2);
	DiscordChannel to = GetNativeCell(3);
	OnDiscordChannelModified cb = view_as<OnDiscordChannelModified>(GetNativeFunction(4));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(5));
	pack.WriteCell(GetNativeCell(6));

	char channelID[32];
	from.GetID(channelID, sizeof(channelID));
	ModifyChannel(bot, channelID, to, pack);
}

public int DiscordBot_ModifyChannelID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel to = GetNativeCell(3);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	OnDiscordChannelModified cb = view_as<OnDiscordChannelModified>(GetNativeFunction(4));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(5));
	pack.WriteCell(GetNativeCell(6));
	ModifyChannel(bot, channelID, to, pack);
}

public int DiscordBot_DeleteChannel(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	OnDiscordChannelModified cb = view_as<OnDiscordChannelModified>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(4));
	pack.WriteCell(GetNativeCell(5));

	char channelID[32];
	channel.GetID(channelID, sizeof(channelID));
	DeleteChannel(bot, channelID, pack);
}

public int DiscordBot_DeleteChannelID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	OnDiscordChannelModified cb = view_as<OnDiscordChannelModified>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(4));
	pack.WriteCell(GetNativeCell(5));
	DeleteChannel(bot, channelID, pack);
}

public int DiscordBot_CreateDM(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordUser user = GetNativeCell(2);

	char userid[64];
	user.GetID(userid, sizeof(userid));
	CreateDM(bot, userid);
}

public int DiscordBot_CreateDMID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char userid[64];
	GetNativeString(2, userid, sizeof(userid));
	CreateDM(bot, userid);
}

public int DiscordBot_GetChannel(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));

	OnGetDiscordChannel cb = view_as<OnGetDiscordChannel>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(GetNativeCell(4));
	pack.WriteCell(GetNativeCell(5));
	GetChannel(bot, channelID, pack);
}

static void ModifyChannel(DiscordBot bot, const char[] channelid, DiscordChannel to, DataPack pack)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s", channelid);
	SendRequest(bot, route, to, k_EHTTPMethodPATCH, OnDiscordDataReceived, _, pack);
}

static void DeleteChannel(DiscordBot bot, const char[] channelid, DataPack pack)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s", channelid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE, OnDiscordDataReceived, _, pack);
}

static void CreateDM(DiscordBot bot, const char[] userid)
{
	char route[64];
	Format(route, sizeof(route), "users/@me/channels");

	JSON_Object obj = new JSON_Object();
	obj.SetString("recipient_id", userid);
	SendRequest(bot, route, obj, k_EHTTPMethodPOST);
}

static void GetChannel(DiscordBot bot, const char[] channelid, DataPack pack)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s", channelid);
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnDiscordDataReceived, _, pack);
}