gamestate = nil

function loadstate()
end

function savestate(savefile=nil)
	require('json_reader')
	write({data=gamestate, path='state.json'})
end