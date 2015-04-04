function init()
	for i=0,100 do
		local entity = Entity:new{model="oildrum", collide=true,
				  x=math.random(-100,100), y=0, z=math.random(-100, 100)}
	end
end

function update(in_events)
	for index,event in pairs(in_events) do
		print("Event " .. index)
		for key,value in pairs(event) do
			print("Key: " .. key .. " Value: " .. value)
		end
	end
	--local choice = math.random(2)
	--choice = choice == 2
	--entities[math.random(100)].enabled = choice;
end
