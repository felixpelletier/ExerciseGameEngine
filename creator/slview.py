from qtheader import *
from PyQt4.QtGui import QHBoxLayout, QPen, QPainter, QBrush
from PyQt4.QtCore import QPoint, QRectF
from sls import SocialLink
import sys

class PrettySL(QWidget):

	def __init__(self, mainframe, op, graph):
		QWidget.__init__(self)
		self.mainframe = mainframe
		self.op = op
		self.graph = graph
		self.table = graph.items
		#self.mainframe.setWindowTitle("Social Link Viewer")
		self.initData()
		self.initUI()
		
		
	def initData(self):
		self.actionIDs = self.graph.getIDs()
		self.actionObjs = []
		for act in self.table:
			self.actionObjs.append(act[0])
		self.maxDepth = len(self.actionIDs) #Not used
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.enter = QPushButton(self, text="Edit")
		self.grid.addWidget(self.enter, 0, 0)
		
		self.showTree = QPushButton(self, text="Show Tree")
		self.grid.addWidget(self.showTree, 0, 1)
		
		#self.delete = QPushButton(self, text="Delete")
		
		self.back = QPushButton(self, text="Back")
		self.back.clicked.connect(self.backF)
		self.grid.addWidget(self.back, 0, 3)
		
		self.tree = TreeWidget(self.actionObjs, self.actionIDs, self.table)
		self.grid.addWidget(self.tree, 1, 0, 1, 4)
		
		self.setWindowModality(Qt.ApplicationModal)
		self.show()
		
	def backF(self):
		self.close()
		
		
class TreeWidget(QWidget):
	
	def __init__(self, actions, ids, table):
		QWidget.__init__(self)
		self.actions = actions
		self.ids = ids
		self.table = table
		
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
		
		#"""FATAL FLAW FOR LINE DRAW
		for element in self.map:
			if element[1] not in self.lineWidgets:
				self.lineWidgets[element[1]] = (QWidget(), QHBoxLayout())
				self.lineWidgets[element[1]][0].setLayout(self.lineWidgets[element[1]][1])
			tempB = QPushButton(self.lineWidgets[element[1]][0], text=self.ids[element[0]])
			tempB.setFixedSize(150, 20)
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
		
		#ifrom = self.mapToTree(self.needsLine[0][0])
		#ito = self.mapToTree(self.needsLine[0][1])
		#qp.drawLine(ifrom.x(), ifrom.y(), ito.x(), ito.y())
		alternate = True
		for line in self.needsLine:
			ifrom = self.mapToTree(line[0])
			ito = self.mapToTree(line[1])
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