//Add in includes:

#ifdef ENABLE_MAINTENANCE_SYSTEM
#include "maintenance.h"
#endif

//Search:

	DSManager dsManager;

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	CMaintenance	maintenance;
#endif