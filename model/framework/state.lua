local state = {}

local function jsonparsestate(table)
	local save = {}
	for key, value in pairs(table) do
		if type(value)~='function' and type(value)~='table' then save[key]=value end
		if type(value)=='table' then save[key]=jsonparsestate(value) end
	end
	return save
end

local function corruptioncheck(state)--Ensure data within the save file covers all essential data
	assert(state.flags~=nil)
	assert(state.mc~=nil)
	assert(state.day~=nil)
	assert(state.slglobal~=nil)
	assert(state.place~=nil)
end

function state.loadstate(savefile)
	local json = require('json_reader')
	if savefile then savefile="PXS"..savefile..".json" else savefile='state.json' end
	state = json.read({file=savefile})
	corruptioncheck(state)
end

function state.savestate(savefile)
	local json = require('json_reader')
	if savefile then savefile="PXS"..savefile..".json" state.evolve('save', savefile) else savefile='state.json' end
	json.write({data=jsonparsestate(state), path=savefile})
end


function state.evolve(key, value)
	state[key] = value
end

function state.flag(flagkey)
	state.flags[flagkey]=true
end

function state.event(event)
	if state.locked then state.eventcallerror="State is locked" return end
	state.lock()
	local json = require('cjson')
	local map = json.decode(event)
	for key, value in pairs(map) do state.context[key]=value end
	state.context.processinput()
	state.unlock()
end

--There is not state.lock here as we assume that any call to changecontext will be effected
--through a state.event processinput call
function state.changecontext(newc, params)
	state.loading(true)
	state.inline=nil
	local context = require(newc)
	context.loadcontext(params)--Do not forget to cal state.loading(false) once loading context is complete
end

function state.loading(start)
	if not start then state.isloading=true print("Loading complete") return end--Loading complete
	state.isloading=nil
	print("Loading...")--Send loading request to graphics
end

--Having two functions is a bit redundant but idgaf
function state.lock() state.locked=true end
function state.unlock()	state.locked=false end

return state

--This file defines all global variables that are callable from the controller or that need
--to be cached for further use. The following are all know values that can be contextually
--found within state and their significance.

--Version: Game version. Currently 0.0.0.0.X
--day: Current day's id (~1-365) and time (morning, after school, evening, etc...)
--slglobal: Current level and angle of each social link in the game
--availablechars: Names of characters that can be in the party
--party: Characters other than MC that are in the party (and all their data)
--mc: All data about the Main Character
--place: Current Place.
--flags: List of all flags that have been raised as of now. (perform "need in flags" for dependancy check)
--save: The save number (1-inf)
--context: What the player is doing now and the input processor for that context
--locked: When locked=true, no events are accepted
--eventcallerror: last error returned by an event handler. Destroy that data to acknowledge it.
--isloading: unique identifier for when the loading screen is needed.


--Current Existing contexts:
--link: Any cutscene (Social Link, Story or Event)

--Possible contexts:
--link: Any cutscene (Social Link, Story or Event)
--overworld: Overworld
--dungeon: Dungeon
--battle: Battle
--velvet: Velvet Room
--shop: any kind of shop in the game