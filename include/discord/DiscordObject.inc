#if defined _DiscordObject_included_
  #endinput
#endif
#define _DiscordObject_included_

/* Discord objects that has an unique snowflake inherits from this methodmap. */
methodmap DiscordObject < JSON_Object
{
    public bool GetID(char[] output, int maxsize)
	{
		return this.GetString("id", output, maxsize);
	}

	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}
}