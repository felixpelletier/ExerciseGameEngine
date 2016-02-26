from PyQt4.QtGui import QApplication, QWidget, QGridLayout, QPushButton, QPixmap, QLabel, QPalette, QSizePolicy
from PyQt4.QtCore import Qt, QRect
import json_reader
from chargui import char_creator
from pergui import per_creator

class OP(QWidget):
	
	def __init__(self, mainframe):
		QWidget.__init__(self)
		self.mainframe = mainframe
		print "Application started"
		self.setAutoFillBackground(True)
		p = QPalette()
		p.setColor(QPalette.Background, Qt.black)
		self.setPalette(p)
		self.initUI()
		
	def initUI(self):
		self.mainframe.setWindowTitle("Story Creator")
		
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		imageLabel = QLabel(self)
		logo = QPixmap(json_reader.buildPath("creator_logo.png"))
		imageLabel.setPixmap(logo)
		self.grid.addWidget(imageLabel, 0, 0)
		
		intframe = QWidget()
		self.grid.addWidget(intframe, 0, 1)
		
		bGrid = QGridLayout()
		intframe.setLayout(bGrid)
		
		createSL = QPushButton(intframe, text="Create Social Link")
		createSL.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
		createSL.clicked.connect(self.actionS)
		bGrid.addWidget(createSL, 0, 0)
		
		createPersona = QPushButton(intframe, text="Create Persona")
		createPersona.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
		createPersona.clicked.connect(self.actionP)
		bGrid.addWidget(createPersona, 1, 0)
		
		createChar = QPushButton(intframe, text="Create Character")
		createChar.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
		createChar.clicked.connect(self.actionC)
		bGrid.addWidget(createChar, 2, 0)
		
		quit = QPushButton(intframe, text="Quit")
		quit.setSizePolicy(QSizePolicy.Preferred, QSizePolicy.Expanding)
		quit.clicked.connect(self.quit)
		bGrid.addWidget(quit, 3, 0)
		
	def actionP(self):
		print "Changed frame to Persona creator"
		self.mainframe.changeState(per_creator(self.mainframe, self))
		#self.destroy()
	
	def actionC(self):
		print "Changed frame to Character creator"
		self.mainframe.changeState(char_creator(self.mainframe, self))
		
	def actionS(self):
		print "Changed frame to SL creator"
		#app = SL_creator(self.parent)
		#self.destroy()
		
	def quit(self):
		print "Exiting..."
		self.mainframe.close()