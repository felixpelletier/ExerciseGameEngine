from qtheader import *
from qtslgui import SLFrame

class SL_creator(QWidget):

	def __init__(self, mainframe, op):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.initUI()
		
	def initUI(self):
		self.mainframe.setWindowTitle("Social Link Creator")
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		list = json_reader.data_list("arcanas")
		
		self.arcSel = QComboBox(self)
		self.arcSel.addItem("Select Arcana")
		self.arcSel.activated.connect(self.showText)
		self.arcSel.addItems(list)
		self.arcSel.setCurrentIndex(0)
		self.grid.addWidget(self.arcSel, 1, 1)
		
		select = QPushButton(self, text="Select")
		select.clicked.connect(self.context)
		self.grid.addWidget(select, 2, 1)
		
		back = QPushButton(self, text="Back")
		back.clicked.connect(self.back)
		self.grid.addWidget(back, 3, 1)
		
		self.card = QLabel(self)
		defaultCard = QPixmap(json_reader.buildPath("int/cards/card.png"))
		self.card.setPixmap(defaultCard)
		self.card.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(self.card, 0, 0)
		
		self.text = QLabel(self, text="")
		self.text.setFixedSize(400, 200)
		self.text.setWordWrap(True)
		self.text.setAlignment(Qt.AlignHCenter)
		self.grid.addWidget(self.text, 1, 0, 3, 1)
		
	def context(self):
		if self.arcSel.currentText() == "Select Arcana":
			return
		levs = []
		for x in range(1,11):
			levs.append("Level " + str(x))
		self.levelOM = QComboBox(self)
		self.levelOM.addItems(levs)
		self.levelOM.setCurrentIndex(0)
		self.grid.addWidget(self.levelOM, 1, 2, 1, 2)
		
		self.angs = []
		try:
			tempLink = json_reader.readLink(str(self.arcSel.currentText()))
			for decon in tempLink["cutscenes"]:
				self.angs.append("Angle " + str(decon)[str(decon).index("_")+1:] )
		except:
			pass
		if not self.angs:
			self.angs.append("No angles")
			
		self.angleOM = QComboBox(self)
		self.angleOM.addItems(self.angs)
		self.angleOM.setCurrentIndex(0)
		self.grid.addWidget(self.angleOM, 2, 2, 1, 2)
		
		self.addAngB = QPushButton(self, text="Add Angle")
		self.addAngB.clicked.connect(self.addAngle)
		self.grid.addWidget(self.addAngB, 3, 2)
		
		self.newAng = QLineEdit(self)
		self.newAng.setFixedSize(20, 20)
		self.grid.addWidget(self.newAng, 3, 3)
		
		self.go = QPushButton(self, text="Go")
		self.go.clicked.connect(self.begin)
		self.grid.addWidget(self.go, 4, 2, 1, 2)
		
	def addAngle(self):
		try:
			(int)(str(self.newAng.text()))
			if self.angs[0] == "No angles":
				self.angleOM.clear()
			self.angleOM.addItem("Angle "+str(self.newAng.text()))
			self.angleOM.setCurrentIndex(self.angleOM.count()-1)
			self.newAng.clear()
		except Exception as e:
			print e
			popup("The Angle must be an integer", "Critical")
			print "Angle must be an integer"
		
	def showText(self):
		temp = [self.arcSel.itemText(i) for i in range(self.arcSel.count())]
		if "Select Arcana" in temp:
			self.arcSel.removeItem(temp.index("Select Arcana"))
		self.text.setText(json_reader.readArcDesc(str(self.arcSel.currentText())))
		self.card.setPixmap(QPixmap(json_reader.buildPath("int/cards/"+str(self.arcSel.currentText())+".png")))
		self.destroyContext()
		
	def destroyContext(self):
		try:
			self.levelOM.close()
			self.angleOM.close()
			self.addAngB.close()
			self.newAng.close()
			self.go.close()
		except:
			pass
		
	def begin(self):
		if self.angleOM.currentText() == "No angles":
			popup("An Angle must be selected.\nCreate angles by entering a number in the text box below and clicking \"Add Angle\"", "Critical")
			return
		enter_level = str(self.levelOM.currentText())[str(self.levelOM.currentText()).index(" ")+1:]
		enter_angle = str(self.angleOM.currentText())[str(self.angleOM.currentText()).index(" ")+1:]
		print "Entered SL creation mode for arcana " + str(self.arcSel.currentText())
		#self.destroyContext()
		self.mainframe.changeState(SLFrame(self.mainframe, self, str(self.arcSel.currentText()), (int)(enter_level), (int)(enter_angle)))
		
	def back(self):
		print "Returned to main screen"
		self.mainframe.changeState(self.op)