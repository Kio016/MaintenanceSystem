//Search:

Set(HEADER_GG_CHECK_AWAKENESS, sizeof(TPacketGGCheckAwakeness), "CheckAwakeness");

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	Set(HEADER_GG_MAINTENANCE, sizeof(TPacketGGMaintenance), "Maintenance");
#endif