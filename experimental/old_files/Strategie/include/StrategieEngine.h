#include <boost/thread.hpp> 
#include <boost/python.hpp>
#include <Vector.h>
#include <GameState.h>
#include <StrategyState.h>

namespace Rule { namespace Strategie { 

class StrategieEngine {
	struct GameState gameState;
	struct StrategyState strategyState;
	
	void updatePosition();
	private:
		boost::thread updateThread;
	public:
		StrategieEngine();
		~StrategieEngine();
		void setGameState(struct GameState data);
		struct StrategyState getState();
};

} }
