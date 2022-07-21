//Search:

	HEADER_GG_CHECK_AWAKENESS = 29,

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	HEADER_GG_MAINTENANCE = 32,
#endif

//Search:

typedef struct SPacketGGBlockChat
{
	BYTE	bHeader;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
	long	lBlockDuration;
} TPacketGGBlockChat;

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
typedef struct SPacketGGMaintenance
{
	BYTE	bHeader;
	bool	bMaintenance;
	DWORD	dwRemainingTime;
	DWORD	dwMaintenanceTime;
} TPacketGGMaintenance;
#endif