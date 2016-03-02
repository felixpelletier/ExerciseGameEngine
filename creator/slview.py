from qtheader import *
from PyQt4.QtGui import QHBoxLayout
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
		self.map = []
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
		
		for element in self.map:
			if element[1] not in self.lineWidgets:
				self.lineWidgets[element[1]] = (QWidget(), QHBoxLayout())
				self.lineWidgets[element[1]][0].setLayout(self.lineWidgets[element[1]][1])
			tempB = QPushButton(self.lineWidgets[element[1]][0], text=self.ids[element[0]])
			self.lineWidgets[element[1]][1].addWidget(tempB)
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
		

app = QApplication(sys.argv)
psl = PrettySL(None, None, SocialLink("Void").startLink(1, 0))
psl.show()
sys.exit(app.exec_())