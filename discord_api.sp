#include <sourcemod>
#include <discord>

#pragma tabsize 0;
#pragma newdecls required;
#pragma semicolon 1;

#include "discord/Message.sp"
#include "discord/Reaction.sp"

public Plugin myinfo = 
{
	name = "",
	author = "Nexd",
	description = "",
	version = "1.0",
	url = "https://github.com/KillStr3aK"
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	CreateNative("DiscordBot.SendMessageToChannel", DiscordBot_SendMessageToChannel);
	CreateNative("DiscordBot.SendMessageToChannelID", DiscordBot_SendMessageToChannelID);

	CreateNative("DiscordBot.DeleteMessagesBulk", DiscordBot_DeleteMessagesBulk);
	CreateNative("DiscordBot.DeleteMessage", DiscordBot_DeleteMessage);
	CreateNative("DiscordBot.DeleteMessageID", DiscordBot_DeleteMessageID);
	
	CreateNative("DiscordBot.CreateReaction", DiscordBot_CreateReaction);
	CreateNative("DiscordBot.CreateReactionID", DiscordBot_CreateReactionID);

	CreateNative("DiscordBot.DeleteOwnReaction", DiscordBot_DeleteOwnReaction);
	CreateNative("DiscordBot.DeleteOwnReactionID", DiscordBot_DeleteOwnReactionID);

	CreateNative("DiscordBot.DeleteReaction", DiscordBot_DeleteReaction);
	CreateNative("DiscordBot.DeleteReactionID", DiscordBot_DeleteReactionID);
	RegPluginLibrary("Discord-API");
	return APLRes_Success;
}

void SendRequest(DiscordBot bot, const char[] route, JSON_Object json = null, EHTTPMethod method = k_EHTTPMethodGET, SteamWorksHTTPDataReceived OnDataReceivedCb = INVALID_FUNCTION, SteamWorksHTTPRequestCompleted OnRequestCompletedCb = INVALID_FUNCTION)
{
	if(OnRequestCompletedCb == INVALID_FUNCTION)
	{
		OnRequestCompletedCb = OnHTTPRequestComplete; // include/discord/DiscordRequest.inc#L8
	}
	
	if(OnDataReceivedCb == INVALID_FUNCTION)
	{
		OnDataReceivedCb = OnHTTPDataReceive; // include/discord/DiscordRequest.inc#L10
	}

	char szEndpoint[256];
	Format(szEndpoint, sizeof(szEndpoint), "https://discord.com/api/%s", route);

	DiscordRequest request = new DiscordRequest(szEndpoint, method);
	request.Timeout = 30;
	request.SetCallbacks(OnRequestCompletedCb, _, OnDataReceivedCb);
	request.SetBot(bot);
	request.SetJsonBody(json);
	request.SetContentSize();
	request.Send();
}