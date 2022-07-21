//Search:

	void		IamAwake(LPDESC d, const char* c_pData);

//Add below:

#ifdef ENABLE_MAINTENANCE_SYSTEM
	void		Maintenance(const char* c_pData);
#endif