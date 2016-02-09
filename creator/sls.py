from logictree import *
import json
import json_reader

class SocialLink():
	
	def __init__(self, arcana):
		self.arcana = arcana
		self.cutscenes = {}#[level][angle]
		self.loadLinks()
		
	def setLink(self, graph, level, angle):
		self.cutscenes[str(level)+"_"+str(angle)] = graph
		
	def loadLinks(self):
		try:
			tempdic = json_reader.readLink(self.arcana)["cutscenes"]
			for id, graph in tempdic.iteritems():
				self.cutscenes[id] = MathGraph(graph["id"]).loadGraph(graph["items"])
		except:
			print "No existing link"
		print self.cutscenes
		print "Loaded"
		
	def getLink(self, level, angle):#Not used
		try:
			return self.cutscenes.pop(str(level)+"_"+str(angle))
		except:
			print "No such link"
			return 0
			
	def startLink(self, level, angle):
		try:
			toreturn = self.cutscenes[(str(level)+"_"+str(angle))]
			print "Link already exists!"
		except:
			toreturn = self.cutscenes[str(level)+"_"+str(angle)]= MathGraph(self.arcana+str(level)+"_"+str(angle))
					
		return toreturn
		
	def save(self):
		json_reader.writeLink(self)
		print "Saved to to file"
		
		
#test = SocialLink("Fool")
#test.getLink(0, 0)
#test.startLink(0, 0)
#print test.getLink(0, 0).id

#test = DynamicList()
#test[6] = "Works"
#print test[6]