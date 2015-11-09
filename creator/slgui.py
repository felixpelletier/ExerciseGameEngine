import Tkinter
#import FixTk ##Not sure why needed (only for build)
from Tkinter import *
from PIL import Image, ImageTk
from ttk import Button, Style, Entry
from creatures import Character, Persona
import json_reader


class SLFrame(Toplevel):
		
	def __init__(self):
		print "Application started"
		Toplevel.__init__(self)
		#self.grid(row=0, column=0)
		#top = Toplevel()
		#dummy = Dummy(self)
		self.initUI()
		
	def initUI(self):
		#self.parent.title("Social Link Creator")
		#self.grid(row=0, column=0)
		
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')

		back = Button(self, text="Back", command=self.back)
		back.grid(row=2, column=1)
		
	def back(self):
		self.destroy()