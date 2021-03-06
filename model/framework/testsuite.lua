--These are tests written to confirm the proper functionality of the logic model. Run in command line
--to view comprehensive analysis of what the model is providing.
--All calls to the model should respect the formats shown here.
local state = require('state')
local json = require('json_reader')
local cjson = require('cjson')

local function printUpdate()
	print("\nRefresh")
	for key, value in pairs(cjson.decode(state.update).menus) do for index, name in pairs(value) do print(key, index, name) end end
end

state.evolve('Version', '0.0.0.0.24')
state.evolve('mc', {name='Chaos', money=3})
state.evolve('slglobal', {['Aeon']={level=1, angle=0}})
state.savestate(nil)

local popup = require('popup')
popup.loadcontext({'Yes', 'No'})
print(popup.options[1], popup.options[2])
state.context = {input='select'}
print(popup.processinput())
state.context = {input='back'}
print(popup.processinput())

--[[
state.changecontext('map', nil)

state.event(cjson.encode({index=2}))
]]--

--[[
json.read({file="shopmenus.json"})

state.changecontext('shop', 'trainer')

printUpdate()

print("\ninput 1 (selecting 'Buy Gear')")
state.event(cjson.encode({key="shop.nav.menu", index=0}))

printUpdate()

print("\ninput 2 (selecting 'Accessories')")
state.event(cjson.encode({key="shop.nav.menu", index=0}))

printUpdate()

print("\ninput 3 (going back)")
state.event(cjson.encode({key="shop.nav.menu", back=true}))

printUpdate()

print("\ninput 4 (selecting 'Accessories' again)")
state.event(cjson.encode({key="shop.nav.menu", index=0}))

printUpdate()

print("\ninput 5 (selecting 'Bikini Armor')")
state.event(cjson.encode({key="shop.nav.menu", index=1}))

printUpdate()
]]--

--[[
state.changecontext('link', {arcana='Aeon'})

state.event(cjson.encode({key="link.action", index=0}))

state.event(cjson.encode({key="link.action", index=0}))

state.event(cjson.encode({key="link.action", index=0}))

state.event(cjson.encode({key="link.action", index=0}))

state.event(cjson.encode({key="link.action", index=0}))

state.event(cjson.encode({key="link.action", index=1}))
]]--


--LEGACY/PROOF OF CONCEPT
--[[
shadowep=json.read({file='Seraph.json'})
aigis=json.read({file='Cherub.json'})
mc=json.read({file='Dominion.json'})

state.changecontext('battle', {['party']={{['name']='Aigis', ['persona']=aigis}, {['name']='MC', ['persona']=mc}}, ['ene']={{['name']='Shadow', ['persona']=shadowep}}})

state.input('select')
state.input('select')
state.input('select')

state.savestate(nil)

state.changecontext('link', {arcana='Aeon', level='1', angle='0'})

state.input('select')
state.input('select')
state.input('select')
state.input('select')
state.input('select')
state.input('up')
state.input('select')
state.input('select')
]]--
print("\nState")
for key, value in pairs(state) do print(key, value) end
print("\nContext")
for key, value in pairs(state.context) do print(key, value) end
print("\nRefresh")
for key, value in pairs(cjson.decode(state.update)) do print(key, value) end
--print(#state.update.options.." options")
