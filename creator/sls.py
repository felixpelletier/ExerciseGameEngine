from logictree import *
import json_reader

class SocialLink():
	
	def __init__(self, arcana):
		self.arcana = arcana
		self.cutscenes = {}#[level][angle]
		self.loadLinks()
		
	def setLink(graph):
		self.cutscenes[str(level)+str(angle)] = graph
		
	def loadLinks(self):
		self.cutscenes = json_reader.readLink(self.arcana)
		print "Loaded"
		
	def getLink(self, level, angle):
		try:
			return self.cutscenes.pop(str(level)+str(angle))
		except:
			print "No such link"
			return 0
			
	def startLink(self, level, angle):
		try:
			self.cutscenes.pop(str(level)+str(angle))
			print "Link already exists!"
		except:
			self.cutscenes[str(level)+str(angle)]= MathGraph(self.arcana+str(level)+str(angle))
					
		return self.cutscenes.pop(str(level)+str(angle))
		
		
		
#test = SocialLink("Fool")
#test.getLink(0, 0)
#test.startLink(0, 0)
#print test.getLink(0, 0).id

#test = DynamicList()
#test[6] = "Works"
#print test[6]