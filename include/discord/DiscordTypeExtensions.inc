#if defined _DiscordTypeExtensions_included_
  #endinput
#endif
#define _DiscordTypeExtensions_included_

methodmap DiscordRoleList < JSON_Array
{
	/**
	* Release resources
	*/
	public void Dispose()
	{
		if(this == null)
			return;

		this.Cleanup();
		delete this;
	}	
}