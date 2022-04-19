#if defined _DiscordEmbedProvider_included_
  #endinput
#endif
#define _DiscordEmbedProvider_included_

methodmap DiscordEmbedProvider < JSON_Object
{
	public DiscordEmbedProvider(const char[] name = "", const char[] url = "")
	{
		JSON_Object obj = new JSON_Object();
		obj.SetString("name", name);
		obj.SetString("url", url);
		return view_as<DiscordEmbedProvider>(obj);
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

	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}
}