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

#define BOT_TOKEN	""
#define GUILD_ID	""
#define USER_ID		""
#define CHANNEL_ID	""

DiscordBot discordBot = null;

public void OnPluginStart()
{
	discordBot = new DiscordBot(BOT_TOKEN);
	discordBot.GetGuild(GUILD_ID, true, OnGuildReceived);
	discordBot.GetChannel(CHANNEL_ID, OnChannelReceived);
}

public void OnChannelReceived(DiscordBot bot, DiscordChannel channel)
{
	char szChannelName[32];
	channel.GetName(szChannelName, sizeof(szChannelName));
	PrintToServer("current channel name: %s", szChannelName);

	channel.SetName("random new name");
	bot.ModifyChannel(channel, channel, INVALID_FUNCTION);

	bot.StartListeningToChannel(channel, OnMessageReceived);

	/* you shouldn't dispose the channel in this case because the bot is listening to it */
	//channel.Dispose();
}

/* Simple discord->ingame chat relay */
public void OnMessageReceived(DiscordBot bot, DiscordChannel channel, DiscordMessage message)
{
	if(message.Author.IsBot)
		return;

	DiscordUser user = message.GetAuthor();

	char szMessage[256];
	message.GetContent(szMessage, sizeof(szMessage));

	char szUsername[MAX_DISCORD_USERNAME_LENGTH];
	user.GetUsername(szUsername, sizeof(szUsername));

	char szDiscriminator[MAX_DISCORD_DISCRIMINATOR_LENGTH];
	user.GetDiscriminator(szDiscriminator, sizeof(szDiscriminator));

	PrintToChatAll("%s#%s: %s", szUsername, szDiscriminator, szMessage);
}

public void OnGuildReceived(DiscordBot bot, DiscordGuild guild)
{
	if(guild != null)
	{
		char guildid[64];
		guild.GetID(guildid, sizeof(guildid));
		bot.GetGuildMemberID(guildid, USER_ID, OnGuildUserReceived);

		/* Release guild resource */
		guild.Dispose();
	}
}

public void OnGuildUserReceived(DiscordBot bot, DiscordGuildUser user)
{
	char szUserNickname[MAX_DISCORD_NICKNAME_LENGTH];
	user.GetNickname(szUserNickname, sizeof(szUserNickname));
	PrintToServer("User nickname: %s", szUserNickname);

	/* Release user resource */
	user.Dispose();
}

public void OnPluginEnd()
{
	/* totally pointless there but nvm */
	discordBot.Dispose();
}