from qtheader import *
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
		self.actions = self.graph.getIDs()
		self.maxDepth = len(self.actions) #Not used
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.enter = QPushButton(self, text="Edit")
		self.grid.addWidget(self.enter, 0, 0)
		
		self.showTree = QPushButton(self, text="Show Tree")
		self.grid.addWidget(self, 0, 1)
		
		self.delete = QPUshButton(self, text="Delete")
		
		self.back = QPushButton(self, text="Back")
		self.back.clicked.connect(self.backF)
		self.grid.addWidget(self.back, 0, 3)
		
		print "Opened"
		
		self.tree = TreeWidget(self.actions, self.table)
		self.grid.addWidget(self.tree, 1, 0, 1, 4)
		
	def backF(self):
		self.close()
		
		
class TreeWidget(QWidget):
	
	def __init__(self, actions, table):
		QWidget.__init__(self)
		self.actions = actions
		self.table = table
		
		self.currentDepth = 0
		
		self.initUI()
		
	def initUI(self):
		self.grid = QGridLayout()
		self.setLayout(self.grid)
		
		self.processed = []
		self.diag = []
		self.needsLine = []
		self.depthTracker = {}
		self.buttons = []
		
		self.nextRow(self.table[0][1:len(self.table[0])], 0)
		
		print self.diag
		print ""
		print ""
		print ""
		print ""
		print ""
		print ""
		print self.needsLine
		print ""
		print ""
		print ""
		print ""
		print ""
		print ""
		print self.depthTracker			
	
	def nextRow(self, currentAction, currentDepth):
		print "Infinite Loop"
		for relation in currentAction:
			if relation not in self.processed:
				self.processed.append(relation)
				self.map.append((relation, currentDepth))
				try:
					self.depthTracker[currentDepth]+=1
				except KeyError:
					self.depthTracker[currentDepth] = 1
				self.nextRow(self, self.table[relation][1:len(self.table[relation])], currentDepth+1)
			else:
				self.needsLine.append(self.actions.index(currentAction), relation)
		
	
		"""LEGACY IDEAS
		self.nextRowActions = []
		for action in currentRowActions:
			if action not in self.processed:
				self.nextRowActions.extend([self.table[i][0] for i in self.table[self.table.index(action)][1:len(self.table[self.table.index(action)])]])
			else:
				self.needsLine.append((self.table))
		"""
app = QApplication(sys.argv)
psl = PrettySL(None, None, SocialLink("Void").startLink(1, 0))
psl.show()
sys.exit(app.exec_())