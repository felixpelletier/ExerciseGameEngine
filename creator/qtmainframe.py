from PyQt4.QtGui import QApplication, QWidget, QGridLayout, QPushButton, QPixmap, QLabel, QPalette, QLayout
from PyQt4.QtCore import Qt, QRect
import json_reader
from qtop import OP
from chargui import char_creator

class MainFrame(QWidget):
	
	def __init__(self, parent):
		self.parent = parent
		QWidget.__init__(self)
		state = "Opening Screen"
		self.setAutoFillBackground(True)
		self.layout = QGridLayout(self)
		self.setLayout(self.layout)
		self.currentWidget = OP(self)
		self.setPalette(self.currentWidget.palette())
		self.layout.addWidget(self.currentWidget, 0, 0, 2, 2)
		self.layout.setSizeConstraint(QLayout.SetFixedSize)
		self.currentWidget.show()
		self.show()
		
	def changeState(self, newWidgetState):
		self.setPalette(newWidgetState.palette())
		self.currentWidget.hide()
		self.layout.addWidget(newWidgetState, 0, 0)
		self.currentWidget = newWidgetState
		newWidgetState.show()
		self.setFixedSize(self.sizeHint())