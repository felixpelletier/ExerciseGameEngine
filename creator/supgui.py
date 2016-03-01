from qtheader import *
from PyQt4.QtGui import QFileDialog
from shutil import copytree, copy
import os
import email
import smtplib

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
		
		self.contact = QPushButton(self, text="Contact")
		self.contact.clicked.connect(self.contactF)
		self.grid.addWidget(self.contact, 0, 2)
		
		self.text = QLabel(self, text="Hello and thank you for using the Persona X Story Creator.\n\nTo import data from other versions of the Story Creator, click \"Import\".\n\nTo export your data to a seperate directory, (to prepare for a version change), click \"Export\".\n\nTo send your data to the dev team or to report a bug with the program, click \"Contact\"")
		self.text.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(self.text, 1, 0, 1, 3)
		
		self.back = QPushButton(self, text="Back")
		self.back.clicked.connect(self.backF)
		self.grid.addWidget(self.back, 2, 1)
		
	def importF(self):
		fileBrowser = QFileDialog()
		fileBrowser.setFileMode(QFileDialog.Directory)
		fileBrowser.setViewMode(QFileDialog.Detail)
		fileBrowser.setOption(QFileDialog.ShowDirsOnly, True)
		if fileBrowser.exec_():
			dir = fileBrowser.selectedFiles()
		else:
			print "Cancelled"
			return
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
		else:
			print "Cancelled"
			return
		print "Copying data to "+str(dir[0])+"/exportdata"
		try:
			copytree(json_reader.buildPath("data"), str(dir[0])+"/exportdata")
		except Exception as e:
			print e
			popup("Error in copying files. There is a file in the selected directory that has the same name as a Story Creator file.\n\nFiles are copied to "+str(dir[0])+"/exportdata"+". Please ensure this directory does not already exist.", "Critical")
			return
		print "Successfully copied files"
		popup("Files exported successfully!", "Information")
		
	def contactF(self):
		self.contact.clicked.disconnect()
		self.text.close()
		emailFrame(self)
		
	def backF(self):
		self.mainframe.changeState(self.op)
		
		
class emailFrame(QWidget):

	def __init__(self, op):
		QWidget.__init__(self)
		self.op = op
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.op.grid.addWidget(self, 1, 0, 1, 3)
		
		subL = QLabel(self, text="Subject:")
		subL.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(subL, 0, 0)
		
		self.subject = QLineEdit(self)
		self.subject.setFixedSize(150, 20)
		self.grid.addWidget(self.subject, 0, 1)
		
		bodL = QLabel(self, text="")
		bodL.setAlignment(Qt.AlignHCenter)
		
		self.body = QTextEdit(self)
		self.body.setFixedSize(400, 150)
		self.grid.addWidget(self.body, 1, 1, 1, 3)
		
		sem = QLabel(self, text="Your email:")
		sem.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(sem, 2, 0)
		
		self.semT = QLineEdit(self)
		self.semT.setFixedSize(150, 20)
		self.grid.addWidget(self.semT, 2, 1)
		
		send = QPushButton(self, text="Send")
		send.clicked.connect(self.send)
		self.grid.addWidget(send, 2, 2)
		
		self.addFiles = QCheckBox(self, text="Send submission")
		self.grid.addWidget(self.addFiles, 0, 2)
		
		self.op.back.clicked.disconnect()
		self.op.back.clicked.connect(self.back)
		
	def send(self):
		if str(self.semT.text())=="" or str(self.semT.text()).isspace() or str(self.subject.text())=="" or str(self.subject.text()).isspace():
			popup("Please enter a message and subject.", "Critical")
			return
		msg = email.message_from_string(str(self.body.toPlainText()))
		msg['From'] = str(self.semT.text())
		msg['To'] = "swwouf@hotmail.com"
		msg['Subject'] = str(self.subject.text())
		
		s = smtplib.SMTP("smtp.live.com", 587)
		s.ehlo()
		s.starttls()
		s.ehlo()
		s.login("personaxdevteam@hotmail.com", 'PersonaX')
		try:
			s.sendmail(msg['From'], msg['To'], msg.as_string())
			print "Message sent successfully"
			popup("Email was sent! Thank you!", "Information")
		except smtplib.SMTPSenderRefused:
			popup("You must provide your email address so that we may contact you if needed.\n\nYour email address will not be shared with any third parties.", "Critical")		
		s.quit()
		
	def back(self):
		self.close()
		self.op.text.show()
		self.op.back.clicked.disconnect()
		self.op.back.clicked.connect(self.op.backF)
		self.op.contact.clicked.connect(self.op.contactF)
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		