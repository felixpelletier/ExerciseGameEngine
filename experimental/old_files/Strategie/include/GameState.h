#ifndef POC_GAMESTATE
#define POC_GAMESTATE

#include "Vector.h"

namespace Rule { namespace Strategie { 

//This is the current state of the game
//
//May contain the position of the ball, the players, the time,
//if the game is running or not. Etc.
struct GameState{
	struct Vector players[12];
	void setPlayer(int i, Vector player) { players[i] = player; }
    	struct Vector getPlayer(int i) const { return players[i]; };
	long time;
	long getTime() const { return time; };
};

} }

#endif
