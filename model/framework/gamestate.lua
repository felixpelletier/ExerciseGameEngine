gamestate = {}

function loadstate()
end

function savestate(savefile)
	require('json_reader')
	write({data=gamestate, path='state.json'})
end

function evolve(key, value)
	gamestate[key] = value
end

evolve('Version', '0.0.0.1')
savestate(nil)


--This file defines all global variables that are callable from the controller or that need
--to be cached for further use. The following are all know values that can be contextually
--found within gamestate and their significance.

--Version: Game version. Currently 0.0.0.1
--cut: The current cutscene being played.
--day: Current day's id (~1-365) and time (morning, after school, evening, etc...)
--slglobal: Current level and angle of each social link in the game
--availablechars: Names of characters that can be in the party
--party: Characters other than MC that are in the party (and all their data)
--mc: All data about the Main Character
--place: Current Place.
--flags: List of all flags that have been raised as of now. (perform "need in flags" for dependancy check)