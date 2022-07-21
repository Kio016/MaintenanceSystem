//Add to bottom:

#ifdef ENABLE_MAINTENANCE_SYSTEM
#include "maintenance.h"
ACMD(do_start_maintenance)
{
	char arg1[256], arg2[256];
	two_arguments(argument, arg1, sizeof(arg1), arg2, sizeof(arg2));

	if (!*arg1 || !*arg2)
		return;

	if (!isnhdigit(*arg1) || !isnhdigit(*arg2))
		return;

	DWORD dwRemainingTime = 0;
	str_to_number(dwRemainingTime, arg1);

	DWORD dwMaintenanceTime = 0;
	str_to_number(dwMaintenanceTime, arg2);

	if (dwRemainingTime <= 0 || dwMaintenanceTime <= 0)
		return;

	auto& rkMaintenanceMgr = CMaintenance::Instance();

	if (rkMaintenanceMgr.IsMaintenance())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, "Bakým aktifken baþka bir bakým baþlatamazsýn.");
		return;
	}

	rkMaintenanceMgr.StartMaintenance(dwRemainingTime, dwMaintenanceTime);
}

ACMD(do_cancel_maintenance)
{
	CMaintenance::Instance().CancelMaintenance();
}
#endif