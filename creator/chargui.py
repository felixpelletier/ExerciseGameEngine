from PyQt4.QtGui import QApplication, QWidget, QGridLayout, QPushButton, QPixmap, QLabel, QPalette, QSizePolicy
from PyQt4.QtCore import Qt, QRect
from creatures import Character, Persona
import json_reader
from popup import popup

class char_creator(QWidget):

	def __init__(self, parent):
		QWidget.__init__(self)
		self.parent = parent
		self.var = IntVar()
		self.variable = StringVar(self)
		self.nameT = None
		self.infoT = None
		self.importantB = None
		self.initUI()
	
	def initUI(self):
		self.parent.title("Persona Creator")
		self.grid(row=0, column=0)
		
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		nameL = Label(self, text="Name:")
		nameL.grid(row=1, column=1)
		
		self.nameT = Text(self, height=1, width=25)
		self.nameT.grid(row=1, column=2)
		
		self.importantB = Checkbutton(self, text="Important?", variable=self.var)
		self.importantB.grid(row=1, column=3)
		
		infoL = Label(self, text="Info:")
		infoL.grid(row=2, column=1)
		
		self.infoT = Text(self, height=7, width=50, wrap=WORD)
		self.infoT.grid(row=2, column=2, columnspan=2)
		
		save = Button(self, text="Save", command=self.save)
		save.grid(row=4, column=1)
		
		edit = Button(self, text="Remove", command=self.remove)
		edit.grid(row=4, column=2)
		
		back = Button(self, text="Back", command=self.back)
		back.grid(row=4, column=3)
		
		names = json_reader.readCharNames()
		names.append("New")
		self.variable.set("New") # default value
		if len(names) == 1:
			w = OptionMenu(self, self.variable, "New", command=self.loadChar)
		else:
			w = OptionMenu(self, self.variable, *names, command=self.loadChar)
		w.grid(row=4, column=4)
	
	def loadChar(self, name):
		print "Loading..."
		self.importantB.deselect()
		self.nameT.delete(1.0, END)
		self.infoT.delete(1.0, END)
		if name == "New":
			return
		charTL = json_reader.readOne(name)
		if(charTL.getImportant()):
			self.importantB.select()
		self.nameT.insert(1.0, charTL.getName())
		self.infoT.insert(1.0, charTL.getDesc())
		print "Loaded character " + self.variable.get()
	
	def remove(self):
		if not popup("Are you certain you want to completely remove this character?\n(Cannot be undone)", "Warning"):
			return
		print "Removing character " + self.variable.get()
		json_reader.deleteChar(self.variable.get())
		self.initUI()
		self.importantB.deselect()
		print "Changed to edit frame"
	
	def save(self):
		if self.nameT.get(1.0, END).replace("\n", "") in ["New", ""]:
			popup("Sorry, your character cannot be called \""+self.nameT.get(1.0, END).replace("\n", "")+"\". That is a reserved keyword (and it's also a dumb name)", "Critical")
			return
		print "Saving"
		toWrite = Character(self.nameT.get(1.0, END).replace("\n", ""), self.infoT.get(1.0, END).replace("\n", ""), self.var.get())
		json_reader.writeOne(toWrite)
		temp = self.nameT.get(1.0, END).replace("\n", "")
		self.initUI()
		self.loadChar(temp)
		self.variable.set(temp)
		print "Saved"
		
	def back(self):
		self.close()
		print "Returned to main screen"
		self.parent.open()