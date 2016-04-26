local popup = {}

function popup.refresh()--Send update to graphic view
	local state = require('state')
	local cjson = require('cjson')
	return cjson.encode({
		key="popup",
		options=popup.options
	})
end

function popup.processinput()
	popup=nil
	local state = require('state')
	if state.context.input=='select' then return true elseif state.context.input=='back' then return false end
end

function popup.loadcontext(options)
	popup.options = options
end

return popup