#if defined _DiscordEmbedField_included_
  #endinput
#endif
#define _DiscordEmbedField_included_

#define MAX_FIELD_NAME_LENGTH 256 // https://discord.com/developers/docs/resources/channel#embed-limits-limits
#define MAX_FIELD_VALUE_LENGTH 1024 // https://discord.com/developers/docs/resources/channel#embed-limits-limits

methodmap DiscordEmbedField < JSON_Object
{
	public DiscordEmbedField(const char[] name = "", const char[] value = "", bool inline = false)
	{
		JSON_Object obj = new JSON_Object();
		obj.SetString("name", name);
		obj.SetString("value", value);
		obj.SetBool("inline", inline);
		return view_as<DiscordEmbedField>(obj);
	}

	property bool Inline
	{
		public get() { return this.GetBool("inline"); }
		public set(bool value) { this.SetBool("inline", value); }
	}

	public bool GetName(char[] output, int maxsize)
	{
		return this.GetString("name", output, maxsize);
	}

	public void SetName(const char[] name)
	{
		this.SetString("name", name);
	}

	public bool GetValue(char[] output, int maxsize)
	{
		return this.GetString("value", output, maxsize);
	}

	public void SetValue(const char[] value)
	{
		this.SetString("value", value);
	}

	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}
}