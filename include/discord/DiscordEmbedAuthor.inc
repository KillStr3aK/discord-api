#if defined _DiscordEmbedAuthor_included_
  #endinput
#endif
#define _DiscordEmbedAuthor_included_

#define MAX_AUTHOR_NAME_LENGTH 256 // https://discord.com/developers/docs/resources/channel#embed-limits-limits

methodmap DiscordEmbedAuthor < JSON_Object
{
	public DiscordEmbedAuthor(const char[] name = "", const char[] url = "", const char[] iconUrl = "")
	{
		JSON_Object obj = new JSON_Object();
		obj.SetString("name", name);
		obj.SetString("url", url);
		obj.SetString("icon_url", iconUrl);
		return view_as<DiscordEmbedAuthor>(obj);
	}

	public bool GetName(char[] output, int maxsize)
	{
		return this.GetString("name", output, maxsize);
	}

	public void SetName(const char[] name)
	{
		this.SetString("name", name);
	}

	public bool GetUrl(char[] output, int maxsize)
	{
		return this.GetString("url", output, maxsize);
	}

	public void SetUrl(const char[] url)
	{
		this.SetString("url", url);
	}

	public bool GetIcon(char[] output, int maxsize)
	{
		return this.GetString("icon_url", output, maxsize);
	}

	public void SetIcon(const char[] iconUrl)
	{
		this.SetString("icon_url", iconUrl);
	}

	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}
}