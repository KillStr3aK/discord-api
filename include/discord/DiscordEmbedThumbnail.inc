#if defined _DiscordEmbedThumbnail_included_
  #endinput
#endif
#define _DiscordEmbedThumbnail_included_

methodmap DiscordEmbedThumbnail < JSON_Object
{
	public DiscordEmbedThumbnail(const char[] url = "", int height, int width)
	{
		JSON_Object obj = new JSON_Object();
		obj.SetString("url", url);
		obj.SetInt("height", height);
		obj.SetInt("width", width);
		return view_as<DiscordEmbedThumbnail>(obj);
	}

	property int Height
	{
		public get() { return this.GetInt("height"); }
		public set(int value) { this.SetInt("height", value); }
	}

	property int Width
	{
		public get() { return this.GetInt("width"); }
		public set(int value) { this.SetInt("width", value); }
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