#if defined _DiscordUser_included_
  #endinput
#endif
#define _DiscordUser_included_

enum DiscordUserFlags
{
	UserFlags_None = 0, /* None */
	Employee = (1 << 0), /* Discord Employee */
	Partner = (1 << 1), /* Partner or Partnered Server Owner */
	HypeSquad = (1 << 2), /* HypeSquad Events */
	BugHunter1 = (1 << 3), /* Bug Hunter Level 1 */
	HouseBravery = (1 << 6), /* House Bravery */
	HouseBrilliance = (1 << 7), /* House Brilliance */
	HouseBalance = (1 << 8), /* House Balance */
	EarlySupporter = (1 << 9), /* Early Supporter */
	TeamUser = (1 << 10), /* Team User */
	BugHunter2 = (1 << 14), /* Bug Hunter Level 2 */
	VerifiedBot = (1 << 16), /* Verified Bot */
	VerifiedBotDeveloper = (1 << 17), /* Early Verified Bot Developer */
	CertifiedModerator = (1 << 18) /* Discord Certified Moderator */
}

enum DiscordPremiumTypes
{
	PremiumType_None = 0,
	NitroClassic = 1,
	Nitro = 2
}

#define MAX_DISCORD_USERNAME_LENGTH 32
#define MAX_DISCORD_DISCRIMINATOR_LENGTH 4

methodmap DiscordUser < DiscordObject
{
	property bool IsBot
	{
		public get() { return this.GetBool("bot"); }
	}

	property bool IsSystem
	{
		public get() { return this.GetBool("system"); }
	}

	property bool HasTwoFactor
	{
		public get() { return this.GetBool("mfa_enabled"); }
	}

	property bool IsVerified
	{
		public get() { return this.GetBool("verified"); }
	}

	/* DiscordUserFlags */
	property int Flags
	{
		public get() { return this.GetInt("flags"); }
	}

	/* DiscordUserFlags */
	property int PublicFlags
	{
		public get() { return this.GetInt("public_flags"); }
	}

	property DiscordPremiumTypes PremiumType
	{
		public get() { return view_as<DiscordPremiumTypes>(this.GetInt("premium_type")); }
	}

	public bool GetUsername(char[] output, int maxsize)
    {
        return this.GetString("username", output, maxsize);
    }

	public bool GetDiscriminator(char[] output, int maxsize)
    {
        return this.GetString("discriminator", output, maxsize);
    }

	public bool GetAvatar(char[] output, int maxsize)
    {
        return this.GetString("avatar", output, maxsize);
    }

	public bool GetLanguage(char[] output, int maxsize)
    {
        return this.GetString("locale", output, maxsize);
    }

	public bool GetEmail(char[] output, int maxsize)
    {
        return this.GetString("email", output, maxsize);
    }

	public bool GetMention(char[] output, int maxsize)
	{
		char szID[32];
		if(!this.GetID(szID, sizeof(szID)))
			return false;

		Format(szID, sizeof(szID), "<@%s>", szID);
		return true;
	}
}