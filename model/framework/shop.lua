local shop = {}

local function _load(shopinquestion)
	local json = require ('json_reader')
	shop.menu=json.read({file='shopmenus.json'})
end

local function genmenus()
	local state = require('state')
	local items = {{}}
	for order, menuitem in pairs(shop.menu.trainer) do
		for i=1, 1 do
			for name, tree in pairs(menuitem) do
				print(name, tree)
				items[i]=name
			end
		end
	end
	if not state.context.index then return items end
	print(state.context.index)
end

function shop.refresh()
	local state = require('state')
	local cjson = require('cjson')
	state.update = cjson.encode({key="shop.show.menutree", menus=genmenus()})
end

function shop.processinput()
	shop.refresh()
end

function shop.loadcontext(shopinquestion)
	local state = require('state')
	state.context=shop
	_load(shopinquestion)
	shop.refresh()
end

return shop