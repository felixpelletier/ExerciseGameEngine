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
	local state = require('state')
	state.cut = angleladder
	state.cut.open = angleladder.cutscene.items[1]
	state.cut.index = 2
end

local function showSpeak()
	local state = require('state')
	local choices = {}
	if #state.cut.open > 2 then
		for i=2, #state.cut.open do choices[#choices+1]=state.cut.cutscene.items[i][1].text end --Won't show anything for physical action based choices
	end
	return {
		key="Social Link Speak Action",
		assets={['textbox.png']={0,0}, [state.cut.open[1].speaker..'.png']={0,0}},
		text=state.cut.open[1].text,
		speaker=state.cut.open[1].speaker,
		options=choices
		--Need emotion (domo arigatou, Mr. Roboto)
	}
end

local function showMove()
	local state = require('state')
	return {
		key="Social Link Move Action",
		assets={[state.cut.open[1].subject]={state.cut.open[1].move, state.cut.open[1].animation}}
	}
end

--local function showInfo() end Ignore Info actions. These should never show up in the game

local function showCam()
	local state = require('state')
	return {
		key="Social Link Camera Action",
		place=state.cut.open[1].place,
		camera={state.cut.open[1].lookAt, state.cut.open[1].cameraPosition}
	}
end

function link.refresh()--Send update to graphic view
	local state = require('state')
	if state.cut.open then
		print("\nAction:\n"..state.cut.open[1].text.."\n")
		state.update = state.cut.open.show
	end
end

local function socialLink()
	local state = require('state')
	return state.cut.cutscene.items[state.cut.open[state.cut.index]+1]
end

function link.processinput(input)
	print("Processing input in context: Social Link")
	local state = require('state')
	if input=='select' then
		state.cut.open = socialLink()
		if state.cut.open[1].points then state.cut.open.show=showSpeak() elseif state.cut.open[1].place then state.cut.open.show=showCam() elseif state.cut.open[1].animation then state.cut.open.show=showMove() end
		state.cut.index = 2
	elseif input=='up' then
		if state.cut.open[state.cut.index+1] then state.cut.index=state.cut.index+1	return end
	elseif input=='down' then
		if state.cut.open[state.cut.index-1] and state.cut.index-1>=2 then state.cut.index=state.cut.index-1 return end
	else print("Input "..input.." not valid in this context") return end
	link.refresh()
	if state.cut.open[1].place or state.cut.open[1].animation then link.processinput('select') end
end

function link.loadcontext(sociallink)
	local state = require('state')
	state.context=link
	_load(sociallink)
	link.refresh()
end

return link