#include <sourcemod>
#include <discord>

#pragma tabsize 0;
#pragma newdecls required;
#pragma semicolon 1;

public Plugin myinfo = 
{
	name = "Discord WebHook Example",
	author = "Nexd",
	description = "",
	version = "1.0",
	url = "https://github.com/KillStr3aK"
};

//webhook
#define ENDPOINT ""
#define CONTENT ""
#define USERNAME ""
#define AVATAR ""

//embed
#define COLOR "#5D00FF"
#define TITLE ""
#define WITH_TIMESTAMP

//author
#define AUTHOR_NAME ""
#define AUTHOR_URL ""
#define AUTHOR_ICON ""

//footer
#define FOOTER_TEXT ""
#define FOOTER_ICON ""

#define THUMBNAIL_LINK ""
#define THUMBNAIL_HEIGHT 200
#define THUMBNAIL_WIDTH 300

#define IMAGE_LINK ""
#define IMAGE_HEIGHT 200
#define IMAGE_WIDTH 300

public void OnPluginStart()
{
	DiscordWebHook hook = new DiscordWebHook(ENDPOINT);
	hook.SetContent(CONTENT);
	hook.SetUsername(USERNAME);
	hook.SetAvatar(AVATAR);

	DiscordEmbed embed = new DiscordEmbed();
	embed.SetColor(COLOR);
	embed.WithTitle(TITLE);
	embed.WithAuthor(new DiscordEmbedAuthor(AUTHOR_NAME, AUTHOR_URL, AUTHOR_ICON));
	embed.WithFooter(new DiscordEmbedFooter(FOOTER_TEXT, FOOTER_ICON));

#if defined WITH_TIMESTAMP
	embed.WithTimestamp(new DateTime(DateTime_Now) - TimeSpan.FromHours(2)); //timezone things
#endif

	embed.WithImage(new DiscordEmbedImage(IMAGE_LINK, IMAGE_HEIGHT, IMAGE_WIDTH));
	embed.WithThumbnail(new DiscordEmbedThumbnail(THUMBNAIL_LINK, THUMBNAIL_HEIGHT, THUMBNAIL_WIDTH));

	for(int i = 0; i < 25; i++)
	{
		bool inline = i % 2 == 0; // i % 2 is used to 'randomize' inline
		embed.AddField(new DiscordEmbedField("FIELD", "VALUE", inline));
	}
	
	hook.Embed(embed);
	hook.Send();
	hook.Dispose();
}
