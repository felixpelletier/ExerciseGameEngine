import sys
#from PyQt4.QtGui import QApplication, QMessageBox

def popup(message, type):
	#if os = OSX
	return True
	icon = {"Information":QMessageBox.Information, "Warning":QMessageBox.Warning,
			"Critical":QMessageBox.Critical, "Question":QMessageBox.Question,
			"Default":QMessageBox.NoIcon}

	box = QMessageBox(icon[type], type, message)
	if type in ["Warning", "Question"]:
		box.setStandardButtons(QMessageBox.Yes | QMessageBox.Cancel)
		box.setDefaultButton(QMessageBox.Yes)
		box.setEscapeButton(QMessageBox.Cancel)
	result = box.exec_()
	return result in [QMessageBox.Yes, QMessageBox.Ok]

#TESTS	    
#print popup("This is a test window", "Warning")
#print popup("This is another test window", "Critical")