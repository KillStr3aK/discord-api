#include <sourcemod>
#include <discord>

#pragma tabsize 0;
#pragma newdecls required;
#pragma semicolon 1;

#include "discord/Message.sp"
#include "discord/Reaction.sp"
#include "discord/User.sp"
#include "discord/Channel.sp"
#include "discord/Guild.sp"

#define API_VERSION 6

public Plugin myinfo = 
{
	name = "Discord API",
	author = "Nexd",
	description = "This library is limited to the basic REST API that Discord provides.",
	version = "1.0",
	url = "https://github.com/KillStr3aK"
};

public APLRes AskPluginLoad2(Handle myself, bool late, char[] error, int err_max)
{
	CreateNative("DiscordBot.CreateGuild", DiscordBot_CreateGuild);

	CreateNative("DiscordBot.AddRole", DiscordBot_AddRole);
	CreateNative("DiscordBot.RemoveRole", DiscordBot_RemoveRole);

	CreateNative("DiscordBot.AddRoleID", DiscordBot_AddRoleID);
	CreateNative("DiscordBot.RemoveRoleID", DiscordBot_RemoveRoleID);

	CreateNative("DiscordBot.CreateDM", DiscordBot_CreateDM);
	CreateNative("DiscordBot.CreateDMID", DiscordBot_CreateDMID);

	CreateNative("DiscordBot.ModifySelf", DiscordBot_ModifySelf);

	CreateNative("DiscordBot.DeleteChannel", DiscordBot_DeleteChannel);
	CreateNative("DiscordBot.DeleteChannelID", DiscordBot_DeleteChannelID);

	CreateNative("DiscordBot.ModifyChannel", DiscordBot_ModifyChannel);
	CreateNative("DiscordBot.ModifyChannelID", DiscordBot_ModifyChannelID);

	CreateNative("DiscordBot.SendMessageToChannel", DiscordBot_SendMessageToChannel);
	CreateNative("DiscordBot.SendMessageToChannelID", DiscordBot_SendMessageToChannelID);

	CreateNative("DiscordBot.EditMessage", DiscordBot_EditMessage);
	CreateNative("DiscordBot.EditMessageID", DiscordBot_EditMessageID);

	CreateNative("DiscordBot.PinMessage", DiscordBot_PinMessage);
	CreateNative("DiscordBot.PinMessageID", DiscordBot_PinMessageID);

	CreateNative("DiscordBot.UnpinMessage", DiscordBot_UnpinMessage);
	CreateNative("DiscordBot.UnpinMessageID", DiscordBot_UnpinMessageID);

	CreateNative("DiscordBot.DeleteMessagesBulk", DiscordBot_DeleteMessagesBulk);
	CreateNative("DiscordBot.DeleteMessage", DiscordBot_DeleteMessage);
	CreateNative("DiscordBot.DeleteMessageID", DiscordBot_DeleteMessageID);
	
	CreateNative("DiscordBot.CreateReaction", DiscordBot_CreateReaction);
	CreateNative("DiscordBot.CreateReactionID", DiscordBot_CreateReactionID);

	CreateNative("DiscordBot.DeleteOwnReaction", DiscordBot_DeleteOwnReaction);
	CreateNative("DiscordBot.DeleteOwnReactionID", DiscordBot_DeleteOwnReactionID);

	CreateNative("DiscordBot.DeleteReaction", DiscordBot_DeleteReaction);
	CreateNative("DiscordBot.DeleteReactionID", DiscordBot_DeleteReactionID);

	CreateNative("DiscordBot.DeleteAllReactions", DiscordBot_DeleteAllReactions);
	CreateNative("DiscordBot.DeleteAllReactionsID", DiscordBot_DeleteAllReactionsID);

	CreateNative("DiscordBot.DeleteAllReactionsEmoji", DiscordBot_DeleteAllReactionsEmoji);
	CreateNative("DiscordBot.DeleteAllReactionsEmojiID", DiscordBot_DeleteAllReactionsEmojiID);
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
	Format(szEndpoint, sizeof(szEndpoint), "https://discord.com/api/v%i/%s/", API_VERSION, route);

	DiscordRequest request = new DiscordRequest(szEndpoint, method);
	request.Timeout = 30;
	request.SetCallbacks(OnRequestCompletedCb, _, OnDataReceivedCb);
	request.SetBot(bot);
	request.SetJsonBody(json);
	request.SetContentSize();
	request.Send();
}