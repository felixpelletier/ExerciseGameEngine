import sys
from PyQt4.QtGui import QApplication, QMessageBox

#WARNING: Returns True if 'x' button or escape key is pressed.
def popup(message, type):
	icon = {"Information":QMessageBox.Information, "Warning":QMessageBox.Warning,
			"Critical":QMessageBox.Critical, "Question":QMessageBox.Question,
			"Default":QMessageBox.NoIcon}

	# Create an PyQT4 application object.
	a = QApplication(sys.argv)

	# Show a message box
	box = QMessageBox(icon[type], type, message)
	if type in ["Warning", "Question"]:
		box.setStandardButtons(QMessageBox.Yes | QMessageBox.Cancel)
	box.setEscapeButton(QMessageBox.Cancel)
	result = box.exec_()
	return result in [QMessageBox.Yes, QMessageBox.Ok]

#TESTS	    
#print popup("This is a test window", "Warning")
#print popup("This is another test window", "Critical")