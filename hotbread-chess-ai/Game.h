#pragma once
#include "State.h"
#include "Color.h"
#include "Move.h"

template<class DerivedState, class DerivedMove>
class Game
{
public:
	virtual std::unique_ptr<DerivedState> nextState(DerivedState s, DerivedMove m) = 0;
	virtual std::vector<DerivedMove> getLegalMoves(DerivedState s) = 0;
	virtual std::unique_ptr<DerivedState> getStartingState() = 0;
	virtual bool isGameEnded(DerivedState s) = 0;
	virtual float getGameReward(DerivedState s) = 0;
};

