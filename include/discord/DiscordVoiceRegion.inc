#if defined _DiscordVoiceRegion_included_
  #endinput
#endif
#define _DiscordVoiceRegion_included_

methodmap DiscordVoiceRegion < JSON_Object
{
    property bool VipOnly
    {
        public get() { return this.GetBool("vip"); }
    }

    property bool Optimal
    {
        public get() { return this.GetBool("optimal"); }
    }

    property bool Deprecated
    {
        public get() { return this.GetBool("deprecated"); }
    }

    property bool Custom
    {
        public get() { return this.GetBool("custom"); }
    }

    public bool GetName(char[] output, int maxsize)
    {
        return this.GetString("name", output, maxsize);
    }

    public bool GetId(char[] output, int maxsize)
    {
        return this.GetString("id", output, maxsize);
    }
}