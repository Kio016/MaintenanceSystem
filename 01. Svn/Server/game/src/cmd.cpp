//Search:

struct command_info cmd_info[]

//add on top:

#ifdef ENABLE_MAINTENANCE_SYSTEM
ACMD(do_start_maintenance);
ACMD(do_cancel_maintenance);
#endif

//Search:

{ "\n",		NULL,			0,			POS_DEAD,	GM_IMPLEMENTOR	}

//Add on top:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	{ "start_maintenance",		do_start_maintenance,	0,	POS_DEAD,	GM_IMPLEMENTOR },
	{ "cancel_maintenance",		do_cancel_maintenance,	0,	POS_DEAD,	GM_IMPLEMENTOR },
#endif