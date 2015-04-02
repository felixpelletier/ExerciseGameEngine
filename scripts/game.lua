function init()
	for i=0,100 do
		local entity = Entity:new{model="oildrum", collide=true,
				  x=math.random(-100,100), y=0, z=math.random(-100, 100)}
	end
end

function update()
	local choice = math.random(2)
	choice = choice == 2
	entities[math.random(100)].enabled = choice;
end
