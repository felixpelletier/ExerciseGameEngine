from qtheader import *
from PyQt4.QtGui import QFileDialog
from shutil import copytree, copy
import os

class sup_ui(QWidget):
	
	def __init__(self, mainframe, op):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.initUI()
		
	def initUI(self):
		self.mainframe.setWindowTitle("Contact/Support")
		
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		importB = QPushButton(self, text="Import")
		importB.clicked.connect(self.importF)
		self.grid.addWidget(importB, 0, 0)
		
		exportB = QPushButton(self, text="Export")
		exportB.clicked.connect(self.export)
		self.grid.addWidget(exportB, 0, 1)
		
		contact = QPushButton(self, text="Contact")
		contact.clicked.connect(self.contact)
		self.grid.addWidget(contact, 0, 2)
		
		text = QLabel(self, text="Hello and thank you for using the Persona X Story Creator.\n\nTo import data from other versions of the Story Creator, click \"Import\".\n\nTo export your data to a seperate directory, (to prepare for a version change), click \"Export\".\n\nTo send your data to the dev team or to report a bug with the program, click \"Contact\"")
		text.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(text, 1, 0, 1, 3)
		
		back = QPushButton(self, text="Back")
		back.clicked.connect(self.back)
		self.grid.addWidget(back, 2, 1)
		
	def importF(self):
		fileBrowser = QFileDialog()
		fileBrowser.setFileMode(QFileDialog.Directory)
		fileBrowser.setViewMode(QFileDialog.Detail)
		fileBrowser.setOption(QFileDialog.ShowDirsOnly, True)
		if fileBrowser.exec_():
			dir = fileBrowser.selectedFiles()
		print "Copying data from "+str(dir[0])
		files = os.listdir(str(dir[0]))
		copyOn = True
		print files
		for file in files:
			copyOn = True
			if file.endswith(".json"):
				if os.path.exists(os.path.join(json_reader.buildPath("data"), file)):
					if popup("File " + file[:len(file)-5] + " already exists. Overwrite?", "Warning"):
						os.remove(json_reader.buildPath("data/"+file))
					else:
						copyOn = False
				if copyOn:
					print "Copying valid file " + file
					copy(os.path.join(str(dir[0]), file), json_reader.buildPath("data"))
					try:#Ugly AF
						json_reader.readOne(file[:len(file)-5])
						json_reader.writeCharNames(file[:len(file)-5])
					except:
						try:
							json_reader.readOneP(file[:len(file)-5])
							json_reader.writePerNames(file[:len(file)-5])
						except:
							pass
		print "Successfully copied files"
		popup("Files imported successfully!", "Information")
		
	def export(self):
		fileBrowser = QFileDialog()
		fileBrowser.setFileMode(QFileDialog.Directory)
		fileBrowser.setViewMode(QFileDialog.Detail)
		fileBrowser.setOption(QFileDialog.ShowDirsOnly, True)
		if fileBrowser.exec_():
			dir = fileBrowser.selectedFiles()
		print "Copying data to "+str(dir[0])+"/exportdata"
		try:
			copytree(json_reader.buildPath("data"), str(dir[0])+"/exportdata")
		except Exception as e:
			print e
			popup("Error in copying files. There is a file in the selected directory that has the same name as a Story Creator file.\n\nFiles are copied to "+str(dir[0])+"/exportdata"+". Please ensure this directory does not already exist.", "Critical")
			return
		print "Successfully copied files"
		popup("Files exported successfully!", "Information")
		
	def contact(self):
		pass
		
	def back(self):
		self.mainframe.changeState(self.op)