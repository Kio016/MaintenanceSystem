//Search:

int CInputP2P::Analyze(LPDESC d, BYTE bHeader, const char* c_pData)

//Add above:

#ifdef ENABLE_MAINTENANCE_SYSTEM
#include "maintenance.h"
void CInputP2P::Maintenance(const char* c_pData)
{
	auto p = (TPacketGGMaintenance*)c_pData;
	auto& rkMaintenanceMgr = CMaintenance::Instance();

	if (!p->bMaintenance)
		rkMaintenanceMgr.CancelMaintenanceTimer();

	rkMaintenanceMgr.SetMaintenance(p->bMaintenance);
	rkMaintenanceMgr.SetRemainingTime(p->dwRemainingTime);
	rkMaintenanceMgr.SetMaintenanceTime(p->dwMaintenanceTime);
	rkMaintenanceMgr.MaintenancePacket(p->dwRemainingTime, p->dwMaintenanceTime);
}
#endif

//Search:

	case HEADER_GG_CHECK_AWAKENESS:
		IamAwake(d, c_pData);
		break;

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	case HEADER_GG_MAINTENANCE:
		Maintenance(c_pData);
		break;
#endif