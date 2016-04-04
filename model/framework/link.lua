local link = {}

local function _load(sociallink)
	local json = require ('json_reader')
	local level = tonumber(sociallink.level)
	local angle = tonumber(sociallink.angle)
	local link = json.read({file=sociallink.arcana..'_link.json'})
	local angleladder = {angle=nil}
	local ladderdown = nil
	local ladderup = nil
	for key, value in pairs(link.cutscenes) do
		local loopangle = tonumber(string.sub(key, string.find(key, '_')+1, -1))
		local ladder = nil
		if angleladder.angle then
			ladder = tonumber(string.sub(angleladder.angle, string.find(angleladder.angle, '_')+1, -1))
		end
		if (string.find(key, level..'_') and loopangle<=angle and ( (ladder and loopangle>ladder) or not angleladder.angle)) then
			angleladder.cutscene=value
			angleladder.angle=key
		end
		if string.find(key, level..'_') and (ladderdown==nil or loopangle>ladderdown) then ladderdown=loopangle end
		if string.find(key, level..'_') and (ladderup==nil or loopangle<ladderup) then ladderup=loopangle end
	end
	if angleladder.angle==nil then
		if angle>ladderdown then
			angleladder.angle=level..'_'..ladderdown
			angleladder.cutscene=link.cutscenes[level..'_'..ladderdown]
		else
			angleladder.angle=level..'_'..ladderup
			angleladder.cutscene=link.cutscenes[level..'_'..ladderup]
		end
	end
	--for key, value in pairs(angleladder.cutscene.items[1][1]) do print(key, value) end
	local state = require('state')
	state.cut = angleladder
	state.cut.open = angleladder.cutscene.items[1]
	--return angleladder
end

function link.refresh()
	local state = require('state')
	if state.cut.open then
		print(state.cut.open[1].text) end
end

function link.SocialLink()
	local state = require('state')
	return state.cut.cutscene.items[state.cut.open[state.cut.index]]
end

function link.processinput(input)
	local state = require('state')
	if input=='select' then
		state.cut.open = link.SocialLink()
		state.cut.index = 2
	elseif input=='up' then
		if state.cut.open[state.cut.index+1] then state.cut.index=state.cut.index+1	end
	elseif input=='down' then
		if state.cut.open[state.cut.index-1] and state.cut.index-1>=2 then state.cut.index=state.cut.index-1 end
	else return end
	link.refresh()
end

function link.loadcontext(sociallink)
	local state = require('state')
	state.context=link
	_load(sociallink)
end

return link