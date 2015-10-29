class Action():

	def __init__(self):
		self.hash = hash(self)
		self.relations = []
		self.trip_set = {}
		
	def getRelations():
		return relations
		
	def hasRelation(relation):
		return (relation in self.relations)
		
	def hash():
		return self.hash
		
class Speak(Action):
	
	def __init__(self):
		self.text = ""
		self.speaker = None#
		self.points = {}
		self.angle = {}
		
	def putPoints(self, arcana, points):
		self.points[arcana] = points
		
	def putAngle(self, arcana, angle):
		self.angle[arcana] = angle
		
	def setSpeaker(person):
		self.speaker = person
		
	def setText(text_new):
		self.text = text_new
		
	def getText():
		return self.text
		
	def getSpeaker():
		return self.speaker
		
	def getPoints():
		return self.points
		
	def getAngle():
		return self.angle
		
	def display():
		return None#
		
class Choice(Action):

	def __init__(self):
		self.choices = []
		self.text = ""
		self.speaker = None#
		
	def setText(textnew):
		self.text = textnew
		
	def setSpeaker(person):
		self.speaker = person
		
	def addChoice(choice):
		self.choices.append(choice)
		
	def addChoice(choice, index)
		self.choices.insert(index, choice)
		
	def getText():
		return self.text
		
	def getSpeaker():
		return self.speaker
		
	def getChoices():
		return self.choices
		
class Camera(Action):
	
	def __init__(self):
		self.place = None#
		self.cameraPosition = []
		self.lookAt = []
		
	def setPlace(placenew):
		self.place = placenew
		
	def setCameraPosition(position3):
		self.cameraPosition = position3
		
	def setLookAt(lookat3):
		self.lookAt = lookat3
		
	def getPlace():
		return self.place
		
	def getCameraPosition():
		return self.cameraPosition
		
	def getLookAt():
		return self.lookAt
		
class Movement(Action):

	def __init__(self):
		self.subject = None#
		self.destination = ()
		self.animation = None#
		
	def setSubject(person):
		self.subject = person
	
	def setDestination(tuple):
		self.destination = tuple
		
	def setAnimation(aniname):
		self.animation = aniname
		
	def getSubject():
		return self.subject
		
	def getDestination():
		return self.destination
		
	def getAnimation():
		return self.animation