#Add in imports:

import uimaintenance

# Search:

        self.__ProcessPreservedServerCommand()

# Add below:

        self.maintenance = uimaintenance.MaintenanceWindow()
        self.maintenance.Hide()

# Search:

        player.ClearSkillDict()

# Add above:

        if self.maintenance:
            self.maintenance.Hide()
            self.maintenance = None

#Search:

		onPressKeyDict[app.DIK_F4]	= lambda : self.__PressQuickSlot(7)

#Add below:

		onPressKeyDict[app.DIK_F12]	= lambda : self.maintenanceadminopen()

#Search:

			# PRIVATE_SHOP_PRICE_LIST
			"MyShopPriceList"		: self.__PrivateShop_PriceList,
			# END_OF_PRIVATE_SHOP_PRICE_LIST

#Add below:

			"Maintenancegui"			: self.Maintenancegui,

#Add to bottom:

	def Maintenancegui(self,time,duration):
		self.maintenance.Open(time,duration)

	def maintenanceadminopen(self):
		if not chr.IsGameMaster(player.GetMainCharacterIndex()):
			return

		self.Maintenancedialog = uimaintenance.MaintenanceDialog()
		self.Maintenancedialog.Show()