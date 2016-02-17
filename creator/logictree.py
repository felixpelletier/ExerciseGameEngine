import action

class MathGraph:

	def __init__(self, name):
		self.id = name
		self.items = DynamicList()
		
	def loadGraph(self, value):
		index = 0
		jndex = 0
		for io in value:
			for jo in io:
				print jo
				if jndex == 0:
					self.addItem(action.load(jo), index)
					print self.getItem(index)
				else:
					self.addRelation(index, ((int)(jo)))
				jndex+=1
			index+=1
			jndex = 0
		return self
		
	def size(self):
		return len(self.items)
		
	def setFirst(self, item):#Not useful (index 0 always first element). Only useful if I do a full overhaul to a pure hashmap structure
		self.first = item
		
	def getIDs(self):#safe but UGLY AF
		temp = []
		for e in self.items:
			temp.append(self.getOne(e))
		return temp
		
	def getOneID(self, element):#safe but UGLY AF
		temp = None
		try:
				if element.text not in temp:
					temp = element.text
				else:
					temp = element.text+str(len(temp))
			except:
				try:
					if ("Camera at "+element.place) not in temp:
						temp = "Camera at "+element.place)
					else:
						temp = "Camera at "+element.place + str(len(temp)))
				except:
					if ("Moving "+element.subject) not in temp:
						temp = "Moving "+element.subject)
					else:
						temp = "Moving "+element.subject + str(len(temp)))
		return temp[0]
		
	def getItem(self, index):
		return self.items[index][0]
		
	def getRelations(self, index):
		return self.items[index]
		
	def addItem(self, action, index):
		if not isinstance(self.items[index], DynamicList):
			self.items[i] = DynamicList()
		self.items[index][0]=action
		
	def addRelation(self, i, j):
		if j not in self.items[i]:
			self.items[i].append(j)
		
	def delRelation(self, i, j):#Not working
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
		
	def delItem(self, i):#Not working
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
						


		
class DynamicList(list):#Needs relocating (theoretically)

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