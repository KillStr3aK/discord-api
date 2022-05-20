#include <sourcemod>
#include <discord>

#pragma tabsize 0;
#pragma newdecls required;
#pragma semicolon 1;

public Plugin myinfo = 
{
	name = "Discord Bot Example Callbacks",
	author = "Nexd",
	description = "Doing random things",
	version = "1.0",
	url = "https://github.com/KillStr3aK"
};

#define BOT_TOKEN ""
#define GUILD_ID ""

public void OnPluginStart()
{
	DiscordBot bot = new DiscordBot(BOT_TOKEN);
	bot.GetGuild(GUILD_ID, true, OnGuild);
	bot.Dispose();
}

public void OnGuild(DiscordGuild guild)
{
	char szGuildName[32];
	guild.GetName(szGuildName, sizeof(szGuildName));
	PrintToChatAll("%s", szGuildName);

	guild.Dispose();
}