from qtheader import *
from sls import SocialLink
from action import *
from simulate import Simulation
from slview import PrettySL
from slinfo import LinkInfo

class SLFrame(QWidget):
		
	def __init__(self, mainframe, op, arcana, level, angle):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.arcana = arcana
		self.level = level
		self.angle = angle
		self.linkstored = SocialLink(arcana)
		self.link = self.linkstored.startLink(level, angle)
		self.i = 0
		self.cc = None
		self.initUI()
		
	def initUI(self):
		self.mainframe.setWindowTitle("Social Link Creator")
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		simulate = QPushButton(self, text="Simulate")
		simulate.clicked.connect(self.simulate)
		self.grid.addWidget(simulate, 2, 0)
		
		self.view = QPushButton(self, text="Graphic View")
		self.view.clicked.connect(lambda:self.viewF(True))
		self.grid.addWidget(self.view, 2, 1)
		
		self.info = QPushButton(self, text="Info")
		self.info.clicked.connect(self.infoF)
		self.grid.addWidget(self.info, 2, 2)

		back = QPushButton(self, text="Back to Arcana selection")
		back.clicked.connect(self.back)
		self.grid.addWidget(back, 2, 3)
		
		self.listview = SLBase(self.mainframe, self)
		self.graphicview = None
		
	def back(self):
		self.mainframe.changeState(self.op)
	
	def simulate(self):
		if len(self.link.getIDs())==0:
			popup("Nothing to simulate!", "Information")
			return
		self.sim = Simulation(self.link, self.arcana, self.level, self.angle)
		
	def infoF(self):
		self.mainframe.changeState(LinkInfo(self.mainframe, self, self.linkstored, str(self.level), str(self.angle)))
		
	def viewF(self, graph):
		if graph:
			if len(self.link.getIDs())==0:
				popup("Nothing to show!", "Information")
				return
			self.graphicview = PrettySL(self.mainframe, self)
			self.listview.close()
			if self.cc:
				self.cc.close()
			self.view.setText("List View")
			self.grid.addWidget(self.graphicview, 0, 0, 1, 4)
			self.graphicview.show()
			self.view.clicked.disconnect()
			self.view.clicked.connect(lambda:self.viewF(False))
		else:
			if self.cc:
				self.cc.show()
			else:
				self.listview = SLBase(self.mainframe, self)
			if self.graphicview:
				self.graphicview.close()
			self.view.setText("Graphic View")
			self.grid.addWidget(self.listview, 0, 0, 1, 4)
			self.listview.show()
			self.view.clicked.disconnect()
			self.view.clicked.connect(lambda:self.viewF(True))
		self.mainframe.center()
			
	
	def writeSave():
		self.linkstored.setLink(self.link, self.level, self.angle)
		self.linkstored.save()
		
class SLBase(QWidget):
	
	def __init__(self, mainframe, op):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.empty = True
		self.load = 0
		self.initUI()
		self.op.grid.addWidget(self, 0, 0, 1, 4)
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.actions = self.op.link.getIDs()#load here (load the hash list from sls.py) NOT LOADING FROM SLS BUT MATHGRAPH
		if len(self.actions)>0:
			self.empty = False
		else:
			self.actions.append("")
		
		if self.empty:
			start = QPushButton(self, text="Start New")
			start.clicked.connect(self.changeFrameL)
			self.grid.addWidget(start, 0, 1)

		self.actOM = QComboBox(self)
		self.actOM.addItems(self.actions)
		self.actOM.setCurrentIndex(0)
		self.actOM.activated.connect(self.changeFrameL)
		self.actOM.setMaximumWidth(150)
		self.grid.addWidget(self.actOM, 0, 0)
	#L for local. wtf overload?		
	def changeFrameL(self):
		print self.actOM.currentText()
		if self.actOM.currentText() is not "":
			print "Set to load"
			self.load = self.op.link.getItem(self.actions.index(self.actOM.currentText()))
			print self.load
		self.op.i = self.actions.index(self.actOM.currentText())
		print "Current index: " + str(self.op.i)
		self.close()
		CreationContainer(self.mainframe, self.op, self.load)
		
	#Overloaded for slview
	def changeFrame(self, load, index):
		self.op.i = index
		CreationContainer(self.mainframe, self.op, load)
		
		
class CreationContainer(QWidget):
	
	def __init__(self, mainframe, op, load):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.op.cc = self
		self.load = load
		self.initUI()
		self.op.grid.addWidget(self, 0, 0, 2, 10)
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.actions = self.op.link.getIDs()
		self.actions.append("New element")
		types = ["Info", "Speak", "Camera Change", "Movement"]
		
		self.save = QPushButton(self, text="Save")
		self.grid.addWidget(self.save, 3, 0)
		
		self.existing_connections = QListWidget(self)
		self.populateExistingConnections()
		self.grid.addWidget(self.existing_connections, 1, 5, 2, 1)
		
		self.next = QComboBox(self)
		self.next.addItems(self.actions)
		self.next.setMaximumWidth(150)
		if self.load!=0:
			self.next.setCurrentIndex(self.op.i)
		self.grid.addWidget(self.next, 3, 2)
		
		self.window = None
		
		self.actOM = QComboBox(self)
		self.actOM.addItems(types)
		self.actOM.activated.connect(self.changeFrame)
		self.grid.addWidget(self.actOM, 0, 0, 1, 2)
		
		self.connect()
		self.next.setCurrentIndex(self.next.count()-1)
		
		self.backB = QPushButton(self, text="Back to List Menu")
		self.backB.clicked.connect(self.back)
		self.grid.addWidget(self.backB, 3, 4)
		
		self.lead = QLabel(self, text="Leads to:")
		self.lead.setAlignment(Qt.AlignRight)
		self.grid.addWidget(self.lead, 3, 1)
		
		self.connectB = QPushButton(self, text="Connect")
		self.connectB.clicked.connect(self.lightConnect)
		self.grid.addWidget(self.connectB, 3, 3)
	
		self.follow_path = QPushButton(self, text="Enter linked element")
		self.follow_path.clicked.connect(self.follow)
		self.grid.addWidget(self.follow_path, 0, 6, 2, 1)
		
		self.rmvRel = QPushButton(self, text="Remove this connection")
		self.rmvRel.clicked.connect(self.removeRelation)
		self.grid.addWidget(self.rmvRel, 1, 6, 2, 1)
		
		self.conLab = QLabel(self, text="This action connects to:")
		self.grid.addWidget(self.conLab, 0, 5)
		
	def removeRelation(self):
		if not self.existing_connections.currentItem() or not popup("Are you sure you want to remove this relation? Any elements with a unique dependancy on this relation will also be deleted.\nIt is highly recommended you take a look at the graphical view of the tree in order to see the potential effects of the deletion.", "Warning"):
			return
		self.op.link.delRelation(self.op.i, self.actions.index(self.existing_connections.currentItem().text()))
		self.populateExistingConnections()
		self.updateElementList()
		self.op.linkstored.save()
	
	def populateExistingConnections(self):
		self.existing_connections.clear()
		for relation in self.op.link.getRelations(self.op.i):
			self.existing_connections.addItem(self.op.link.getOneID(self.op.link.getItem(relation)))

	def back(self):
		if not popup("Return to list main menu?\n(Lose any unsaved changes)", "Warning"):
			return
		self.close()
		self.op.cc = None
		self.op.viewF(False)
		
	def follow(self):
		if not self.existing_connections.currentItem() or self.existing_connections.currentItem().text() == "":
			return
		print [self.next.itemText(i) for i in range(self.next.count())].index(self.existing_connections.currentItem().text())
		self.next.setCurrentIndex([self.next.itemText(i) for i in range(self.next.count())].index(self.existing_connections.currentItem().text()))
		self.op.i = self.actions.index(self.next.currentText())
		self.connect()
		self.next.setCurrentIndex(self.next.count()-1)
		
	def lightConnect(self):
		if not self.checkCached():
			popup("Please save this action before linking it to a new one", "Information")
			return
		if self.next.currentText() == "New element":
			self.op.link.addRelation(self.op.i, self.op.link.size())
			print "Linked to index " + str(self.op.link.size())
			self.op.i = self.op.link.size()
			self.load=0
			self.changeFrame(0)
			self.updateElementList()
		else:
			self.op.link.addRelation(self.op.i, self.actions.index(self.next.currentText()))
			print "Linked to index " + str(self.actions.index(self.next.currentText()))
		self.populateExistingConnections()
		
	def connect(self):
		print self.next.currentText()
		if self.next.currentText() == "New element":
			self.load=0
			self.changeFrame(0)
		else:
			if isinstance(self.op.link.getItem(self.actions.index(self.next.currentText())), Info):
				self.actOM.setCurrentIndex(0)
			elif isinstance(self.op.link.getItem(self.actions.index(self.next.currentText())), Speak):
				self.actOM.setCurrentIndex(1)
			elif isinstance(self.op.link.getItem(self.actions.index(self.next.currentText())), Camera):
				self.actOM.setCurrentIndex(2)
			elif isinstance(self.op.link.getItem(self.actions.index(self.next.currentText())), Movement):
				self.actOM.setCurrentIndex(3)
			else:
				raise Exception("Not a type!")
			self.load = self.op.link.getItem(self.actions.index(self.next.currentText()))
			self.changeFrame(0)
			
	def checkCached(self):
		print len(self.op.link.items)-1
		print self.op.i
		if self.op.link.getItem(self.op.i) == []:
			return False
		return True
			
	def updateElementList(self):
		self.next.clear()
		self.actions = self.op.link.getIDs()
		self.actions.append("New element")
		self.next.addItems(self.actions)
		self.next.setCurrentIndex(len(self.actions)-1)
		
	def changeFrame(self, something):
		print "Changed to " + self.actOM.currentText()
		try:
			self.window.close()
		except AttributeError:
			pass#No window open
		if self.actOM.currentText() == "Speak":
			self.window = SpeakFrame(self, self.load)
		elif self.actOM.currentText() == "Camera Change":
			self.window = CameraFrame(self, self.load)
		elif self.actOM.currentText() == "Movement":
			self.window = MoveFrame(self, self.load)
		else:# self.actOM.currentText() == "Info":
			self.window = InfoFrame(self, self.load)
		try:
			self.save.clicked.disconnect()
		except:
			pass
		self.save.clicked.connect(self.window.save)
		self.populateExistingConnections()
		self.updateElementList()
			
class InfoFrame(QWidget):

	def __init__(self, op, load):
		QWidget.__init__(self)
		self.op = op
		self.load = load
		self.initUI()
		self.op.grid.addWidget(self, 1, 0, 1, 5)
		
	def initUI(self):		
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.infoBox = QTextEdit(self)
		self.infoBox.setFixedSize(300, 150)
		self.grid.addWidget(self.infoBox, 1, 0, 1, 5)
		
		print self.load
		if self.load!=0:
			try:
				self.infoBox.setText(self.load.getText())
			except Exception as e:
				print e
				pass
		
	def save(self):
		print "Saving"
		infoSlide = Info()
		print "..."
		infoSlide.setText(self.infoBox.toPlainText())
		print self.op.op.i
		self.op.op.link.addItem(infoSlide, self.op.op.i)
		print "Saved"
		self.op.op.linkstored.setLink(self.op.op.link, self.op.op.level, self.op.op.angle)
		self.op.op.linkstored.save()
		self.op.updateElementList()
		popup("Saved!", "Information")
		
class SpeakFrame(QWidget):
	
	def __init__(self, op, load):
		QWidget.__init__(self)
		self.op = op
		self.load = load
		self.pointvec = []
		self.pointvar = []
		self.anglevec = []
		self.anglevar = []
		self.addPAtIndex = 4
		self.addAAtIndex = 4
		self.initUI()
		self.op.grid.addWidget(self, 1, 0, 1, 5)
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.characs = json_reader.readCharNames()
		self.arcanas = json_reader.data_list("arcanas")
		self.arcanas.extend([""])
		
		self.textl = QLabel(self, text="Text:")
		self.grid.addWidget(self.textl, 1, 0)
		
		self.infoBox = QTextEdit(self)
		self.infoBox.setFixedSize(300, 150)
		self.grid.addWidget(self.infoBox, 1, 1, 3, 3)
		
		self.textl = QLabel(self, text="Points:")
		self.grid.addWidget(self.textl, 2, 4, 1, 2)
		
		self.pointBox = QLineEdit(self)
		self.pointBox.setFixedSize(20, 20)
		self.grid.addWidget(self.pointBox, 3, 4)
		self.pointvec.append(self.pointBox)
		
		pointOM = QComboBox(self)
		pointOM.addItems(self.arcanas)
		pointOM.setCurrentIndex(pointOM.count()-1)
		self.grid.addWidget(pointOM, 3, 5)
		self.pointvar.append(pointOM)
		
		self.textl = QLabel(self, text="Angle:")
		self.grid.addWidget(self.textl, 2, 6, 1, 2)
		
		angleBox = QLineEdit(self)
		angleBox.setFixedSize(20, 20)
		self.grid.addWidget(angleBox, 3, 6)
		self.anglevec.append(angleBox)
		
		angleOM = QComboBox(self)
		angleOM.addItems(self.arcanas)
		angleOM.setCurrentIndex(angleOM.count()-1)
		self.grid.addWidget(angleOM, 3, 7)
		self.anglevar.append(angleOM)
		
		self.speakerl = QLabel(self, text="Speaker:")
		self.grid.addWidget(self.speakerl, 1, 4)
		

		self.speaker = QComboBox(self)
		self.speaker.addItems(self.characs)
		self.grid.addWidget(self.speaker, 1, 5)
		
		self.emotionL = QLabel(self, text="Emotion:")#emotionL memes
		self.grid.addWidget(self.emotionL, 1, 6)
		self.s_emotions = json_reader.data_list('sprite_emotions')
		self.emotion = QComboBox(self)
		self.emotion.addItems(self.s_emotions)
		self.grid.addWidget(self.emotion, 1, 7)		
		
		self.addp = QPushButton(self, text="Add points")
		self.addp.clicked.connect(self.extendP)
		self.grid.addWidget(self.addp, 30, 4, 1, 2)
		
		self.adda = QPushButton(self, text="Add angles")
		self.adda.clicked.connect(self.extendA)
		self.grid.addWidget(self.adda, 30, 6, 1, 2)
		
		if self.load != 0:
			try:
				self.infoBox.setText(self.load.getText())
				self.speaker.setCurrentIndex(self.characs.index(self.load.getSpeaker()))
				self.emotion.setCurrentIndex(self.s_emotions.index(self.load.emotion))
				first = True
				for arcana, points in self.load.getPoints().iteritems():
					if first:
						first = False
					else:
						self.extendP()
					self.pointvec[-1].setText(str(points))
					self.pointvar[-1].setCurrentIndex(self.arcanas.index(arcana))
				first = True
				for arcana, angle in self.load.getAngle().iteritems():
					if first:
						first = False
					else:
						self.extendA()
					self.anglevec[-1].setText(str(angle))
					self.anglevar[-1].setCurrentIndex(self.arcanas.index(arcana))
			except Exception as e:
				print e
				pass
			
			
		
	def extendP(self):
		self.pointvec.extend([QLineEdit(self)])
		self.pointvec[-1].setFixedSize(20, 20)
		self.pointvar.extend([QComboBox(self)])
		self.grid.addWidget(self.pointvec[-1], self.addPAtIndex, 4)
		self.pointvar[-1].addItems(self.arcanas)
		self.pointvar[-1].setCurrentIndex(self.pointvar[-1].count()-1)
		self.grid.addWidget(self.pointvar[-1], self.addPAtIndex, 5)
		self.addPAtIndex+=1
		
	def extendA(self):
		self.anglevec.extend([QLineEdit(self)])
		self.anglevec[-1].setFixedSize(20, 20)
		self.anglevar.extend([QComboBox(self)])
		self.grid.addWidget(self.anglevec[-1], self.addAAtIndex, 6)
		self.anglevar[-1].addItems(self.arcanas)
		self.anglevar[-1].setCurrentIndex(self.anglevar[-1].count()-1)
		self.grid.addWidget(self.anglevar[-1], self.addAAtIndex, 7)
		self.addAAtIndex+=1
		
	def save(self):
		print "Saving"
		print "..."
		speakSlide = Speak()
		speakSlide.setText(self.infoBox.toPlainText())
		speakSlide.setSpeaker(self.speaker.currentText())
		speakSlide.emotion=self.emotion.currentText()
		for i in xrange(len(self.pointvec)):
			if(self.pointvar[i].currentText()!=""):
				try:
					amount = (int)(self.pointvec[i].text())
					speakSlide.putPoints(self.pointvar[i].currentText(), amount)
				except:
					popup("All Points must be integers.\nTo discard one line, empty the text field and set the arcana to blank.", "Critical")
					print "Amount must be an integer"
		for i in xrange(len(self.anglevec)):
			if(self.anglevar[i].currentText()!=""):
				try:
					amount = (int)(self.anglevec[i].text())
					speakSlide.putAngle(self.anglevar[i].currentText(), amount)
				except:
					popup("All Points and Angles must be integers.\nTo discard one line, set empty the text field and set the arcana to blank.", "Critical")
					print "Amount must be an integer"
		self.op.op.link.addItem(speakSlide, self.op.op.i)
		print "Saved"
		self.op.op.linkstored.setLink(self.op.op.link, self.op.op.level, self.op.op.angle)
		self.op.op.linkstored.save()
		self.op.updateElementList()
		popup("Saved!", "Information")
		
		
class CameraFrame(QWidget):
	
	def __init__(self, op, load):
		QWidget.__init__(self)
		self.op = op
		self.load = load
		self.initUI()
		self.op.grid.addWidget(self, 1, 0, 1, 5)
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.locations = json_reader.data_list("locations")
		
		self.textl = QLabel(self, text="Camera's position x:")
		self.grid.addWidget(self.textl, 1, 0)
		
		self.cx = QLineEdit(self)
		self.cx.setFixedSize(20, 20)
		self.grid.addWidget(self.cx, 1, 1)
		
		self.textl = QLabel(self, text="Camera's position y:")
		self.grid.addWidget(self.textl, 2, 0)
		
		self.cy = QLineEdit(self)
		self.cy.setFixedSize(20, 20)
		self.grid.addWidget(self.cy, 2, 1)
		
		self.textl = QLabel(self, text="Camera's position z:")
		self.grid.addWidget(self.textl, 3, 0)
		
		self.cz = QLineEdit(self)
		self.cz.setFixedSize(20, 20)
		self.grid.addWidget(self.cz, 3, 1)
		
		self.textl = QLabel(self, text="Look at x:")
		self.grid.addWidget(self.textl, 1, 2)
		
		self.lx = QLineEdit(self)
		self.lx.setFixedSize(20, 20)
		self.grid.addWidget(self.lx, 1, 3)
		
		self.textl = QLabel(self, text="Look at y:")
		self.grid.addWidget(self.textl, 2, 2)
		
		self.ly = QLineEdit(self)
		self.ly.setFixedSize(20, 20)
		self.grid.addWidget(self.ly, 2, 3)
		
		self.textl = QLabel(self, text="Look at z:")
		self.grid.addWidget(self.textl, 3, 2)
		
		self.lz = QLineEdit(self)
		self.lz.setFixedSize(20, 20)
		self.grid.addWidget(self.lz, 3, 3)
		
		self.locationl = QLabel(self, text="Location:")
		self.grid.addWidget(self.locationl, 1, 4)
		
		self.locationO = QComboBox(self)
		self.locationO.addItems(self.locations)
		self.locationO.setCurrentIndex(0)
		self.grid.addWidget(self.locationO, 1, 5)
		
		if self.load != 0:
			try:
				self.locationO.setCurrentIndex(self.locations.index(self.load.getPlace()))
				cp = self.load.getCameraPosition()
				la = self.load.getLookAt()
				self.cx.setText(str(cp[0]))
				self.cy.setText(str(cp[1]))
				self.cz.setText(str(cp[2]))
				self.lx.setText(str(la[0]))
				self.ly.setText(str(la[1]))
				self.lz.setText(str(la[2]))
			except Exception as e:
				print e
				pass
		
			
	def save(self):
		print "Saving"
		cameraSlide = Camera()
		cameraSlide.setPlace(self.locationO.currentText())
		print "..."
		try:
			(int)(self.lx.text())
			(int)(self.ly.text())
			(int)(self.lz.text())
			(int)(self.cx.text())
			(int)(self.cy.text())
			(int)(self.cz.text())
		except:
			popup("Camera position (x, y, z) and look direction (x, y, z) must be entered as whole numbers", "Critical")
			print "Must be an integer"
			return
		
		cameraSlide.setLookAt(((int)(self.lx.text()),(int)(self.ly.text()),(int)(self.lz.text())))
		cameraSlide.setCameraPosition(((int)(self.cx.text()),(int)(self.cy.text()),(int)(self.cz.text())))
		self.op.op.link.addItem(cameraSlide, self.op.op.i)
		print "Saved"
		self.op.op.linkstored.setLink(self.op.op.link, self.op.op.level, self.op.op.angle)
		self.op.op.linkstored.save()
		self.op.updateElementList()
		popup("Saved!", "Information")
		
		
class MoveFrame(QWidget):
	
	def __init__(self, op, load):
		QWidget.__init__(self)
		self.op = op
		self.load = load
		self.initUI()
		self.op.grid.addWidget(self, 1, 0, 1, 5)
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.animations = json_reader.data_list("animations")
		self.characs = json_reader.readCharNames()
		
		self.textl = QLabel(self, text="Go to x:")
		self.grid.addWidget(self.textl, 1, 0)
		
		self.lx = QLineEdit(self)
		self.lx.setFixedSize(20, 20)
		self.grid.addWidget(self.lx, 1, 1)
		
		self.textl = QLabel(self, text="Go to y:")
		self.grid.addWidget(self.textl, 2, 0)
		
		self.ly = QLineEdit(self)
		self.ly.setFixedSize(20, 20)
		self.grid.addWidget(self.ly, 2, 1)
		
		self.speakerl = QLabel(self, text="Person:")
		self.grid.addWidget(self.speakerl, 1, 3)
		
		self.speaker = QComboBox(self)
		self.speaker.addItems(self.characs)
		self.speaker.setCurrentIndex(0)
		self.grid.addWidget(self.speaker, 1, 4)
		
		self.anil = QLabel(self, text="Animation:")
		self.grid.addWidget(self.anil, 2, 3)
		
		self.ani = QComboBox(self)
		self.ani.addItems(self.animations)
		self.ani.setCurrentIndex(self.animations.index("Idle"))
		self.grid.addWidget(self.ani, 2, 4)
		
		if self.load != 0:
			try:
				self.ani.setCurrentIndex(self.animations.index(self.load.getAnimation()))
				self.speaker.setCurrentIndex(self.characs.index(self.load.getSubject()))
				self.lx.setText(self.load.getDestination()[0])
				self.ly.setText(self.load.getDestination()[1])
			except Exception as e:
				print e
				pass
		
		
	def save(self):
		print "Saving"
		moveSlide = Movement()
		moveSlide.setSubject(self.speaker.currentText())
		moveSlide.setAnimation(self.ani.currentText())
		print "..."
		try:
			(int)(self.lx.text())
			(int)(self.ly.text())
		except:
			popup("Destination coordinates (x, y) must be entered as integers", "Critical")
			print "Numbers must be integers"
			return
		
		moveSlide.setDestination(((int)(self.lx.text()),(int)(self.ly.text())))
		self.op.op.link.addItem(moveSlide, self.op.op.i)
		print "Saved"
		self.op.op.linkstored.setLink(self.op.op.link, self.op.op.level, self.op.op.angle)
		self.op.op.linkstored.save()
		self.op.updateElementList()
		popup("Saved!", "Information")
		