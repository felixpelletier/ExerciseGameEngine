function initiate()
	local state = require('state')
	state.lock()
	
	state.flags = {}
	state.day={id=1, time='Early Morning'}
	state.place={map='Home'}
	state.slglobal={
		Fool={0, 0},
		Magician={0, 0},
		Priestess={0, 0},
		Empress={0, 0},
		Emperor={0, 0},
		Hierophant={0, 0},
		Lovers={0, 0},
		Chariot={0, 0},
		Justice={0, 0},
		Hermit={0, 0},
		Fortune={0, 0},
		Strength={0, 0},
		HangedMan={0, 0},
		Death={0, 0},
		Temperance={0, 0},
		Devil={0, 0},
		Tower={0, 0},
		Star={0, 0},
		Moon={0, 0},
		Sun={0, 0},
		Judgement={0, 0},
		World={0, 0},
		Aeon={0, 0},
		Void={0, 0}
	}
	state.mc={
		money=0,
		name="",
		personalist={},
		persona={},
		stats={courage=1, charm=1, academics=1},
		gear={shoes='Normal Shoes', armour='Real Clothes', accessory='Hair'}
	}
	state.availablechars={}
	state.party={{}}
	state.version='Version 0.0.0.0'
	
	state.unlock()
end