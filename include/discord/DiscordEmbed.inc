#if defined _DiscordEmbed_included_
  #endinput
#endif
#define _DiscordEmbed_included_

#include <discord/DiscordEmbedAuthor>
#include <discord/DiscordEmbedFooter>
#include <discord/DiscordEmbedProvider>
#include <discord/DiscordEmbedThumbnail>
#include <discord/DiscordEmbedImage>
#include <discord/DiscordEmbedVideo>
#include <discord/DiscordEmbedField>

#define MAX_EMBED_DESCRIPTION_LENGTH 4096 // https://discord.com/developers/docs/resources/channel#embed-limits-limits
#define MAX_EMBED_FIELDS 25

methodmap DiscordEmbed < JSON_Object
{
	public DiscordEmbed(DiscordEmbed embed = view_as<DiscordEmbed>(null))
	{
		if(embed == null)
			embed = view_as<DiscordEmbed>(new JSON_Object());

		return embed;
	}

	public void WithTitle(const char[] title)
	{
		this.SetString("title", title);
	}

	public bool GetTitle(char[] output, int maxsize)
	{
		return this.GetString("title", output, maxsize);
	}

	public void WithDescription(const char[] description)
	{
		this.SetString("description", description);
	}

	public bool GetDescription(char[] output, int maxsize)
	{
		return this.GetString("description", output, maxsize);
	}

	public void WithUrl(const char[] url)
	{
		this.SetString("url", url);
	}

	public bool GetUrl(char[] output, int maxsize)
	{
		return this.GetString("url", output, maxsize);
	}

	public void WithTimestamp(DateTime dateTime)
	{
		char szDate[DATE_LENGTH];
		dateTime.ToString(szDate, sizeof(szDate));
		this.SetString("timestamp", szDate);
	}

	public bool GetTimestamp(DateTime& out)
	{
		char szDate[DATE_LENGTH];
		this.GetString("timestamp", szDate, sizeof(szDate));
		return DateTime.TryParse(szDate, out);
	}

	public void SetType(const char[] type = "rich")
	{
		this.SetString("type", type);
	}

	public bool GetType(char[] output, int maxsize)
	{
		return this.GetString("type", output, maxsize);
	}

	public void SetColor(const char[] hexcode)
	{
		this.SetInt("color", HexToDec(hexcode));
	}

	public void GetColor(char[] output, int maxsize)
	{
		int color = this.GetInt("color");
		Format(output, maxsize, "#%X", color);
	}

	public void WithAuthor(DiscordEmbedAuthor author)
	{
		this.SetObject("author", author);
	}

	public DiscordEmbedAuthor GetAuthor()
	{
		return view_as<DiscordEmbedAuthor>(this.GetObject("author"));
	}

	public void WithFooter(DiscordEmbedFooter footer)
	{
		this.SetObject("footer", footer);
	}

	public DiscordEmbedFooter GetFooter()
	{
		return view_as<DiscordEmbedFooter>(this.GetObject("footer"));
	}

	public void WithImage(DiscordEmbedImage image)
	{
		this.SetObject("image", image);
	}

	public DiscordEmbedImage GetImage()
	{
		return view_as<DiscordEmbedImage>(this.GetObject("image"));
	}

	public void WithThumbnail(DiscordEmbedThumbnail thumbnail)
	{
		this.SetObject("thumbnail", thumbnail);
	}

	public DiscordEmbedThumbnail GetThumbnail()
	{
		return view_as<DiscordEmbedThumbnail>(this.GetObject("thumbnail"));
	}

	public void WithVideo(DiscordEmbedVideo video)
	{
		this.SetObject("video", video);
	}

	public DiscordEmbedVideo GetVideo()
	{
		return view_as<DiscordEmbedVideo>(this.GetObject("video"));
	}

	public void WithProvider(DiscordEmbedProvider provider)
	{
		this.SetObject("provider", provider);
	}

	public DiscordEmbedProvider GetProvider()
	{
		return view_as<DiscordEmbedProvider>(this.GetObject("provider"));
	}

	public JSON_Array GetFields()
	{
		return view_as<JSON_Array>(this.GetObject("fields"));
	}

	public void AddField(DiscordEmbedField field)
	{
		if(!this.HasKey("fields"))
			this.SetObject("fields", new JSON_Array());

		JSON_Array fields = this.GetFields();
		if(fields.Length < MAX_EMBED_FIELDS)
		{
			fields.PushObject(field);
			this.SetObject("fields", fields);
		} else LogError("DiscordEmbed cannot have more than %i fields!", MAX_EMBED_FIELDS);
	}

	public bool RemoveField(int index)
	{
		JSON_Array fields = this.GetFields();
		bool result = fields.Remove(index);
		this.SetObject("fields", fields);
		return result;
	}

	property int Color
	{
		public get() { return this.GetInt("color"); }
		public set(int value) { this.SetInt("color", value); }
	}

	property DateTime Timestamp
	{
		public get()
		{ 
			char szDate[DATE_LENGTH];
			this.GetString("timestamp", szDate, sizeof(szDate));
			return DateTime.Parse(szDate);
		}

		public set(DateTime value) { this.WithTimestamp(value); }
	}

	property DiscordEmbedAuthor Author
	{
		public get() { return this.GetAuthor(); }
		public set(DiscordEmbedAuthor value) { this.WithAuthor(value); }
	}

	property DiscordEmbedFooter Footer
	{
		public get() { return this.GetFooter(); }
		public set(DiscordEmbedFooter value) { this.WithFooter(value); }
	}

	property DiscordEmbedImage Image
	{
		public get() { return this.GetImage(); }
		public set(DiscordEmbedImage value) { this.WithImage(value); }
	}

	property DiscordEmbedThumbnail Thumbnail
	{
		public get() { return this.GetThumbnail(); }
		public set(DiscordEmbedThumbnail value) { this.WithThumbnail(value); }
	}

	property DiscordEmbedVideo Video
	{
		public get() { return this.GetVideo(); }
		public set(DiscordEmbedVideo value) { this.WithVideo(value); }
	}

	property DiscordEmbedProvider Provider
	{
		public get() { return this.GetProvider(); }
		public set(DiscordEmbedProvider value) { this.WithProvider(value); }
	}

	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}
}

public int HexToDec(const char[] hex)
{
	//i = 1 to skip the #
    int i = 1, result, value;
    while((value = IsHex(hex[i++])) != -1)
    {
        result = result * 16 + value;
    }

    return result
}
 
public int IsHex(char ch)
{
    if(!ch)
        return -1;
    
    if('0' <= ch <= '9')
        return ch - '0';
    
    ch &= ~0x20;
    if('A' <= ch <= 'F')
        return ch - 'A' + 10;
    
    return -1;
}