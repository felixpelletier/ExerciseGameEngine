from qtheader import *
from sls import SocialLink
import sys

class LinkInfo(QWidget):
	
	def __init__(self, link, linklevel, linkangle):
		QWidget.__init__(self)
		self.link = link
		self.linklevel = linklevel
		self.linkangle = linkangle
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.levang = {}
		elev = []
		
		for key, cutscene in self.link.cutscenes.iteritems():
			if key[:key.index("_")] in self.levang:
				self.levang[key[:key.index("_")]].append(key[key.index("_")+1:])
			else:
				self.levang[key[:key.index("_")]] = [key[key.index("_")+1:]]
			if key[:key.index("_")] not in elev:
				elev.append(key[:key.index("_")])
		for level, angle in self.levang.iteritems():
			angle.sort()
		elev.sort()
		if elev[-1] == '10':
			elev = elev[:len(elev)-1]
		print elev
		infoL = QLabel(self, text="Social Link Information")
		self.grid.addWidget(infoL, 0, 0, 1, 13)
		
		self.level = QComboBox(self)
		if len(elev) != 0:
			elev.insert(0, "")
			self.level.addItems(elev)
			self.level.activated.connect(self.recs)
		else:
			self.level.addItems(["No levels have been created"])
		self.grid.addWidget(self.level, 1, 1, 1, 1)
		
		atlevel = QLabel(self, text="At " + self.link.arcana + " level ")
		self.grid.addWidget(atlevel, 1, 0, 1, 1)
		
		arcanainfo = QLabel(self, text=self.link.arcana + " Social Link info")
		self.aitext = QTextEdit(self)
		self.aitext.setFixedSize(300, 100)
		
		self.save = QPushButton(self, text="Save")
		self.back = QPushButton(self, text="Back")
		self.save.clicked.connect(self.saveinfo)
		self.back.clicked.connect(self.endedit)

		if self.linklevel and self.linkangle:
			self.grid.addWidget(arcanainfo, 2, 0, 1, 6)
			self.grid.addWidget(self.aitext, 3, 0, 1, 6)
		
			thisinfo = QLabel(self, text=self.link.arcana + " info for level: " + self.linklevel + ", angle: " + self.linkangle)
			self.grid.addWidget(thisinfo, 2, 7, 1, 6)
		
			self.titext = QTextEdit(self)
			self.titext.setFixedSize(300, 100)
			self.grid.addWidget(self.titext, 3, 7, 1, 6)
		
			self.grid.setAlignment(thisinfo, Qt.AlignHCenter)
			self.grid.setAlignment(self.titext, Qt.AlignHCenter)
			self.grid.addWidget(self.save, 4, 0, 1, 6)
			self.grid.addWidget(self.back, 4, 7, 1, 6)
		else:
			self.grid.addWidget(arcanainfo, 2, 0, 1, 12)
			self.grid.addWidget(self.aitext, 3, 0, 1, 12)
			self.grid.addWidget(self.save, 4, 0, 1, 1)
			self.grid.addWidget(self.back, 4, 1, 1, 1)
			
		youhave = QLabel(self, text="You have established the ")
		ofthe = QLabel(self, text=" of the " + self.link.arcana + " arcana!")
		
		#self.grid.addWidget(youhave)
		
		self.grid.setAlignment(infoL, Qt.AlignHCenter)
		self.grid.setAlignment(self.aitext, Qt.AlignHCenter)
		self.grid.setAlignment(arcanainfo, Qt.AlignHCenter)
		self.grid.setAlignment(self.save, Qt.AlignRight)
		self.grid.setAlignment(self.back, Qt.AlignLeft)
		
	def saveinfo(self):
		pass
		
	def endedit(self):
		pass
		
		
	def recs(self):
		try:
			self.reqs.close()
		except Exception as e:
			print e
			print "Can't close oudated req widget"
		if self.level.currentText() == "":
			return
		if self.level.itemText(0)=="":
			self.level.removeItem(0)
		
		self.reqs = Requirements(self)
		self.grid.addWidget(self.reqs, 1, 2, 1, 11)
		
		
		
class Requirements(QWidget):
	def __init__(self, op):
		QWidget.__init__(self)
		self.op = op
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.textboxes = {}
		self.eangs = []
		self.courages = []
		self.charms = []
		self.acads = []
		rowi = 1
		for angle in self.op.levang[self.op.level.currentText()]:
			eang = QLabel(self, text=angle)
			self.eangs.append(eang)
			ptb = QLineEdit(self)
			ptb.setFixedSize(20, 20)
			self.textboxes[angle] = ptb
			self.grid.addWidget(QLabel(self, text="Reaching angle"), rowi, 0)
			self.grid.addWidget(self.eangs[-1], rowi, 1)
			self.grid.addWidget(QLabel(self, text="requires"), rowi, 2)
			self.grid.addWidget(self.textboxes[angle], rowi, 3)
			self.grid.addWidget(QLabel(self, text="points and: Courage"), rowi, 4)
			courage = QComboBox(self)
			self.courages.append(courage)
			self.courages[-1].addItems(["1", "2", "3", "4", "5"])
			self.courages[-1].setCurrentIndex(0)
			self.grid.addWidget(self.courages[-1], rowi, 5)
			self.grid.addWidget(QLabel(self, text="Charm"), rowi, 6)
			charm = QComboBox(self)
			self.charms.append(charm)
			self.charms[-1].addItems(["1", "2", "3", "4", "5"])
			self.charms[-1].setCurrentIndex(0)
			self.grid.addWidget(self.charms[-1], rowi, 7)
			self.grid.addWidget(QLabel(self, text="Academics"), rowi, 8)
			acad = QComboBox(self)
			self.acads.append(acad)
			self.acads[-1].addItems(["1", "2", "3", "4", "5"])
			self.acads[-1].setCurrentIndex(0)
			self.grid.addWidget(self.acads[-1], rowi, 9)
			rowi+=1
		
app = QApplication(sys.argv)
sl = SocialLink("Void")
li = LinkInfo(sl, None, None)
li.show()
sys.exit(app.exec_())