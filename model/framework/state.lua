local state = {}

function state.loadstate(savefile)
	local json = require('json_reader')
	if savefile then savefile="PXS"..savefile..".json" else savefile='state.json' end
	gamestate = json.read({file=savefile})
end

function state.savestate(savefile)
	local json = require('json_reader')
	evolve('save', savefile)
	if savefile then savefile="PXS"..savefile..".json" else savefile='state.json' end
	json.write({data=gamestate, path=savefile})
end

function state.evolve(key, value)
	gamestate[key] = value
end

local function parsekey(key)
	--parse input key into lua readable form if necessary, eg KEY.W to 'up' or whatnot
	return key
end

function state.input(inputkey)
	if not state.backlog then state.backlog=parsekey(inputkey) end
end

function processinput()--threaded
	if state.backlog then
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


return state

--loadstate(nil)
--print("Game is at version: "..gamestate.Version)
--evolve('Version', '0.0.0.0.3')
--savestate(nil)



--This file defines all global variables that are callable from the controller or that need
--to be cached for further use. The following are all know values that can be contextually
--found within gamestate and their significance.

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
--context: What the player is doing now (link, overworld, dungeon) and the input processor for that context
--backlog: The last key pressed. No inputs are saved unless this value is nil
