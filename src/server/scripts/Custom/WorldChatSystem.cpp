/************************************
*        Made by ??                 *
*                                   *
*      Edit & Release by            *
*      Ghostcrawler336              *
*                                   *
*************************************
*/

#include "ScriptPCH.h"
#include "Chat.h"
#include "Common.h"

/* Colors */
#define MSG_COLOR_ORANGE "|cffFFA500"
#define MSG_COLOR_DARKORANGE "|cffFF8C00"
#define MSG_COLOR_RED "|cffFF0000"
#define MSG_COLOR_LIGHTRED "|cffD63931"
#define MSG_COLOR_ROYALBLUE "|cff4169E1"
#define MSG_COLOR_LIGHTBLUE "|cffADD8E6"
#define MSG_COLOR_YELLOW "|cffFFFF00"
#define MSG_COLOR_GREEN "|cff008000"
#define MSG_COLOR_PURPLE "|cffDA70D6"
#define MSG_COLOR_WHITE  "|cffffffff"
#define MSG_COLOR_SUBWHITE  "|cffbbbbbb"

/* Ranks */
#define ADMINISTRATOR "Admin"
#define MODERATOR "Moderator"
#define GAMEMASTER "GM"
#define DEVELOPER "Developer"
#define OWNER "Owner"
#define VIP "Vip"
#define PLAYER "Player"


class World_Chat : public CommandScript
{
    public:
    World_Chat() : CommandScript("World_Chat") { }

    static bool HandleWorldChatCommand(ChatHandler * pChat, const char * msg)
    {
		if(!*msg)
			return false;

        Player * player = pChat->GetSession()->GetPlayer();
        char message[1024];

		switch(player->GetSession()->GetSecurity())
		{
			case SEC_PLAYER:
				snprintf(message, 1024, "[World][Player][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_LIGHTBLUE, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
			    case SEC_VIP:
				snprintf(message, 1024, "[World][Vip][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_PURPLE, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
				case SEC_GAMEMASTER:
				snprintf(message, 1024, "[World][GM][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(),  MSG_COLOR_YELLOW, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
				case SEC_MODERATOR:
				snprintf(message, 1024, "[World][Moderator][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_ORANGE, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
				case SEC_DEVELOPER:
				snprintf(message, 1024, "[World][Developer][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_ROYALBLUE, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
				case SEC_ADMINISTRATOR:
				snprintf(message, 1024, "[World][Admin][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_RED, msg);
				sWorld->SendGlobalText(message, NULL);
			break;
			
				case SEC_OWNER:
				snprintf(message, 1024, "[World][Owner][%s%s|r]: %s%s|r", MSG_COLOR_WHITE, player->GetName(), MSG_COLOR_RED, msg);
				sWorld->SendGlobalText(message, NULL);
			break;

			case SEC_CONSOLE:
				snprintf(message, 1024, "[World][%sAdministrator|r][%s%s|r]: %s%s|r", MSG_COLOR_RED, MSG_COLOR_LIGHTRED, player->GetName(),
					MSG_COLOR_LIGHTBLUE, msg);
				sWorld->SendGlobalText(message, NULL);
			break;

			
			
			
		}
        return true;
    }

    ChatCommand * GetCommands() const
    {
            static ChatCommand HandleWorldChatCommandTable[] =
            {
                    { "world",        SEC_PLAYER,         true,     &HandleWorldChatCommand,               "",  NULL },
                    { NULL,              0,               false,    NULL,                                  "",  NULL }
            };
            return HandleWorldChatCommandTable;
    }
};

void AddSC_World_Chat()
{
        new World_Chat;
}