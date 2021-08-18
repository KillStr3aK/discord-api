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

static void CreateGuild(DiscordBot bot, DiscordGuild guild)
{
	char route[64];
	Format(route, sizeof(route), "guilds");
	SendRequest(bot, route, guild, k_EHTTPMethodPOST);
}

static void AddRole(DiscordBot bot, const char[] guildid, const char[] userid, const char[] roleid)
{
    char route[64];
	Format(route, sizeof(route), "guilds/%s/members/%s/roles/%s", guildid, userid, roleid);
	SendRequest(bot, route, _, k_EHTTPMethodPUT);
}

static void RemoveRole(DiscordBot bot, const char[] guildid, const char[] userid, const char[] roleid)
{
    char route[64];
	Format(route, sizeof(route), "guilds/%s/members/%s/roles/%s", guildid, userid, roleid);
	SendRequest(bot, route, _, k_EHTTPMethodDELETE);
}