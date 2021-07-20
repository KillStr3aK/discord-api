#if defined _DiscordEmoji_included_
  #endinput
#endif
#define _DiscordEmoji_included_

methodmap DiscordEmoji < DiscordObject
{
    property JSON_Array Roles
    {
        public get() { return view_as<JSON_Array>(this.GetObject("roles"));}
    }

    property DiscordUser User
    {
        public get() { return view_as<DiscordUser>(this.GetObject("user")); }
    }

    property bool RequireColons
    {
        public get() { return this.GetBool("require_colons"); }
    }

    property bool Managed
    {
        public get() { return this.GetBool("managed"); }
    }

    property bool Animated
    {
        public get() { return this.GetBool("animated"); }
    }

    property bool Available
    {
        public get() { return this.GetBool("available"); }
    }

    public bool GetName(char[] output, int maxsize)
    {
        return this.GetString("name", output, maxsize);
    }
}