from logictree import MathGraph

class SocialLink():
	
	def __init__(self, arcana):
		self.arcana = arcana
		self.cutscenes = {}#[level][angle]
		
	def getLink(self, level, angle):
		try:
			return self.cutscenes.pop(str(level)+str(angle))
		except:
			print "Not such link"
			
	def startLink(self, level, angle):
		try:
			self.cutscenes.pop(str(level)+str(angle))
			print "Link already exists!"
			return
		except:
			self.cutscenes[str(level)+str(angle)]= MathGraph(self.arcana+str(level)+str(angle))
		
		
		
test = SocialLink("Fool")
test.getLink(0, 0)
test.startLink(0, 0)
print test.getLink(0, 0).id

test = DynamicList()
test[6] = "Works"
print test[6]