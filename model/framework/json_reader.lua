function get(datapath)
	local json = require('cjson')
	local file = io.open(datapath.file)
	local todecode = file:read "*a"
	local decoded = json.decode(todecode)
	if datapath.path then
		return (decoded[datapath.path])
	end
	return decoded
end
--print (get({file='data.json', path='test'}))