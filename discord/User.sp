public int DiscordBot_ModifySelf(Handle plugin, int params)
{
    DiscordBot bot = GetNativeCell(1);
    char username[32];
    GetNativeString(2, username, sizeof(username));

    char avatar[128];
    GetNativeString(3, avatar, sizeof(avatar));
    ModifySelf(bot, username, avatar);
}

static void ModifySelf(DiscordBot bot, const char[] username, const char[] avatar)
{
    char route[64];
	Format(route, sizeof(route), "users/@me");

    JSON_Object obj = new JSON_Object();
    obj.SetString("username", username);
    if(strlen(avatar) > 0)
        obj.SetString("avatar", avatar);

	SendRequest(bot, route, obj, k_EHTTPMethodPATCH);
}