#if defined _DiscordAttachment_included_
  #endinput
#endif
#define _DiscordAttachment_included_

methodmap DiscordAttachment < DiscordObject
{
    property int Height
    {
        public get() { return this.GetInt("height"); }
    }

    property int Width
    {
        public get() { return this.GetInt("width"); }
    }

    property int Size
    {
        public get() { return this.GetInt("size"); }
    }

    public bool GetUrl(char[] output, int maxsize)
	{
		return this.GetString("url", output, maxsize);
	}

    public bool GetFilename(char[] output, int maxsize)
	{
		return this.GetString("filename", output, maxsize);
	}
}