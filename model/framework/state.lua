local state = {}

local function jsonparsestate(table)
	local save = {}
	for key, value in pairs(table) do
		if type(value)~='function' and type(value)~='table' then save[key]=value end
		if type(value)=='table' then save[key]=jsonparsestate(value) end
	end
	return save
end

function state.loadstate(savefile)
	local json = require('json_reader')
	if savefile then savefile="PXS"..savefile..".json" else savefile='state.json' end
	gamestate = json.read({file=savefile})
end

function state.savestate(savefile)
	local json = require('json_reader')
	if savefile then savefile="PXS"..savefile..".json" state.evolve('save', savefile) else savefile='state.json' end
	json.write({data=jsonparsestate(state), path=savefile})
end


function state.evolve(key, value)
	state[key] = value
end

local function parsekey(key)
	--parse input key into lua readable form if necessary, eg KEY.W to 'up' or whatnot
	return key
end

function state.input(inputkey)--We assume the threading is happening in C because lua has no multithreading.
	if not state.backlog then
		state.backlog=parsekey(inputkey) print(inputkey)
		print("Processing input: "..state.backlog)
		state.context.processinput(state.backlog)
		state.backlog=nil
	end
end


function state.changecontext(newc, params)
	local context = require(newc)
	context.loadcontext(params)
end

function state.loading(start)
	if not start then return end--Loading complete
	--Send loading request to graphics
end

function state.lock()
	state.backlog=0
end

function state.unlock()
	state.backlog=nil
end


return state

--loadstate(nil)
--print("Game is at version: "..gamestate.Version)
--evolve('Version', '0.0.0.0.5')
--savestate(nil)



--This file defines all global variables that are callable from the controller or that need
--to be cached for further use. The following are all know values that can be contextually
--found within state and their significance.

--Version: Game version. Currently 0.0.0.0.X
--cut: The current cutscene being played.
--day: Current day's id (~1-365) and time (morning, after school, evening, etc...)
--slglobal: Current level and angle of each social link in the game
--availablechars: Names of characters that can be in the party
--party: Characters other than MC that are in the party (and all their data)
--mc: All data about the Main Character
--place: Current Place.
--flags: List of all flags that have been raised as of now. (perform "need in flags" for dependancy check)
--save: The save number (1-inf)
--context: What the player is doing now and the input processor for that context
--backlog: The last key pressed. No inputs are saved unless this value is nil


--Current Existing contexts:
--link: Any cutscene (Social Link, Story or Event)

--Possible contexts:
--link: Any cutscene (Social Link, Story or Event)
--overworld: Overworld
--dungeon: Dungeon
--battle: Battle
--velvet: Velvet Room