local map = {}

local function _load()
	local json = require('json_reader')
	map.places={}
	for key, value in pairs(json.read({file='hereisthemap.json'})) do
		print(key, value[1], value[2][1], value[2][1])
		map.places[key]={value[1], value[2]}
	end
end

function map.refresh()--Send update to graphic view
	local state = require('state')
	local cjson = require('cjson')
	state.update = cjson.encode({key="map.show",places=map.places})
end

function map.processinput()
	local state = require('state')
	print("You chose to travel to "..map.places[state.context.index+1][1])
	state.changecontext('Overworld', map.places[state.context.index+1][1])
end

function map.loadcontext()
	local state = require('state')
	state.context=map
	_load()
	map.refresh()
	state.loading(false)
end

return map