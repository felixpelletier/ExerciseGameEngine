from creatures import Character
import os
import json

		
def writeOne(character):
	with open(character.getName() + '.json', 'w') as outfile:
		json.dump(character.__dict__, outfile)
	outfile.close()
	writeCharNames(character.getName())

def writeOneP(persona):
	with open(persona.getName() + '.json', 'w') as outfile:
		json.dump(persona.__dict__, outfile)
	outfile.close()
	if persona.getName() not in readPerNames():
		writePerNames(persona.getName())
	
def readOne(name):
	with open(name+'.json') as json_data:
		characterL = json.load(json_data)
	json_data.close()
	return Character(characterL["name"], characterL["desc"], characterL["important"])
	
def readP(fetch):
	with open(fetch+".json") as json_data:
		persona = json.load(json_data)
	json_data.close()
	return persona
	
def writeCharNames(name):
	list = readCharNames()
	list.append(name)
	with open('chars.json', 'w') as outfile:
		json.dump(list, outfile)
	outfile.close()
	
def writePerNames(name):
	list = readPerNames()
	list.append(name)
	with open('pers.json', 'w') as outfile:
		json.dump(list, outfile)
	outfile.close()
	
def readPerNames():
	try:
		with open('pers.json') as json_data:
			names = json.load(json_data)
		json_data.close()
		noU = []
		for item in names:
			if isinstance(item, unicode):
				item = item.encode('utf-8')
			noU.append(item)
		return noU
	except:
		print "No existing names"
	empty = []
	return empty
	
def deleteChar(name):
	list = readCharNames()
	list.remove(name)
	with open('chars.json', 'w') as outfile:
		json.dump(list, outfile)
	outfile.close()
	os.remove(name + '.json')
	
def deletePer(name):
	list = readPerNames()
	list.remove(name)
	with open('pers.json', 'w') as outfile:
		json.dump(list, outfile)
	outfile.close()
	os.remove(name + '.json')
	
def readCharNames():
	try:
		with open('chars.json') as json_data:
			names = json.load(json_data)
		json_data.close()
		noU = []
		for item in names:
			if isinstance(item, unicode):
				item = item.encode('utf-8')
			noU.append(item)
		return noU
	except:
		print "No existing names"
	empty = []
	return empty
		

def data_list(fetch):
	with open('data.json') as json_data:
		temp = json.load(json_data)
	json_data.close()
	data = temp[fetch]
	noU = []
	for item in data:
		if isinstance(item, unicode):
			item = item.encode('utf-8')
		noU.append(item)
	return noU
		
def base_level_of(name):
	with open('persona.json') as json_data:
		personas = json.load(json_data)
	json_data.close()
	for persona in personas:
		if persona["name"] == name:
			return persona["level"]


def fused_persona(arcana, level):
	with open('persona.json') as json_data:
		personas = json.load(json_data)
	json_data.close()
	for persona in personas:
		if persona["arcana"] == arcana:
			temp = persona
			if persona["level"] >= level:
				return temp
	return temp

def get_persona(name):
	with open('persona.json') as json_data:
		personas = json.load(json_data)
	json_data.close()
	for persona in personas:
		if persona["name"] == name:
			return persona
	
def read_combos(name1, name2):
	with open('persona.json') as json_data:
		personas = json.load(json_data)
	json_data.close()
	with open('fusion_combos.json') as json_data:
		combos = json.load(json_data)
	json_data.close()
	for persona in personas:
		if persona["name"] == name1:
			a1 = persona["arcana"]
		if persona["name"] == name2:
			a2 = persona["arcana"]
	if (a1+a2) in combos["2way"]:
		return combos["2way"][a1+a2]
	elif (a2+a1) in combos["2way"]:
		return combos["2way"][a2+a1]
	
#print fused_persona("Magician", 10)
#print read_combos("Jack Frost", "Angel")