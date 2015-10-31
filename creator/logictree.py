class MathGraph:

	def __init__(self, name):
		self.id = name
		self.first = None
		self.items = [][]
		
	def setFirst(self, item):
		self.first = item
		
	def getItem(self, index):
		return self.items[index]
		
	def getRelations(self, index):
		return self.items[index].pop(0)
		
	def addItem(self, action):
		self.items[len(items)][0] = action
		
	def addRelation(self, i, j):
		self.items[i][len(items[i])] = j
		
	def delRelation(self, i, j):
		self.items[i].remove(j)
		
	def delItem(self, i):
		array = self.items.pop(i)
		for item in self.items:
			for relation in item:
				if relation is i:
					item.remove(i)
				if relation in array:
					array.remove(relation)
		array.remove(i)
		array.pop(0)
		for index in array:
			self.delItem(index)
						


# class LogicTree:
	
	# def __init__(self, first_element):
		# self.list_all = [first_element]
		# self.list_rel = []
		# print "Uni-directional tree created"
		# print self.list_all[0] + " is first element"
		
	# def get_nexts(self, origin):
		# print self.determine_index(origin)
		# print self.list_rel
		# return self.list_rel[self.determine_index(origin)]
		
	# def determine_index(self, origin):
		# i=0
		# while self.list_all[i] != origin:
		# print i
			# i+1
		# return i
		
	# def add_next(self, origin, next):
		# try:
			# self.list_rel[self.determine_index(origin)] + {next}
		# except IndexError:
			# self.list_rel + [{next}]
		# print self.list_rel
		
# lt = LogicTree("Die for me")
# lt.add_next("Die for me", "Alice")
# lt.get_nexts("Die for me")