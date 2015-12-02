import Tkinter
#import FixTk ##Not sure why needed (only for build)
from Tkinter import *
from PIL import Image, ImageTk
from ttk import Button, Style, Entry
from creatures import Character, Persona
from action import *
from sls import *
import json_reader


class SLFrame(Toplevel):
		
	def __init__(self, pRootWindow, arcana, level, angle):
		self.rootWindow = pRootWindow
		print "Application started"
		Toplevel.__init__(self)
		img = Tkinter.Image("photo", file="icon.gif")
		self.tk.call('wm','iconphoto',self._w,img)
		self.link = SocialLink(arcana).startLink(level, angle)
		self.i = 0
		self.initUI()
		
	def initUI(self):
		self.title("Social Link Creator")
		
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')

		back = Button(self, text="Back to Arcana selection", command=self.back)
		back.grid(row=1, column=1, rowspan=2)
		
		SLBase(self)
		
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
		self.grid(row=0, column=0, rowspan=2)
		
	def initUI(self):
		self.actions = [""]	#load here (load the hash list from sls.py)
		self.index.set("")	#load here
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		if len(self.actions)!=1:
			self.empty = False#Tests
		
		if self.empty:
			start = Button(self, text="Start New", command=self.changeFrame)
			start.grid(row=1, column=1)
			
		actOM = OptionMenu(self, self.index, *self.actions, command=self.enter)
		actOM.config(width=5)
		actOM.grid(row=0, column=0, sticky="ew")
			
	def changeFrame(self):
		print "Starting new Social Link"
		self.destroy()
		self.parent.i = self.actions.index(self.index.get())
		print self.parent.i
		CreationContainer(self.parent)
		
	def enter(self, something):
		if self.index.get() is "":
			print "No valid action selected"
			return
		self.parent.i = self.actions.index(self.index.get())
		enter = Button(self, text="Edit", command=self.changeFrame)
		enter.grid(row=0, column=1)
		
		
		
class CreationContainer(Frame):
	
	def __init__(self, parent):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.type = StringVar(self)
		self.connection = StringVar(self)
		self.load = 0
		self.initUI()
		self.grid(row=0, column=0, rowspan=2)
		
	def initUI(self):
		self.actions = ["New element"]
		types = ["Info", "Speak", "Camera Change", "Movement"]
		self.type.set("Info")
		self.connection.set("New element")
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		self.window = InfoFrame(self, self.load)
		
		actOM = OptionMenu(self, self.type, *types, command=self.changeFrame)
		actOM.config(width=5)
		actOM.grid(row=0, column=0, columnspan=2, sticky="ew")
		
		self.back = Button(self, text="Back", command=self.back)
		self.back.grid(row=2, column=4)
		
		self.save = Button(self, text="Save", command=self.window.save)
		self.save.grid(row=2, column=0)
		
		self.lead = Label(self, text="Leads to:")
		self.lead.grid(row=2, column=1)
		
		self.next = OptionMenu(self, self.connection, *self.actions)
		self.next.grid(row=2, column=2)
		
		self.connect = Button(self, text="Connect", command=self.connect)
		self.connect.grid(row=2, column=3)
		
	def back(self):
		print "Back"
		self.destroy()
		SLBase(self.parent)
		
	def connect(self):
		if self.connection.get() == "New element":
			self.parent.link.addRelation(self.parent.i, self.parent.link.size())
			print "Linked to index " + str(self.parent.link.size())
			self.parent.i = self.parent.link.size()
			self.load=0
			self.changeFrame(0)
		else:
			self.parent.link.addRelation(self.parent.i, self.actions.index(self.connection.get()))
			print "Linked to index " + self.actions.index(self.connection.get())
			self.parent.i = self.actions.index(self.connection.get())
			if isinstance(self.parent.link.getItem(self.actions.index(self.connection.get())), Info):
				self.type.set("Info")
			elif isinstance(self.parent.link.getItem(self.actions.index(self.connection.get())), Speak):
				self.type.set("Speak")
			elif isinstance(self.parent.link.getItem(self.actions.index(self.connection.get())), Camera):
				self.type.set("Camera Change")
			elif isinstance(self.parent.link.getItem(self.actions.index(self.connection.get())), Movement):
				self.type.set("Movement")
			self.load = self.parent.link.getItem(self.actions.index(self.connection.get()))
			self.changeFrame(0)
		
	def changeFrame(self, something):
		print "Changed to " + self.type.get()
		self.window.destroy()
		if self.type.get() == "Speak":
			self.window = SpeakFrame(self, self.load)
		elif self.type.get() == "Camera Change":
			self.window = CameraFrame(self, self.load)
		elif self.type.get() == "Movement":
			self.window = MoveFrame(self, self.load)
		else:# self.type.get() == "Info":
			self.window = InfoFrame(self, self.load)
		self.save.config(command=self.window.save)
			
class InfoFrame(Frame):

	def __init__(self, parent, load):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.type = StringVar(self)
		self.next = StringVar(self)
		self.initUI()
		self.grid(row=1, column=0, columnspan=5)
		
	def initUI(self):		
		self.infoBox = Text(self, height=4, width=50)
		self.infoBox.grid(row=1, column=0, columnspan=5)
		
			
	def save(self):
		print "Saving"
		infoSlide = Info()
		print "..."
		infoSlide.setText(self.infoBox.get(1.0, END).replace("\n", ""))
		self.parent.parent.link.addItem(infoSlide, self.parent.parent.i)
		print "Saved"
		
		
class SpeakFrame(Frame):
	
	def __init__(self, parent, load):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.type = StringVar(self)
		self.speakerv = StringVar(self)
		anga = StringVar(self)
		anga.set("")
		poina = StringVar(self)
		poina.set("")
		self.pointvec = []
		self.pointvar = [poina]
		self.anglevec = []
		self.anglevar = [anga]
		self.addPAtIndex = 4
		self.addAAtIndex = 4
		self.initUI()
		self.grid(row=1, column=0, columnspan=5)
		
	def initUI(self):
		characs = json_reader.readCharNames()
		self.arcanas = json_reader.data_list("arcanas")
		self.arcanas.extend([""])
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		self.textl = Label(self, text="Text:")
		self.textl.grid(row=1, column=0)
		
		self.infoBox = Text(self, height=3, width=40)
		self.infoBox.grid(row=1, column=1, columnspan=3, rowspan=3)
		
		self.textl = Label(self, text="Points:")
		self.textl.grid(row=2, column=4, columnspan=2)
		
		self.pointBox = Text(self, height=1, width=3)
		self.pointBox.grid(row=3, column=4)
		self.pointvec.append(self.pointBox)
		
		speaker = OptionMenu(self, self.pointvar[0], *self.arcanas)
		speaker.config(width=10)
		speaker.grid(row=3, column=5, sticky='ew')
		
		self.textl = Label(self, text="Angle:")
		self.textl.grid(row=2, column=6, columnspan=2)
		
		self.angleBox = Text(self, height=1, width=3)
		self.angleBox.grid(row=3, column=6)
		self.anglevec.append(self.angleBox)
		
		speaker = OptionMenu(self, self.anglevar[0], *self.arcanas)
		speaker.config(width=10)
		speaker.grid(row=3, column=7, sticky='ew')
		
		self.speakerl = Label(self, text="Speaker:")
		self.speakerl.grid(row=1, column=4)
		
		speaker = OptionMenu(self, self.speakerv, *characs)
		speaker.config(width=10)
		speaker.grid(row=1, column=5, sticky='ew')
		
		self.addp = Button(self, text="Add points", command=self.extendP)
		self.addp.grid(row=30, column=4, columnspan=2)
		
		self.adda = Button(self, text="Add angles", command=self.extendA)
		self.adda.grid(row=30, column=6, columnspan=2)
		
	def extendP(self):
		self.pointvec.extend([Text(self, height=1, width=3)])
		self.pointvar.extend([StringVar(self)])
		self.pointvar[-1].set("")
		self.pointvec[-1].grid(row=self.addPAtIndex, column=4)
		temp = OptionMenu(self, self.pointvar[-1], *self.arcanas)
		temp.config(width=10)
		temp.grid(row=self.addPAtIndex, column=5, sticky='ew')
		self.addPAtIndex+=1
		
	def extendA(self):
		self.anglevec.extend([Text(self, height=1, width=3)])
		self.anglevar.extend([StringVar(self)])
		self.anglevar[-1].set("")
		self.anglevec[-1].grid(row=self.addAAtIndex, column=6)
		temp=OptionMenu(self, self.anglevar[-1], *self.arcanas)
		temp.config(width=10)
		temp.grid(row=self.addAAtIndex, column=7, sticky='ew')
		self.addAAtIndex+=1
		
	def save(self):
		print "Saving"
		print "..."
		speakSlide = Speak()
		speakSlide.setText(self.infoBox.get(1.0, END).replace("\n", ""))
		speakSlide.setSpeaker(self.speakerv.get())
		for i in xrange(len(self.pointvec)):
			if(self.pointvar[i].get()!=""):
				try:
					amount = (int)(self.pointvec[i].get(1.0, END))
					speakSlide.putPoints(self.pointvar[i].get(), amount)
				except:
					print "Amount must be an integer"
		for i in xrange(len(self.anglevec)):
			if(self.anglevar[i].get()!=""):
				try:
					amount = (int)(self.anglevec[i].get(1.0, END))
					speakSlide.putAngle(self.anglevar[i].get(), amount)
				except:
					print "Amount must be an integer"
		self.parent.parent.link.addItem(speakSlide, self.parent.parent.i)
		print "Saved"
		
		
class CameraFrame(Frame):
	
	def __init__(self, parent, load):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.type = StringVar(self)
		self.location = StringVar(self)
		self.initUI()
		self.grid(row=1, column=0, columnspan=5)
		
	def initUI(self):
		locations = json_reader.data_list("locations")
		self.location.set("Home")
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		self.textl = Label(self, text="Camera's position x:")
		self.textl.grid(row=1, column=0)
		
		self.cx = Text(self, height=1, width=3)
		self.cx.grid(row=1, column=1)
		
		self.textl = Label(self, text="Camera's position y:")
		self.textl.grid(row=2, column=0)
		
		self.cy = Text(self, height=1, width=3)
		self.cy.grid(row=2, column=1)
		
		self.textl = Label(self, text="Camera's position z:")
		self.textl.grid(row=3, column=0)
		
		self.cz = Text(self, height=1, width=3)
		self.cz.grid(row=3, column=1)
		
		self.textl = Label(self, text="Look at x:")
		self.textl.grid(row=1, column=2)
		
		self.lx = Text(self, height=1, width=3)
		self.lx.grid(row=1, column=3)
		
		self.textl = Label(self, text="Look at y:")
		self.textl.grid(row=2, column=2)
		
		self.ly = Text(self, height=1, width=3)
		self.ly.grid(row=2, column=3)
		
		self.textl = Label(self, text="Look at z:")
		self.textl.grid(row=3, column=2)
		
		self.lz = Text(self, height=1, width=3)
		self.lz.grid(row=3, column=3)
		
		self.locationl = Label(self, text="Location:")
		self.locationl.grid(row=1, column=4)
		
		locationO = OptionMenu(self, self.location, *locations)
		locationO.config(width=5)
		locationO.grid(row=1, column=5, sticky='ew')
		
			
	def save(self):
		print "Saving"
		cameraSlide = Camera()
		cameraSlide.setPlace(self.location.get())
		print "..."
		try:
			(int)(self.lx.get(1.0, END))
			(int)(self.ly.get(1.0, END))
			(int)(self.lz.get(1.0, END))
			(int)(self.cx.get(1.0, END))
			(int)(self.cy.get(1.0, END))
			(int)(self.cz.get(1.0, END))
		except:
			print "Must be an integer"
			return
		
		cameraSlide.setLookAt(((int)(self.lx.get(1.0, END)),(int)(self.ly.get(1.0, END)),(int)(self.lz.get(1.0, END))))
		cameraSlide.setCameraPosition(((int)(self.cx.get(1.0, END)),(int)(self.cy.get(1.0, END)),(int)(self.cz.get(1.0, END))))
		self.parent.parent.link.addItem(cameraSlide, self.parent.parent.i)
		print "Saved"
		
		
class MoveFrame(Frame):
	
	def __init__(self, parent, load):
		Frame.__init__(self, master=parent)
		self.parent = parent
		self.type = StringVar(self)
		self.speakerv = StringVar(self)
		self.aniv = StringVar(self)
		self.initUI()
		self.grid(row=1, column=0, columnspan=5)
		
	def initUI(self):
		animations = json_reader.data_list("animations")
		characs = json_reader.readCharNames()
		self.aniv.set("Idle")
		Style().configure("TButton", padding=(0,5,0,5), background='WhiteSmoke')
		
		self.textl = Label(self, text="Go to x:")
		self.textl.grid(row=1, column=0)
		
		self.lx = Text(self, height=1, width=3)
		self.lx.grid(row=1, column=1)
		
		self.textl = Label(self, text="Go to y:")
		self.textl.grid(row=2, column=0)
		
		self.ly = Text(self, height=1, width=3)
		self.ly.grid(row=2, column=1)
		
		self.speakerl = Label(self, text="Person:")
		self.speakerl.grid(row=1, column=3)
		
		speaker = OptionMenu(self, self.speakerv, *characs)
		speaker.config(width=10)
		speaker.grid(row=1, column=4, sticky='ew')
		
		self.anil = Label(self, text="Animation:")
		self.anil.grid(row=2, column=3)
		
		ani = OptionMenu(self, self.aniv, *animations)
		ani.config(width=10)
		ani.grid(row=2, column=4, sticky='ew')
		
			
	def save(self):
		print "Saving"
		moveSlide = Movement()
		moveSlide.setSubject(self.speakerv.get())
		moveSlide.setAnimation(self.aniv.get())
		print "..."
		try:
			(int)(self.lx.get(1.0, END))
			(int)(self.ly.get(1.0, END))
		except:
			print "Numbers must be integers"
			return
		
		moveSlide.setDestination(((int)(self.lx.get(1.0, END)),(int)(self.ly.get(1.0, END))))
		
		self.parent.parent.link.addItem(moveSlide, self.parent.parent.i)
		print "Saved"
		
		
		