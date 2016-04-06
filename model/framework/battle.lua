local battle = {}

local function turn()
	local state = require('state')
	state.lock()
	while state.battle.party[state.battle.participants[state.battle.open].name]==nil do
		print(state.battle.participants[state.battle.open].name.." used Splash, but nothing happened!\n")
		state.battle.open=state.battle.open+1
		if state.battle.open>#state.battle.participants then state.battle.open=1 end
		battle.refresh()
	end
	state.unlock()
end

local function detorder()
	local state = require('state')
	local done=false
	while not done do
		done=true
		for i=1, #state.battle.participants-1 do
			if state.battle.participants[i].persona.agi<state.battle.participants[i+1].persona.agi then
				temp=state.battle.participants[i]
				state.battle.participants[i]=state.battle.participants[i+1]
				state.battle.participants[i+1]=temp
				done=false
			end
		end
	end
	state.battle.open = 1
	for i=1, #state.battle.participants do print(state.battle.participants[i].persona.name, state.battle.participants[i].persona.agi) end
	turn()
end

local function _load(inst)
	local state = require('state')
	state.battle={}
	state.battle.party={}
	state.battle.ene={}
	state.battle.participants = {}
	for i=1, #inst.party do state.battle.party[inst.party[i].name]=true state.battle.participants[#state.battle.participants+1]=inst.party[i] end
	for i=1, #inst.ene do state.battle.ene[i]=inst.ene[i].name state.battle.participants[#state.battle.participants+1]=inst.ene[i] end
	detorder()
end


function battle.refresh()
	local state = require('state')
	state.update={'None'}
end

function battle.processinput(input)
	local state = require('state')
	if input=='select' then
		print(state.battle.participants[state.battle.open].name.." used Agi!")
		state.battle.open=state.battle.open+1
		if state.battle.open>#state.battle.participants then state.battle.open=1 end
		print("Next participant: "..state.battle.participants[state.battle.open].name.."\n")
	end
	turn()
end

function battle.loadcontext(inst)
	local state = require('state')
	state.context=battle
	_load(inst)
	battle.refresh()
end

return battle