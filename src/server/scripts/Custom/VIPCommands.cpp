/*
* Made By ???
* Error Fixed By Rochet2
* Released By Ghostcrawler
* Edited By Sinistah
*/

/* Insert Into World Database
INSERT INTO `command` VALUES ('vip mall', '1', '');
INSERT INTO `command` VALUES ('vip changerace', '1', '');
INSERT INTO `command` VALUES ('vip changefaction', '1', '');
INSERT INTO `command` VALUES ('vip maxskills', '1', '');
INSERT INTO `command` VALUES ('vip customize', '1', '');
INSERT INTO `command` VALUES ('vip tele', '1', '');
INSERT INTO `command` VALUES ('vip morph', '1', '');
INSERT INTO `command` VALUES ('vip demorph', '1', '')
*/

#include "ScriptMgr.h"
#include "ObjectMgr.h"
#include "MapManager.h"
#include "Chat.h"
#include "Common.h"

class vipcommands : public CommandScript
{
public:
    vipcommands() : CommandScript("vipcommands") { }

    ChatCommand* GetCommands() const
    {
        static ChatCommand vipCommandTable[] =

        {
            { "mall",	    SEC_PLAYER,     true, &HandleVipMallCommand,         "", NULL },
            { "changerace",    SEC_PLAYER,  false, &HandleChangeRaceCommand,             "", NULL },
			{ "changefaction",	SEC_PLAYER,  false, &HandleChangeFactionCommand,		"", NULL },
			{ "maxskills",	SEC_PLAYER,  false, &HandleMaxSkillsCommand,		"", NULL },
			{ "customize",	SEC_PLAYER,  false, &HandleCustomizeCommand,		"", NULL },
			{ "tele",           SEC_PLAYER,  false, &HandleTeleCommand,		"", NULL },
			{ "morph",           SEC_PLAYER,  false, &HandleMorphCommand,		"", NULL },
			{ "demorph",           SEC_PLAYER,  false, &HandleDemorphCommand,		"", NULL },
 
            { NULL,             0,                     false, NULL,                                           "", NULL }
        };
        static ChatCommand commandTable[] =
        {
            { "vip",	    SEC_PLAYER,   true, NULL,      "",  vipCommandTable},
	       { NULL,             0,                  false, NULL,                               "", NULL }
        };
        return commandTable;
    }


static bool HandleTeleCommand(ChatHandler* handler, const char* args)
    {
        if (!*args)
            return false;

        Player* me = handler->GetSession()->GetPlayer();

        // id, or string, or [name] Shift-click form |color|Htele:id|h[name]|h|r
        GameTele const* tele = handler->extractGameTeleFromLink((char*)args);

        if (!tele)
        {
            handler->SendSysMessage(LANG_COMMAND_TELE_NOTFOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        MapEntry const* map = sMapStore.LookupEntry(tele->mapId);
        if (!map || map->IsBattlegroundOrArena())
        {
            handler->SendSysMessage(LANG_CANNOT_TELE_TO_BG);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

        me->TeleportTo(tele->mapId, tele->position_x, tele->position_y, tele->position_z, tele->orientation);
        return true;
		}

static bool HandlevipCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

            me->Say("vip command?", LANG_UNIVERSAL);
            return true;
    }

static bool HandleMorphCommand(ChatHandler* handler, const char* args)
    {
        handler->GetSession()->GetPlayer()->SetDisplayId((uint32)atol((char*)args));
        return true;
    }

static bool HandleChangeRaceCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_RACE);
		handler->PSendSysMessage("Relog to change race of your character.");
        return true;
    }

static bool HandleChangeFactionCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CHANGE_FACTION);
		handler->PSendSysMessage("Relog to change faction of your character.");
        return true;
    }

static bool HandleMaxSkillsCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->UpdateSkillsToMaxSkillsForLevel();
		handler->PSendSysMessage("Your weapon skills are now maximized.");
        return true;
    }

static bool HandleCustomizeCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();
		me->SetAtLoginFlag(AT_LOGIN_CUSTOMIZE);
		handler->PSendSysMessage("Relog to customize your character.");
        return true;
    }

static bool HandleVipMallCommand(ChatHandler* handler, const char* args)
    {

        Player* me = handler->GetSession()->GetPlayer();

        if (me->isInCombat())
        {
            handler->SendSysMessage(LANG_YOU_IN_COMBAT);
            handler->SetSentErrorMessage(true);
            return false;
        }

        // stop flight if need
        if (me->isInFlight())
        {
            me->GetMotionMaster()->MovementExpired();
            me->CleanupAfterTaxiFlight();
        }
        // save only in non-flight case
        else
            me->SaveRecallPosition();

		me->TeleportTo(530,	-1572.22f,	7952.655f,	-22.6071f,	0.995982f); // MapId, X, Y, Z, O
                return true;
    }

static bool HandleDemorphCommand(ChatHandler* handler, const char* args)
	{
		Player* me = handler->GetSession()->GetPlayer();
		me->DeMorph();
		me->SetFloatValue(OBJECT_FIELD_SCALE_X, 1.0);
		return true;
	}
	
};

void AddSC_vipcommands()
{
    new vipcommands();
}