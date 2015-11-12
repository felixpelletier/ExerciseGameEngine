import Tkinter
#import FixTk ##Not sure why needed (only for build)
from Tkinter import *
from PIL import Image, ImageTk
from ttk import Button, Style, Entry
from creatures import Character, Persona
import json_reader


class SLFrame(Toplevel):
		
	def __init__(self, pRootWindow):
		self.rootWindow = pRootWindow
		print "Application started"
		Toplevel.__init__(self)
		img = Tkinter.Image("photo", file="icon.gif")
		self.tk.call('wm','iconphoto',self._w,img)
		self.initUI()
		
	def initUI(self):
		self.title("Social Link Creator")
		
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')

		back = Button(self, text="Back", command=self.back)
		back.grid(row=1, column=1, rowspan=2)
		
		base = SLBase(self)
		base.grid(row=0, column=0, rowspan=2)
		
	def back(self):
		self.destroy()
		self.rootWindow.deiconify()
		
		
class SLBase(Frame):
	
	def __init__(self, parent):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.empty = True
		self.index = StringVar(self)
		self.initUI()
		
	def initUI(self):
		actions = [""]	#load here
		self.index.set("")	#load here
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		if self.empty:
			start = Button(self, text="Start New", command=self.newFirst)
			start.grid(row=1, column=1)
		else:
			continueB = Button(self, text="New Action", command=self.new)
			continueB.grid(row=1, column=1)
			
		actOM = OptionMenu(self, self.index, *actions, command=self.enter)
		actOM.config(width=5)
		actOM.grid(row=0, column=0, sticky="ew")
			
	def newFirst(self):
		print "Starting new Social Link"
	
	def new(self):
		print "Switching to action frame"
		
	def enter(self, something):
		if self.index.get() is "":
			print "No valid action selected"
			return
		enter = Button(self, text="Edit", command=self.editFrame)
		enter.grid(row=0, column=1)
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		