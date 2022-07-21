import ui, app, net

class MaintenanceDialog(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.__LoadDialog()

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def __LoadDialog(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "uiscript/maintenanceadmin.py")
		except:
			import exception
			exception.Abort("MaintenanceDialog.__LoadDialog.LoadObject")

		try:
			getObject = self.GetChild
			self.titleName = self.GetChild("TitleName")
			self.GetChild("titlebar").SetCloseEvent(ui.__mem_func__(self.OnCancel))
			self.cancelButton = self.GetChild("cancel_button")
			self.startmaintenanceButton = self.GetChild("start_maintenance")
			self.cancelmaintenanceButton = self.GetChild("cancel_maintenance")
			self.inputSlot = getObject("InputSlot")
			self.inputValue = getObject("InputValue")
			self.inputSlot2 = getObject("InputSlot2")
			self.inputValue2 = getObject("InputValue2")

		except:
			import exception
			exception.Abort("MaintenanceDialog.__LoadDialog.BindObject")

		self.SetCenterPosition()
		self.SetTop()
		self.cancelButton.SetEvent(ui.__mem_func__(self.OnCancel))
		self.startmaintenanceButton.SetEvent(ui.__mem_func__(self.StartMaintenance))
		self.cancelmaintenanceButton.SetEvent(ui.__mem_func__(self.CancelMaintenance))
		self.cancelButton.Hide()

	def Destroy(self):
		self.ClearDictionary()
		self.titleName = None
		self.cancelButton = None
		self.inputSlot = None
		self.inputValue = None
		self.inputSlot2 = None
		self.inputValue2 = None

	def SetTitle(self, title):
		self.titleName.SetText(title)

	def StartMaintenance(self):
		self.Hide()
		time = self.inputValue.GetText()
		duration = self.inputValue2.GetText()
		net.SendChatPacket("/start_maintenance %d %d" % (int(time), int(duration)))

	def CancelMaintenance(self):
		self.Hide()
		net.SendChatPacket("/cancel_maintenance")

	def OnCancel(self):
		self.Hide()
		return True

class MaintenanceWindow(ui.ScriptWindow):
	def __init__(self):
		ui.ScriptWindow.__init__(self)
		self.LoadWindow()
		self.maintime = 0

	def __del__(self):
		ui.ScriptWindow.__del__(self)

	def LoadWindow(self):
		try:
			pyScrLoader = ui.PythonScriptLoader()
			pyScrLoader.LoadScriptFile(self, "UIScript/maintenance.py")
		except:
			import exception
			exception.Abort("MaintenanceWindow.LoadWindow.LoadObject")
		try:
			self.board = self.GetChild("Thinboard")
			self.textLine1 = self.GetChild("message1")
			self.textLine2 = self.GetChild("message2")
		except:
			import exception
			exception.Abort("MaintenanceWindow.LoadWindow.LoadObject")

	def Open(self, time, duration):
		self.SetTop()
		self.Show()
		self.textLine1.SetText("Süre: %s sürecek." % (self.SecondToHMD(int(duration))))
		self.maintime = int(time)

	def Close(self):
		self.Hide()

	def SecondToHMD(self, time):
		second = int(time % 60)
		minute = int((time / 60) % 60)
		hour = int(((time / 60) / 60) % 24)
		day = int((((time / 60) / 60) / 24) % 30)

		if hour <= 0:
			if time % 60 == 0:
				return "%d dakika" % (minute)
			else:
				return "%d dakika %02d saniye" % (minute, second)
		else:
			if day <= 0:
				if time % 60*60 == 0:
					return "%d saat" % (hour)
				else:
					if time % 60 == 0:
						return "%d saat %02d dakika" % (hour, minute)
					else:
						return "%d saat %02d dakika %02d saniye" % (hour, minute, second)
			else:
				return "%d gün %d saat %02d dakika %02d saniye" % (day, hour, minute, second)

	def OnUpdate(self):
		remain_time = self.maintime - app.GetGlobalTimeStamp()
		if remain_time > 0:
			self.textLine2.SetText("Kalan zaman: %s" % (self.SecondToHMD(remain_time)))
		else:
			self.Hide()