events = {}

Entity = {}

Entity.__index = Entity

id_counter = 1

function Entity:new()
	newObj = {id = id_counter}
	id_counter = id_counter + 1
	event = {}
	event.id = newObj.id
	event.type = "new_entity"
	table.insert(events, event)
	return setmetatable(newObj, self)
end

function Entity.__newindex(entity, key, value)
	event = {}
	event.id = entity.id
	event.type = "parameter"
	event.key = key
	event.value = value
	table.insert(events, event)
end

function _update()
	events = {}
	update()
	return events
end
