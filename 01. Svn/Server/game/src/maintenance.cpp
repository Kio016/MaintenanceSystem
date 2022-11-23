/***
Author: Kio
File name: maintenance.cpp
Date: 20.07.2022
***/

#include "stdafx.h"
#include "char.h"
#include "utils.h"
#include "config.h"
#include "desc_client.h"
#include "desc_manager.h"
#include "p2p.h"
#include "maintenance.h"

CMaintenance::CMaintenance() = default;
CMaintenance::~CMaintenance() = default;

static LPEVENT m_pkMaintenanceEvent = nullptr;

EVENTINFO(maintenance_data_info)
{
	DWORD dwRemainingTime;
	DWORD dwMaintenanceTime;
	maintenance_data_info() : dwRemainingTime(0), dwMaintenanceTime(0) {}
};

EVENTFUNC(maintenance_start_event)
{
	maintenance_data_info* info = dynamic_cast<maintenance_data_info*>(event->info);

	if (info == nullptr)
	{
		sys_err("maintenance_start_event> <Factor> Null pointer");
		return 0;
	}

	if (get_global_time() > info->dwRemainingTime)
	{
		char szNotice[128];
		snprintf(szNotice, sizeof(szNotice), "<Bakým Sistemi> Bakým baþlýyor... %s sürecektir.", CMaintenance::Instance().SecondToHM(info->dwMaintenanceTime));
		BroadcastNotice(szNotice, true);

		TPacketGGShutdown p;
		p.bHeader = HEADER_GG_SHUTDOWN;
		P2P_MANAGER::Instance().Send(&p, sizeof(TPacketGGShutdown));

		Shutdown(10);
		return 0;
	}

	return PASSES_PER_SEC(1);
}

void CMaintenance::StartMaintenance(DWORD dwTime, DWORD dwTime2)
{
	DWORD dwRemainingTime = get_global_time() + dwTime;

	SetMaintenance(true);
	SetRemainingTime(dwRemainingTime);
	SetMaintenanceTime(dwTime2);

	StartMaintenanceTimer(dwRemainingTime, dwTime2);
	MaintenancePacket(dwRemainingTime, dwTime2);
	MaintenanceP2PPacket(true, dwRemainingTime, dwTime2);
}

void CMaintenance::StartMaintenanceTimer(DWORD dwTime, DWORD dwTime2)
{
	auto info = AllocEventInfo<maintenance_data_info>();
	info->dwRemainingTime = dwTime;
	info->dwMaintenanceTime = dwTime2;
	m_pkMaintenanceEvent = event_create(maintenance_start_event, info, 1);
}

struct maintenance_packet_func
{
	DWORD m_dwTime, m_dwTime2;

	maintenance_packet_func(DWORD dwTime, DWORD dwTime2) : m_dwTime(dwTime), m_dwTime2(dwTime2) {}

	void operator () (LPDESC d)
	{
		if (d->GetCharacter())
			d->GetCharacter()->ChatPacket(CHAT_TYPE_COMMAND, "Maintenancegui %d %d", m_dwTime, m_dwTime2);
	}
};

void CMaintenance::MaintenancePacket(DWORD dwTime, DWORD dwTime2)
{
	const DESC_MANAGER::DESC_SET& c_ref_set = DESC_MANAGER::Instance().GetClientSet();
	std::for_each(c_ref_set.begin(), c_ref_set.end(), maintenance_packet_func(dwTime, dwTime2));
}

void CMaintenance::MaintenanceP2PPacket(bool bStatus, DWORD dwTime, DWORD dwTime2)
{
	TPacketGGMaintenance p;
	p.bHeader = HEADER_GG_MAINTENANCE;
	p.bMaintenance = bStatus;
	p.dwRemainingTime = dwTime;
	p.dwMaintenanceTime = dwTime2;
	P2P_MANAGER::Instance().Send(&p, sizeof(p));
}

void CMaintenance::CancelMaintenance()
{
	SetMaintenance(false);
	SetRemainingTime(0);
	SetMaintenanceTime(0);

	CancelMaintenanceTimer();
	MaintenancePacket(0, 0);
	MaintenanceP2PPacket(false, 0, 0);
}

void CMaintenance::CancelMaintenanceTimer()
{
	event_cancel(&m_pkMaintenanceEvent);
}

const char* CMaintenance::SecondToHM(DWORD dwTime)
{
	DWORD dwSecond = dwTime % 60;
	DWORD dwMinute = (dwTime / 60) % 60;
	DWORD dwHour = ((dwTime / 60) / 60) % 24;

	static char szMessage[64];

	if (dwHour <= 0)
	{
		if (dwTime % 60 == 0)
			snprintf(szMessage, sizeof(szMessage), "%d dakika", dwMinute);
		else
			snprintf(szMessage, sizeof(szMessage), "%d dakika %d saniye", dwMinute, dwSecond);
	}
	else
	{
		if (dwTime % 60*60 == 0)
			snprintf(szMessage, sizeof(szMessage), "%d saat", dwHour);
		else
		{
			if (dwTime % 60 == 0)
				snprintf(szMessage, sizeof(szMessage), "%d saat %d dakika", dwHour, dwMinute);
			else
				snprintf(szMessage, sizeof(szMessage), "%d saat %d dakika %d saniye", dwHour, dwMinute, dwSecond);
		}
	}

	return szMessage;
}
