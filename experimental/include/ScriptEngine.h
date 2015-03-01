#pragma once

#include <boost/thread.hpp> 
#include <boost/python.hpp>

namespace Soul { namespace Script { 

class StrategieEngine {
	struct GameState gameState;
	struct StrategyState strategyState;
	
	void updatePosition();
	private:
	public:
		StrategieEngine();
		~StrategieEngine();
		void setGameState(struct GameState data);
		struct StrategyState getState();
};

} }
