local shop = {}

local function _load(shopinquestion)
	local json = require ('json_reader')
	shop.menu=json.read({file='shopmenus.json'})[shopinquestion]
end

local function genmenus()
	local state = require('state')
	local items = {}
	local i = 1
	for key, value in pairs(shop.menu.order) do
		items[i]={}
		items[i]=value
		i=i+1
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
	state.loading(false)
end

return shop