from shotgun_api3 import Shotgun
import json

SCRIPT_NAME = 'Samuel - API'
SCRIPT_KEY = '2b3f3b6e442242c067501a9e17503bac1d27b6ea244a4e4b5987e26d5f6520e2'
sg = Shotgun("https://objeus.shotgunstudio.com", SCRIPT_NAME, SCRIPT_KEY)

also = ['code', 'description']
ignore = ['sg_status_list', 'sg_opent_tickets']

spellfields = sg.schema_field_read('CustomEntity01')

releventfields = {}
returnfields = []

for field in spellfields:
	if ('sg_' in field or field in also) and field not in ignore:
		returnfields.append(field)
		if 'sg_' in field:
			releventfields[field] = field[3:].replace('_', '')
		if field == 'code':
			releventfields[field] = "name"
		if field == 'description':
			releventfields[field] = "desc"


sg_spells = sg.find('CustomEntity01', [], returnfields)

spells = {}
for spell in sg_spells:
	spells[spell['code']] = {}
	for field in spell:
		if field in releventfields:
			spells[spell['code']][releventfields[field]] = spell[field]

with open("spells.json", 'w') as outfile:
	json.dump(spells, outfile)
outfile.close()