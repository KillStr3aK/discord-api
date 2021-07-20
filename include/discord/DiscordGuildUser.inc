#if defined _DiscordGuildUser_included_
  #endinput
#endif
#define _DiscordGuildUser_included_

#include <discord/DiscordUser>

#define MAX_DISCORD_NICKNAME_LENGTH 32

methodmap DiscordGuildUser < JSON_Object
{
    public DiscordUser GetUser()
    {
        return view_as<DiscordUser>(this.GetObject("user"));
    }

    property bool IsDeaf
    {
        public get() { return this.GetBool("deaf"); }
    }

    property bool IsMute
    {
        public get() { return this.GetBool("mute"); }
    }

    property bool IsPending
    {
        public get() { return this.GetBool("pending"); }
    }

    public bool GetNickname(char[] output, int maxsize)
    {
        return this.GetString("nick", output, maxsize);
    }

    public bool GetJoinedDate(char[] buffer, int maxsize)
    {
        return this.GetString("joined_at", buffer, maxsize);
    }

    public bool GetJoinedDateTime(DateTime& out)
    {
        char szDate[DATE_LENGTH];
        this.GetString("joined_at", szDate, sizeof(szDate));
        return DateTime.TryParse(szDate, out);
    }

    public bool GetBoostingSince(char[] buffer, int maxsize)
    {
        return this.GetString("premium_since", buffer, maxsize);
    }

    public bool GetBoostingSinceDateTime(DateTime& out)
    {
        char szDate[DATE_LENGTH];
        this.GetString("premium_since", szDate, sizeof(szDate));
        return DateTime.TryParse(szDate, out);
    }

    public JSON_Array GetRoles()
    {
        return view_as<JSON_Array>(this.GetObject("roles"));
    }
}