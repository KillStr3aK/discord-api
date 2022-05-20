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
#define USER_ID ""

DiscordBot discordBot = null;
DiscordGuild discordGuild = null;

public void OnPluginStart()
{
	discordBot = new DiscordBot(BOT_TOKEN);
	discordBot.GetGuild(GUILD_ID, true, OnGuildReceived);
}

public void OnGuildReceived(DiscordGuild guild)
{
	discordGuild = guild;

	if(discordGuild != null)
	{
		char guildid[64];
		discordGuild.GetID(guildid, sizeof(guildid));
		discordBot.GetGuildMemberID(guildid, USER_ID, OnGuildUserReceived);
	}
}

public void OnGuildUserReceived(DiscordGuildUser user)
{
	char szUserNickname[MAX_DISCORD_NICKNAME_LENGTH];
	user.GetNickname(szUserNickname, sizeof(szUserNickname));
	PrintToChatAll("User nickname: %s", szUserNickname);

	user.Dispose();
}

public void OnPluginEnd()
{
	/*
		totally pointless there but nvm
	*/
	discordGuild.Dispose();
	discordBot.Dispose();
}
