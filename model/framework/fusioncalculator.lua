require('json_reader')

function combos(way)
	local combos = get({file='fusion_combos.json', path=way.way})
	return combos
end
com = combos({way='2way'})
print (com)
print (com.FoolFool)
for fusionb, result in pairs(com) do
	print(fusionb,result)
end