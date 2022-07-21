//Add in includes:

#ifdef ENABLE_MAINTENANCE_SYSTEM
#include "maintenance.h"
#endif

//Search:

	if (g_noticeBattleZone)
	{
		if (FN_is_battle_zone(ch))
		{
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("ÀÌ ¸Ê¿¡¼± °­Á¦ÀûÀÎ ´ëÀüÀÌ ÀÖÀ»¼ö µµ ÀÖ½À´Ï´Ù."));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("ÀÌ Á¶Ç×¿¡ µ¿ÀÇÇÏÁö ¾ÊÀ»½Ã"));
			ch->ChatPacket(CHAT_TYPE_NOTICE, LC_TEXT("º»ÀÎÀÇ ÁÖ¼º ¹× ºÎ¼ºÀ¸·Î µ¹¾Æ°¡½Ã±â ¹Ù¶ø´Ï´Ù."));
		}
	}

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	auto& rkMaintenanceMgr = CMaintenance::Instance();
	if (rkMaintenanceMgr.IsMaintenance())
		ch->ChatPacket(CHAT_TYPE_COMMAND, "Maintenancegui %d %d", rkMaintenanceMgr.GetRemainingTime(), rkMaintenanceMgr.GetMaintenanceTime());
#endif