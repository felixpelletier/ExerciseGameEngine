events = {}

entities = {}

Entity = {}

Entity.__index = Entity

id_counter = 1

function Entity:new(args)
	newObj = {id = id_counter}
	id_counter = id_counter + 1
	event = {}
	event.id = newObj.id
	event.type = "new_entity"
	for k,v in pairs(args) do event[k] = v end
	table.insert(events, event)
	entities[newObj.id] = newObj
	return setmetatable(newObj, self)
end

function Entity.__newindex(entity, key, value)
	event = {}
	event.id = entity.id
	event.type = "parameter"
	event.key = key
	event.value = tostring(value)
	table.insert(events, event)
end

function _update()
	events = {}
	update()
	return events
end

function _init()
	events = {}
	init()
	return events
end
