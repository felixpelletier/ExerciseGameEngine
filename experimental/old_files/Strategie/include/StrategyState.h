#ifndef POC_STRATSTATE
#define POC_STRATSTATE

#include "Vector.h"

namespace Rule { namespace Strategie { 

//This is the strategy engine's response.
//It tells the main game engine where it wants it's players. 
//
//May contain the position of the ball, the players, the time,
//if the game is running or not. Etc.
struct StrategyState{
	struct Vector players[12];
	void setPlayer(int i, Vector player) { players[i] = player; };
    	struct Vector getPlayer(int i) const { return players[i]; };
	
};

} }

#endif


