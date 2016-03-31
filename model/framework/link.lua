cut = nil
--cut should actually be in gamestate table

local function _load(sociallink)
	require ('json_reader')
	local level = tonumber(sociallink.level)
	local angle = tonumber(sociallink.angle)
	local link = read({file=sociallink.arcana..'_link.json'})
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
	return angleladder.cutscene
end

local function getcut(sociallink)
	cut = _load(sociallink)
	cut.index=1
	--print("Cut is wrong cut")
	return cut.items[1]
end

function SocialLink(sociallink)
	if not cut or cut.id~=sociallink.arcana..sociallink.level..'_'..sociallink.angle then return getcut(sociallink) end
	--print("Cut is right cut")
	return cut.items[sociallink.index]
end

print(SocialLink({arcana='Aeon', level='1', angle='0'})[1].text)
print(SocialLink({arcana='Aeon', level='1', angle='0', index=2})[1].text)
print(SocialLink({arcana='Aeon', level='2', angle='0'})[1].text)
	