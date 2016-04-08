--These are tests written to confirm the proper functionality of the logic model. Run in command line
--to view comprehensive analysis of what the model is providing.
--All calls to the model should respect the formats shown here.
local state = require('state')
local json = require('json_reader')

state.evolve('Version', '0.0.0.0.5')
state.evolve('mc', {['name']='Chaos'})
state.savestate(nil)

shadowep=json.read({file='Seraph.json'})
aigis=json.read({file='Cherub.json'})
mc=json.read({file='Dominion.json'})

state.changecontext('battle', {['party']={{['name']='Aigis', ['persona']=aigis}, {['name']='MC', ['persona']=mc}}, ['ene']={{['name']='Shadow', ['persona']=shadowep}}})

state.input('select')
state.input('select')
state.input('select')

state.savestate(nil)

--[[state.changecontext('link', {arcana='Aeon', level='1', angle='0'})

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
for key, value in pairs(state.update) do print(key, value) end
--print(#state.update.options.." options")