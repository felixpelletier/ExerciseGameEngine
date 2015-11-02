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
						

