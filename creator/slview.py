from qtheader import *
from PyQt4.QtGui import QHBoxLayout, QPen, QPainter, QBrush
from PyQt4.QtCore import QPoint, QRectF
from sls import SocialLink
import sys

class PrettySL(QWidget):

	def __init__(self, mainframe, op):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.graph = self.op.link
		self.table = self.op.link.items
		self.lastButtonPressed = False
		self.subtree = []
		self.initData()
		self.initUI()
		
		
	def initData(self):
		self.lab = None
		self.actionIDs = self.graph.getIDs()
		self.actionObjs = []
		for act in self.table:
			self.actionObjs.append(act[0])
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)

		self.tree = TreeWidget(self, self.actionObjs, self.actionIDs, self.table)
		self.grid.addWidget(self.tree, 0, 0, 10, 3)
		
		self.legend = Legend(self)
		self.grid.addWidget(self.legend, 0, 3, 1, 2)
		
		self.setWindowModality(Qt.ApplicationModal)
		self.show()
		
	def trackIndex(self, index):
		print "Called"
		self.lastButtonPressed = True
		self.subtree = self.graph.subTree(index)
		print self.subtree
		self.initInfoUI(index)
		
	def initInfoUI(self, index):
		if not self.lab:
			self.lab = QLabel(self, text="Selected element summary:")
			self.grid.addWidget(self.lab, 1, 3, 1, 2)
			self.idLabel = QLabel(self, text=self.actionIDs[index])
			self.idLabel.setFixedSize(350, 40)
			self.idLabel.setWordWrap(True)
			self.grid.addWidget(self.idLabel, 2, 3, 1, 2)
			self.edit = QPushButton(self, text="Edit")
			self.edit.clicked.connect(lambda:self.enter(index))
			self.grid.addWidget(self.edit, 3, 3, 1, 2)
		else:
			self.idLabel.setText(self.actionIDs[index])
			self.edit.clicked.disconnect()
			self.edit.clicked.connect(lambda:self.enter(index))
		
	def enter(self, index):
		load = self.graph.getItem(index)
		self.close()
		self.op.view.setText("Graphic View")
		self.op.view.clicked.disconnect()
		self.op.view.clicked.connect(lambda:self.op.viewF(True))
		self.op.listview.changeFrame(load, index)

		
		
class Legend(QWidget):
	
	def __init__(self, op):
		QWidget.__init__(self)
		self.op = op
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.lab = QLabel(self, text="Legend")
		self.grid.addWidget(self.lab, 0, 0, 1, 2)
		
		self.dd = QLabel(self, text="Downstream dependancy:")
		self.grid.addWidget(self.dd, 1, 0)
		
		self.ud = QLabel(self, text="Upstream dependancy:")
		self.grid.addWidget(self.ud, 2, 0)
		
		self.unid = QLabel(self, text="Unique dependancy:")
		self.grid.addWidget(self.unid, 3, 0)
		
		empty = QLabel(self)
		empty.setFixedSize(100, 20)
		self.grid.addWidget(empty, 1, 1)
		self.grid.addWidget(empty, 2, 1)
		self.grid.addWidget(empty, 3, 1)
		
	def paintEvent(self, event):
		qp = QPainter()
		qp.begin(self)
		self.drawLines(qp)
		qp.end()
		
	def drawLines(self, qp):
		pen = QPen(Qt.black, 2, Qt.SolidLine)
		qp.setPen(pen)
		
		qp.drawRect(self.lab.x()-5, self.lab.y()-5, 275, 100)
		
		qp.drawLine(self.dd.x()+155, self.dd.y()+5, self.dd.x()+250, self.dd.y()+5)
		pen.setStyle(Qt.DashLine)
		qp.setPen(pen)
		qp.drawLine(self.ud.x()+155, self.ud.y()+5, self.ud.x()+250, self.ud.y()+5)
		pen.setStyle(Qt.SolidLine)
		pen.setColor(Qt.red)
		qp.setPen(pen)
		qp.drawLine(self.unid.x()+155, self.unid.y()+5, self.unid.x()+250, self.unid.y()+5)
		
class TreeWidget(QWidget):
	
	def __init__(self, op, actions, ids, table):
		QWidget.__init__(self)
		self.actions = actions
		self.ids = ids
		self.table = table
		self.op = op
		
		self.currentDepth = 0
		
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.processed = []
		self.map = [(0, 0)]
		self.needsLine = []
		self.depthTracker = {}
		self.buttons = []
		
		self.nextRow(self.table[0], 1)
		
		print self.map
		print ""
		print ""
		print ""
		print self.needsLine
		print ""
		print ""
		print ""
		print self.depthTracker
		
		self.placedInLine = {}
		self.lineWidgets = {}
		self.buttons = {}
		
		for element in self.map:
			if element[1] not in self.lineWidgets:
				self.lineWidgets[element[1]] = (QWidget(), QHBoxLayout())
				self.lineWidgets[element[1]][0].setLayout(self.lineWidgets[element[1]][1])
			tempB = QPushButton(self.lineWidgets[element[1]][0], text=self.ids[element[0]])
			tempB.setFixedSize(150, 20)
			tempB.clicked.connect(lambda ignore, ind=element[0]:self.op.trackIndex(ind))
			self.lineWidgets[element[1]][1].addWidget(tempB)
			self.buttons[element[0]] = tempB
		for lineNumber, widget in self.lineWidgets.iteritems():
			self.grid.addWidget(widget[0], lineNumber, 0)
		
	
	def nextRow(self, currentAction, currentDepth):
		for relation in currentAction[1:len(currentAction)]:
			if relation not in self.processed:
				print self.processed
				print (relation, currentDepth)
				self.processed.append(relation)
				self.map.append((relation, currentDepth))
				try:
					self.depthTracker[currentDepth]+=1
				except KeyError:
					self.depthTracker[currentDepth] = 1
				self.nextRow(self.table[relation], currentDepth+1)
			self.needsLine.append((self.actions.index(currentAction[0]), relation))
		
	def paintEvent(self, event):
		qp = QPainter()
		qp.begin(self)
		self.drawLines(qp)
		qp.end()
		
	def drawLines(self, qp):
		pen = QPen(Qt.black, 2, Qt.SolidLine)
		qp.setPen(pen)
		# Can be used to test drawing lines between specific actions. Keep for now.
		#ifrom = self.mapToTree(self.needsLine[0][0])
		#ito = self.mapToTree(self.needsLine[0][1])
		#qp.drawLine(ifrom.x(), ifrom.y(), ito.x(), ito.y())
		alternate = True
		for line in self.needsLine:
			ifrom = self.mapToTree(line[0])
			ito = self.mapToTree(line[1])
			if line[0] in self.op.subtree or line[1] in self.op.subtree:
				pen.setColor(Qt.red)
				qp.setPen(pen)
				if line[0] in self.op.subtree:
					qp.drawRect(ifrom.x()-6, ifrom.y()-7.5, 150, 20)
				if line[1] == self.map[-1][0]:
					qp.drawRect(ito.x()-6, ito.y()-7.5, 150, 20)
			if self.op.lastButtonPressed:
				self.update()
				self.op.lastButtonPressed=False
			if line[0]+1 == line[1]:
				qp.drawLine(ifrom.x()+40, ifrom.y(), ito.x()+40, ito.y())
			elif line[0] > line[1]:
				pen.setStyle(Qt.DashLine)
				qp.setPen(pen)
				if alternate:
					qp.drawArc(QRectF(ito.x(), ito.y(), 100, ifrom.y()-ito.y()), 90*16, 180*16)
					alternate=False
				else:
					qp.drawArc(QRectF(ito.x(), ito.y(), 100, ifrom.y()-ito.y()), 270*16, 180*16)
					alternate=True
				pen.setStyle(Qt.SolidLine)
			pen.setColor(Qt.black)
			qp.setPen(pen)
				
		
		
	def mapToTree(self, index):
		p = QPoint(self.buttons[index].x(), self.buttons[index].y())
		return self.buttons[index].mapTo(self, p)
		
"""TESTS
app = QApplication(sys.argv)
psl = PrettySL(None, None, SocialLink("Void").startLink(1, 0))
psl.show()
sys.exit(app.exec_())
"""