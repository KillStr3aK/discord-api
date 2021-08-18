public int DiscordBot_ModifyChannel(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordChannel from = GetNativeCell(2);
    DiscordChannel to = GetNativeCell(3);

    char channelID[32];
	from.GetID(channelID, sizeof(channelID));
    ModifyChannel(bot, channelID, to);
}

public int DiscordBot_ModifyChannelID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordChannel to = GetNativeCell(3);

    char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));
    ModifyChannel(bot, channelID, to);
}

public int DiscordBot_DeleteChannel(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    DiscordChannel channel = GetNativeCell(2);

    char channelID[32];
	channel.GetID(channelID, sizeof(channelID));
    DeleteChannel(bot, channelID);
}

public int DiscordBot_DeleteChannelID(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);

    char channelID[32];
	GetNativeString(2, channelID, sizeof(channelID));
    DeleteChannel(bot, channelID);
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

static void ModifyChannel(DiscordBot bot, const char[] channelid, DiscordChannel to)
{
	char route[64];
	Format(route, sizeof(route), "channels/%s", channelid);
	SendRequest(bot, route, to, k_EHTTPMethodPATCH);
}

static void DeleteChannel(DiscordBot bot, const char[] channelid)
{
    char route[64];
	Format(route, sizeof(route), "channels/%s", channelid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}

static void CreateDM(DiscordBot bot, const char[] userid)
{
    char route[64];
	Format(route, sizeof(route), "users/@me/channels");

    JSON_Object obj = new JSON_Object();
    obj.SetString("recipient_id", userid);
	SendRequest(bot, route, obj, k_EHTTPMethodPOST);
}