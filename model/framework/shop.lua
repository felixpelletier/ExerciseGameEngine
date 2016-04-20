local shop = {}

local function _load(shopinquestion)
	local json = require ('json_reader')
	shop.menu=json.read({file='shopmenus.json'})[shopinquestion]
	shop.depth = {shopinquestion}
end
--for salti, saltv in pairs() do print(salti, saltv) end
local function genmenus()--Hope to god I remember this... Ask Samuel what this is doing
	local state = require('state')
	local items = {{}}
	local current=shop.menu
	for index, toplevel in pairs(shop.menu) do for name, tree in pairs(toplevel) do items[1][index]=name end end--Get base shop options available on opening shop screen
	for index, nextlevel in pairs(shop.depth) do--shop.depth stores the indexes of the selections made
		if index~=1 then--skip first level used for toplevel
			if current[nextlevel]==nil then for k, v in pairs(current) do print(k, v, nextlevel) if v[nextlevel] then current=v[nextlevel] elseif v[1][nextlevel] then current=v[1][nextlevel] end end--current alternates between being a list and a map containing one item for ordering purposes
			else current=current[nextlevel] end
			items[index]={}
			print(current)
			if type(current)=='string' then--If element is purchasable then engage in purchase logic
				items[index][1]="Bought "..current.." for 1000 yen!"
				print(items[index][1])
				shop.depth[#shop.depth]=nil--Don't want to get stuck at the buying level, so reset to previous one after purchase.
				return items--Purchase is end-tree interaction. Do not try and continue parsing
			end
			for singlekey, singlevalue in pairs(current) do
				print(singlekey, singlevalue)
				for name, subcat in pairs(singlevalue) do--singlevalue ALWAYS contains only ONE key (NOT TRUE! LOADED ITEMS ARE PROPERLY MAPPED!), value pair the exta layer is for ordering purposes because lua
					if type(subcat)=='table' then--the "next value" in the "tree" is either a table or a function. if table...
						for subcatname, subcatsubcat in pairs(subcat) do--there's only one key in the table by design so add that key to the list
							if type(subcatname)=='string' then
								items[index][#items[index]+1]=subcatname
							else
								items[index][#items[index]+1]=subcatsubcat
							end
							print(subcatname, subcatsubcat)
						end
					else--if function, place the return of the function in the list
						for loadeditemindex, itemname in pairs(loadstring(subcat)()) do
							print("Name", itemname)
							items[index][loadeditemindex]=itemname
						end
						for salti, saltv in pairs(items[index]) do print("Salt", salti, saltv) end
						singlevalue[name]=items[index]
					end
					
				end
			end
			print()
		end	
	end
	return items
end

function shop.refresh()
	local state = require('state')
	local cjson = require('cjson')
	state.update = cjson.encode({key="shop.show.menutree", menus=genmenus()})
end

function shop.processinput()
	local state = require('state')
	--print(#shop.depth)
	if state.context.back then
		shop.depth[#shop.depth]=nil
		state.context.back=nil
		if #shop.depth==0 then print("Change context") end
	else shop.depth[#shop.depth+1]=state.context.index+1 end
	--print(#shop.depth)
	shop.refresh()
end

function shop.loadcontext(shopinquestion)
	local state = require('state')
	state.context=shop
	_load(shopinquestion)
	shop.refresh()
	state.loading(false)
end

return shop