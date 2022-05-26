public int DiscordBot_StartTimer(Handle plugin, int params)
{
	DiscordBot bot = GetNativeCell(1);
	DiscordChannel channel = GetNativeCell(2);
	OnDiscordChannelMessage cb = view_as<OnDiscordChannelMessage>(GetNativeFunction(3));

	DataPack pack = new DataPack();
	pack.WriteCell(bot);
	pack.WriteCell(plugin);
	pack.WriteFunction(cb);
	pack.WriteCell(channel);

	ListenGetMessages(bot, channel, pack);
}

static void ListenGetMessages(DiscordBot bot, DiscordChannel channel, DataPack pack)
{
	char channelid[32];
	channel.GetID(channelid, sizeof(channelid));

	char lastmessageid[32];
	channel.GetLastMessageID(lastmessageid, sizeof(lastmessageid));

	char route[256];
	Format(route, sizeof(route), "channels/%s/messages?limit=%i&after=%s", channelid, 100, lastmessageid);
	SendRequest(bot, route, _, k_EHTTPMethodGET, OnListenChannelDataReceived, _, pack);
}

public int OnListenChannelDataReceived(Handle request, bool failure, int offset, int statuscode, DataPack pack)
{
	if(failure || (statuscode != 200 && statuscode != 204))
	{
		if(statuscode == 400 || statuscode == 429 || statuscode == 500)
		{
			// bad format or rate limit or server error handling
		}
		
		new DiscordException("OnListenChannelDataReceived - Fail %i %i", failure, statuscode);
		delete pack;
		delete request;
		return;
	}

	SteamWorks_GetHTTPResponseBodyCallback(request, ReceivedData, pack);
	delete request;
}

static stock Action GetMessageTimer(Handle timer, DataPack pack)
{
	pack.Reset();
	DiscordBot bot = pack.ReadCell();
	pack.ReadCell(); // read plugin handle to jump position..
	pack.ReadFunction(); // read function callback to jump position..
	DiscordChannel channel = pack.ReadCell();

	ListenGetMessages(bot, channel, pack);
}

static int ReceivedData(const char[] data, DataPack pack)
{
	pack.Reset();
	DiscordBot bot = pack.ReadCell();
	Handle plugin = pack.ReadCell();
	Function callback = pack.ReadFunction();
	DiscordChannel channel = pack.ReadCell();

	if(!bot.IsListeningToChannel(channel) || callback == INVALID_FUNCTION)
	{
		delete pack;
		return;
	}

	char channelid[32];
	JSON_Array messages = view_as<JSON_Array>(json_decode(data));

	for(int i = 0; i < messages.Length; i++)
	{
		DiscordMessage message = view_as<DiscordMessage>(messages.GetObject(i));
		message.GetChannelID(channelid, sizeof(channelid));

		if(!bot.IsListeningToChannelID(channelid))
		{
			delete pack;
			return;
		}

		if(i == 0)
		{
			char messageid[64];
			message.GetID(messageid, sizeof(messageid));
			channel.SetLastMessageID(messageid);
		}

		Call_StartFunction(plugin, callback);
		Call_PushCell(bot);
		Call_PushCell(channel);
		Call_PushCell(message);
		Call_Finish();
	}
	
	CreateTimer(bot.MessageCheckInterval, GetMessageTimer, pack);
}