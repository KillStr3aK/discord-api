public int DiscordBot_CreateGuild(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordGuild guild = GetNativeCell(2);
	CreateGuild(bot, guild);
}

public int DiscordBot_AddRole(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordGuild guild = GetNativeCell(2);
	DiscordUser user = GetNativeCell(3);
	DiscordRole role = GetNativeCell(4);

	char guildid[64];
	guild.GetID(guildid, sizeof(guildid));

	char userid[64];
	user.GetID(userid, sizeof(userid));

	char roleid[64];
	role.GetID(roleid, sizeof(roleid));
	AddRole(bot, guildid, userid, roleid);
}

public int DiscordBot_AddRoleID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char guildid[64];
	GetNativeString(2, guildid, sizeof(guildid));

	char userid[64];
	GetNativeString(3, userid, sizeof(userid));

	char roleid[64];
	GetNativeString(4, roleid, sizeof(roleid));
	AddRole(bot, guildid, userid, roleid);
}

public int DiscordBot_RemoveRole(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordGuild guild = GetNativeCell(2);
	DiscordUser user = GetNativeCell(3);
	DiscordRole role = GetNativeCell(4);

	char guildid[64];
	guild.GetID(guildid, sizeof(guildid));

	char userid[64];
	user.GetID(userid, sizeof(userid));

	char roleid[64];
	role.GetID(roleid, sizeof(roleid));
	RemoveRole(bot, guildid, userid, roleid);
}

public int DiscordBot_RemoveRoleID(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char guildid[64];
	GetNativeString(2, guildid, sizeof(guildid));

	char userid[64];
	GetNativeString(3, userid, sizeof(userid));

	char roleid[64];
	GetNativeString(4, roleid, sizeof(roleid));
	RemoveRole(bot, guildid, userid, roleid);
}

public int DiscordBot_GetGuild(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);

	char guildid[64];
	GetNativeString(2, guildid, sizeof(guildid));

	bool with_counts = GetNativeCell(3);
	OnGetDiscordGuild cb = view_as<OnGetDiscordGuild>(GetNativeFunction(4));

	DataPack pack = new DataPack();
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	GetGuild(bot, guildid, with_counts, pack);
}

static void CreateGuild(DiscordBot bot, DiscordGuild guild)
{
	char route[128];
	Format(route, sizeof(route), "guilds");
	SendRequest(bot, route, guild, k_EHTTPMethodPOST);
}

static void AddRole(DiscordBot bot, const char[] guildid, const char[] userid, const char[] roleid)
{
	char route[128];
	Format(route, sizeof(route), "guilds/%s/members/%s/roles/%s", guildid, userid, roleid);
	SendRequest(bot, route, _, k_EHTTPMethodPUT);
}

static void RemoveRole(DiscordBot bot, const char[] guildid, const char[] userid, const char[] roleid)
{
	char route[128];
	Format(route, sizeof(route), "guilds/%s/members/%s/roles/%s", guildid, userid, roleid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}

static void GetGuild(DiscordBot bot, const char[] guildid, bool with_counts, DataPack pack)
{
	with_counts = false;
	char route[128];
	Format(route, sizeof(route), "guilds/%s?with_counts=%s", guildid, with_counts ? "true" : "false");
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnGuildReceived, _, pack);
}

public int OnGuildReceived(Handle request, bool failure, int offset, int statuscode, DataPack pack)
{
	if(failure || (statuscode != 200 && statuscode != 204))
	{
		if(statuscode == 400 || statuscode == 429 || statuscode == 500)
		{
			// bad format or rate limit or server error handling
		}
		
		new DiscordException("OnGuildReceived - Fail %i %i", failure, statuscode);
		delete request;
		return;
	}

	SteamWorks_GetHTTPResponseBodyCallback(request, ReceivedGuildData, pack);
	delete request;
}

public int ReceivedGuildData(const char[] data, DataPack pack)
{
	pack.Reset();
	Handle plugin = pack.ReadCell();
	OnGetDiscordGuild callback = view_as<OnGetDiscordGuild>(pack.ReadFunction());
	delete pack;
	
	DiscordGuild guild = view_as<DiscordGuild>(json_decode(data));

	Call_StartFunction(plugin, callback);
	Call_PushCell(guild);
	Call_Finish();
}