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
				if jndex == 0:
					self.addItem(action.load(jo), index)
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
			ret = self.getOneID(e[0])
			if ret is None:
				break
			if ret not in temp:
				temp.append(ret)
			else:
				temp.append(ret+str(len(temp)))
		return temp
		
	def getOneID(self, element):#safe but UGLY AF
		temp = None
		if isinstance(element, action.Info) or isinstance(element, action.Speak):
			temp = element.text
		elif isinstance(element, action.Camera):
			temp = element.place
		elif isinstance(element, action.Movement):
			temp = element.subject
		return temp
		
	def getItem(self, index):
		return self.items[index][0]
		
	def getRelations(self, index):
		if len(self.items)!=0:
			return self.items[index][1:len(self.items[index])]
		else:
			return []
		
	def addItem(self, action, index):
		if not isinstance(self.items[index], DynamicList):
			self.items[i] = DynamicList()
		self.items[index][0]=action
		
	def addRelation(self, i, j):
		if j not in self.items[i]:
			self.items[i].append(j)
		
	def delRelation(self, i, j):
		self.items[i].remove(j)
		jfound = False
		print self.items[i]
		for itemRelation in self.items:
			if j in itemRelation:
				jfound=True
		if not jfound:
			self.delItem(j)
		
	def delItem(self, i):#Not working
		for relation in self.items[i][1:len(self.items[i])]:
			self.delRelation(i, relation)
		for itemRelation in self.items:
			if i in itemRelation:
				itemRelation.remove(i)		
		self.items.pop(i)


		
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