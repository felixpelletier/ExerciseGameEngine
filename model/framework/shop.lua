local shop = {}

local function _load(shopinquestion)
	local json = require ('json_reader')
	shop.menu=json.read({file='shopmenus.json'})
	shop.depth = {[0]=shopinquestion}
end

local function genmenus()
	local state = require('state')
	local items = {{}}
	local current=shop.menu
	for index, nextlevel in pairs(shop.depth) do
		print("Next level of depth:", index, nextlevel)
		for key, value in pairs(current) do print(key, value) end
		current=current[nextlevel]
		for order, menuitem in pairs(current) do
			for i=1, 1 do
				for name, tree in pairs(menuitem) do
					print(order, name, tree)
					items[i][#items[i]+1]=name
				end
			end
		end
	end
	for order, item in pairs(items[1]) do print(order, item) end
	return items
end

function shop.refresh()
	local state = require('state')
	local cjson = require('cjson')
	state.update = cjson.encode({key="shop.show.menutree", menus=genmenus()})
end

function shop.processinput()
	local state = require('state')
	shop.depth[#shop.depth+1]=state.context.index
	for key, value in pairs(shop.depth) do print(key, value) end
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