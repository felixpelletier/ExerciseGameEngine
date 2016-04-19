local shop = {}

local function _load(shopinquestion)
	local json = require ('json_reader')
	shop.menu=json.read({file='shopmenus.json'})[shopinquestion]
	shop.depth = {}
end

local function genmenus()
	local state = require('state')
	local items = {{}}
	local current=shop.menu
	for index, toplevel in pairs(shop.menu) do for name, tree in pairs(toplevel) do items[1][index]=name end end
	for index, nextlevel in pairs(shop.depth) do
		current=current[nextlevel]
		items[index]={}
		for order, menuitem in pairs(current) do
			for name, tree in pairs(menuitem) do
				print("Putting "..name.." in "..index)
				items[index][#items[index]+1]=name
			end
		end
	end
	for order, item in pairs(items) do print(order, item, key, value) end
	return items
end

function shop.refresh()
	local state = require('state')
	local cjson = require('cjson')
	state.update = cjson.encode({key="shop.show.menutree", menus=genmenus()})
end

function shop.processinput()
	local state = require('state')
	shop.depth[#shop.depth+2]=state.context.index
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