class MathGraph:

	def __init__(self, name):
		self.id = name
		self.first = None
		self.items = DynamicList()
		
	def setFirst(self, item):
		self.first = item
		
	def getItem(self, index):
		return self.items[index]
		
	def getRelations(self, index):
		return self.items[index]
		
	def addItem(self, action):
		self.items.append(action)
		
	def addRelation(self, i, j):
		if not isinstance(self.items[len(items)], DynamicList):
			self.items[i] = DynamicList()
		if j not in self.items[i]:
			self.items[i].append(j)
		
	def delRelation(self, i, j):
		try:
			self.items[i].remove(j)
		except:
			print "Relation does not exist"
			return
		jfound = False
		for item in self.items:
			for relation in item:
				if relation is j:
					jfound=True
		if not jfound:
			self.delItem(j)
		
	def delItem(self, i):
		array = self.items.pop(i)
		for item in self.items:
			for relation in item:
				if relation is i:#If edge leading to deleted item is found elsewhere, delete that edge
					item.remove(i)
				if relation in array:#If another edge leads to the same place as an item in array, that subtree need not be deleted therefore remove from array
					array.remove(relation)
		while i in array:#Remove self-referencing in array to prevent stackoverflow
			array.remove(i)#could cause bug if element links to itself multiple times
		array.pop(0)#Remove object
		for index in array:#Delete full subtree of item
			if index > i:#Adjusting index after repositioning in step one
				self.delItem(index-1)
			else:
				self.delItem(index)
						


		
class DynamicList(list):

    def __getslice__(self, i, j):
        return self.__getitem__(slice(i, j))
    def __setslice__(self, i, j, seq):
        return self.__setitem__(slice(i, j), seq)
    def __delslice__(self, i, j):
        return self.__delitem__(slice(i, j))

    def _resize(self, index):
        n = len(self)
        if isinstance(index, slice):
            m = max(abs(index.start), abs(index.stop))
        else:
            m = index + 1
        if m > n:
            self.extend([self.__class__() for i in range(m - n)])

    def __getitem__(self, index):
        self._resize(index)
        return list.__getitem__(self, index)

    def __setitem__(self, index, item):
        self._resize(index)
        if isinstance(item, list):
            item = self.__class__(item)
        list.__setitem__(self, index, item)