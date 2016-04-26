local shop = {}

local function buy(item)
	local state = require('state')
	if state.mc.money > item[2] then
		state.mc.money=state.mc.money-item[2]--item[1]=name, item[2]=cost
		state.mc.items={item[1]}
		return true
	end
	return false
end

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
			print(current[1])
			if type(current[1])=='string' then--If element is purchasable then engage in purchase logic
				local canbuy = buy(current)
				if canbuy then
					items[index][1]="Bought "..current[1].." for "..current[2].." yen!"
					print(items[index][1])
				else
					items[index][1]="Not enough money to purchase "..current[1].."!"
				end
				shop.depth[#shop.depth]=nil--Don't want to get stuck at the buying level, so reset to previous one after purchase. Be careful to catch select input when on the buy screen as in that context or player will be stuck buy the same thing over and over
				return items--Purchase is end-tree interaction. Do not try and continue parsing
			end
			for singlekey, singlevalue in pairs(current) do
				print(singlekey, singlevalue)
				if type(singlevalue)=='table' then
					for name, subcat in pairs(singlevalue) do--singlevalue ALWAYS contains only ONE key (NOT TRUE! LOADED ITEMS ARE PROPERLY MAPPED!), value pair the exta layer is for ordering purposes because lua
						if type(subcat)=='table' then--the "next value" in the "tree" is either a table or a function. if table...
							for subcatname, subcatsubcat in pairs(subcat) do--there's only one key in the table by design so add that key to the list
								if type(subcatname)=='string' then--LEGACY?
									items[index][#items[index]+1]=subcatname
								elseif type(subcatname)=='number' and type(subcatsubcat[1])=='string' then--For case where list was loaded, then back was pressed. List is cached for future use
									items[index][#items[index]+1]=subcatsubcat[1]
								else
									items[index][#items[index]+1]=subcatsubcat
								end
								print(subcatname, subcatsubcat)
							end
						else--if function, place the return of the function in the list
							print('Function detected')
							for loadeditemindex, itemname in pairs(loadstring(subcat)()) do
								print("Name", itemname)
								items[index][loadeditemindex]=itemname[1]
							end
							for salti, saltv in pairs(items[index]) do print("Salt", salti, saltv) end
							singlevalue[name]=loadstring(subcat)()--items[index]
						end
					
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
	if shop.popup do shop.popup.processinput() shop.popup=nil return end
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