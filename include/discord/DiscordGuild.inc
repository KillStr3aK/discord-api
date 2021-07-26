#if defined _DiscordGuild_included_
  #endinput
#endif
#define _DiscordGuild_included_

enum DiscordGuildVerificationLevel
{
    VerificationLevel_NONE = 0, /* unrestricted */
    LOW = 1, /* must have verified email on account */
    MEDIUM = 2, /* must be registered on Discord for longer than 5 minutes */
    HIGH = 3, /* must be a member of the server for longer than 10 minutes */
    VERY_HIGH = 4 /* must have a verified phone number */
}

enum DiscordGuildMessageNotificationLevel
{
    ALL_MESSAGES = 0, /* members will receive notifications for all messages by default */
    ONLY_MENTIONS = 1 /* members will receive notifications only for messages that @mention them by default */
}

enum DiscordGuildExplicitContentFilterLevel
{
    DISABLED = 0, /* media content will not be scanned */
    MEMBERS_WITHOUT_ROLES, /* 	media content sent by members without roles will be scanned */
    ALL_MEMBERS /* media content sent by all members will be scanned */
}

enum DiscordGuildMFALevel
{
    MFALevel_NONE = 0, /* guild has no MFA/2FA requirement for moderation actions */
    ELEVATED /* guild has a 2FA requirement for moderation actions */
}

enum DiscordGuildNSFWLevel
{
    DEFAULT = 0,
    EXPLICIT,
    SAFE,
    AGE_RESTRICTED
}

enum DiscordGuildPremiumTier
{
    TIER_NONE = 0, /* guild has not unlocked any Server Boost perks */
    TIER_1 = 1, /* guild has unlocked Server Boost level 1 perks */
    TIER_2 = 2, /* guild has unlocked Server Boost level 2 perks */
    TIER_3 = 3 /* guild has unlocked Server Boost level 3 perks */
}

enum DiscordGuildSystemChannelFlags
{
    SUPPRESS_JOIN_NOTIFICATIONS = (1 << 0), /* Suppress member join notifications */
    SUPPRESS_PREMIUM_SUBSCRIPTIONS = (1 << 1), /* Suppress server boost notifications */
    SUPPRESS_GUILD_REMINDER_NOTIFICATIONS = (1 << 2) /* Suppress server setup tips */
}

methodmap DiscordGuild < DiscordObject
{
    property bool IsOwner
    {
        public get() { return this.GetBool("owner"); }
    }

    property bool Widget
    {
        public get() { return this.GetBool("widget_enabled"); }
    }

    property bool IsLarge
    {
        public get() { return this.GetBool("large"); }
    }

    property bool IsUnavailable
    {
        public get() { return this.GetBool("unavailable"); }
    }

    property int AfkTimeout
    {
        public get() { return this.GetInt("afk_timeout"); }
    }

    property int MemberCount
    {
        public get() { return this.GetInt("member_count"); }
    }

    property int BoostCount
    {
        public get() { return this.GetInt("premium_subscription_count"); }
    }

    property DiscordGuildPremiumTier PremiumTier
    {
        public get() { return view_as<DiscordGuildPremiumTier>(this.GetInt("premium_tier")); }
    }

    property JSON_Array Roles
    {
        public get() { return view_as<JSON_Array>(this.GetObject("roles")); }
    }

    property JSON_Array Emojis
    {
        public get() { return view_as<JSON_Array>(this.GetObject("emojis")); }
    }

    property JSON_Array Members
    {
        public get() { return view_as<JSON_Array>(this.GetObject("members")); }
    }

    property JSON_Array Channels
    {
        public get() { return view_as<JSON_Array>(this.GetObject("channels")); }
    }

    property JSON_Array Features
    {
        public get() { return view_as<JSON_Array>(this.GetObject("features")); }
    }

    property DiscordGuildVerificationLevel VerificationLevel
    {
        public get() { return view_as<DiscordGuildVerificationLevel>(this.GetInt("verification_level")); }
    }

    property DiscordGuildMessageNotificationLevel NotificationLevel
    {
        public get() { return view_as<DiscordGuildMessageNotificationLevel>(this.GetInt("default_message_notifications")); }
    }

    property DiscordGuildExplicitContentFilterLevel ExplicitContentFilter
    {
        public get() { return view_as<DiscordGuildExplicitContentFilterLevel>(this.GetInt("explicit_content_filter")); }
    }

    property DiscordGuildMFALevel MFALevel
    {
        public get() { return view_as<DiscordGuildMFALevel>(this.GetInt("mfa_level")); }
    }

    property DiscordGuildNSFWLevel NSFWLevel
    {
        public get() { return view_as<DiscordGuildNSFWLevel>(this.GetInt("nsfw_level")); }
    }

    public JSON_Array GetRoles()
    {
        return this.Roles;
    }

    public JSON_Array GetEmojis()
    {
        return this.Emojis;
    }

    public JSON_Array GetMembers()
    {
        return this.Members;
    }

    public JSON_Array GetChannels()
    {
        return this.Channels;
    }

    public JSON_Array GetFeatures()
    {
        return this.Features;
    }

    public bool GetName(char[] output, int maxsize)
    {
        return this.GetString("name", output, maxsize);
    }

    public bool GetDescription(char[] output, int maxsize)
    {
        return this.GetString("description", output, maxsize);
    }

    public bool GetBanner(char[] output, int maxsize)
    {
        return this.GetString("banner", output, maxsize);
    }

    public bool GetIcon(char[] output, int maxsize)
    {
        return this.GetString("icon", output, maxsize);
    }

    public bool GetIconHash(char[] output, int maxsize)
    {
        return this.GetString("icon_hash", output, maxsize);
    }

    public bool GetSplash(char[] output, int maxsize)
    {
        return this.GetString("splash", output, maxsize);
    }

    public bool GetRegion(char[] output, int maxsize)
    {
        return this.GetString("region", output, maxsize);
    }

    public bool GetPreferredLanguage(char[] output, int maxsize)
    {
        return this.GetString("preferred_locale", output, maxsize);
    }

    public bool GetAfkChannelID(char[] output, int maxsize)
    {
        return this.GetString("afk_channel_id", output, maxsize);
    }
}