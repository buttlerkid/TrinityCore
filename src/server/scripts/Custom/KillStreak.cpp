#include "ScriptPCH.h"

class System_OnPvPKill : public PlayerScript
{
	public:
		System_OnPvPKill() : PlayerScript("System_OnPvPKill") {}

	struct SystemInfo
	{
		uint32 KillStreak;
		uint32 LastGUIDKill;
	};

static std::map<uint32, SystemInfo> KillingStreak;
	
void OnPvPKill(Player *pKiller, Player *pVictim)
	{
		uint32 kGUID; 
		uint32 vGUID;
		kGUID = pKiller->GetGUID();
		vGUID = pVictim->GetGUID();	
		if(kGUID == vGUID)
		{
			return;
		}
		if(KillingStreak[kGUID].LastGUIDKill == vGUID)
		{
			return;
		}
		
		KillingStreak[kGUID].KillStreak++;
		KillingStreak[vGUID].KillStreak = 0;
		KillingStreak[kGUID].LastGUIDKill = vGUID;
		KillingStreak[vGUID].LastGUIDKill = 0;
		
		switch(KillingStreak[kGUID].KillStreak)
		{
			case 10:
			char msg[500];
			sprintf(msg, "[PvP System]: %s killed %s and is on a 10 kill streak. ", pKiller->GetName(), pVictim->GetName());
			sWorld.SendWorldText(LANG_SYSTEMMESSAGE, msg);
			break;
		}
	}
};

void AddSC_System()
{
    new System_OnPvPKill;
}