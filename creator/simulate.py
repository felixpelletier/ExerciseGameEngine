from qtheader import *
import sys
from logictree import MathGraph
from action import *


class Simulation(QApplication):
	
	def __init__(self, link, arcana, level, angle):
		QApplication.__init__(self, sys.argv)
		#self.quitOnLastWindowClosed()
		self.start(link, arcana, level, angle)

	def start(self, link, arcana, level, angle):
		# The QWidget widget is the base class of all user interface objects in PyQt4.
		w = QWidget()
		# Set window title
		w.setWindowTitle(arcana + " Social Link Level: " + str(level) + " Angle: " + str(angle))	
	
		grid = QGridLayout()
		w.setLayout(grid)
		
		self.label = None
		self.next = None
		self.responses = []
		
		self.action(w, grid, link.items, 0)
	
		quit = QPushButton("Quit", w)
		quit.clicked.connect((lambda:self.shutdown(w))) #
		grid.addWidget(quit, 1000, 0)
	
		# Show window
		w.show()
		
		self.exec_()
		
	def shutdown(self, w):
		w.close()
		w.destroy()
		self.quit()
		del self
		
	def action(self, w, grid, link, currentIndex):
		if not self.label:
			self.label = QLabel(parent=w)
		if isinstance(link[currentIndex][0], Info):
			actionText = link[currentIndex][0].text
		elif isinstance(link[currentIndex][0], Speak):
			actionText = link[currentIndex][0].speaker+":\n\n"+link[currentIndex][0].text
		elif isinstance(link[currentIndex][0], Camera):
			actionText = "Camera is being changed in/to " + link[currentIndex][0].place
		elif isinstance(link[currentIndex][0], Movement):
			actionText = link[currentIndex][0].subject + " is performing a " + link[currentIndex][0].animation +" action"
		else:
			actionText = "ERROR READING SOCIAL LINK\nACTION INDEX: " + currentIndex
		self.label.setText(actionText)
		grid.addWidget(self.label, 0, 0)
		
		if len(link[currentIndex]) == 2:
			if len(self.responses!=0):
				for button in self.responses:
					button.destroy()
				self.responses = []
			if not self.next:
				self.next = QPushButton("Next", w)
				grid.addWidget(self.next, 1, 0)
			self.next.clicked.connect((lambda:self.action(w, grid, link, link[currentIndex][1])))
		elif len(link[currentIndex]) > 2:
			if self.next:
				self.next.destroy()
				self.next = None
			for relation in link[currentIndex][1:]:
				self.responses.append(QPushButton(link.getOneID(link.getItem(relation)), w))
				grid.addWidget(self.responses[-1], len(self.responses), 0)
				self.responses[-1].clicked.connect((lambda:self.action(w, grid, link, link[relation][1])))
		else:
			pass
			
