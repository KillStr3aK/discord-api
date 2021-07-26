#include <sourcemod>
#include <discord>

#pragma tabsize 0;
#pragma newdecls required;
#pragma semicolon 1;

public Plugin myinfo = 
{
	name = "Discord Bot Example",
	author = "Nexd",
	description = "Doing random things",
	version = "1.0",
	url = "https://github.com/KillStr3aK"
};

#define BOT_TOKEN ""

public void OnPluginStart()
{
	DiscordBot bot = new DiscordBot(BOT_TOKEN);

/* Send a random message with embed */
	DiscordMessage message = new DiscordMessage("Aye!");
	DiscordEmbed embed = new DiscordEmbed();
	embed.WithDescription("Random Description");
	embed.WithAuthor(new DiscordEmbedAuthor("Example Bot", "https://github.com/KillStr3aK"));
	embed.WithFooter(new DiscordEmbedFooter("NEXD @ Eternar"));
	message.Embed(embed);

	bot.SendMessageToChannelID("866539462401982514", message);
/* -- */

/* Create reaction */
	bot.CreateReactionID("866539462401982514", "869072008464441405", DiscordEmoji.FromName(":100:"));
/* -- */

/* Delete animated custom reaction that was created by this bot */
	bot.DeleteOwnReactionID("866539462401982514", "869072008464441405", DiscordEmoji.FromName("a:heartrainbow:842923225397985340"));
/* -- */

/* Delete message */
	bot.DeleteMessageID("866539462401982514", "869047387413413888");
/* -- */

	bot.Dispose();
}
