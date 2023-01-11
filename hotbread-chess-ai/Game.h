#pragma once
#include "State.h"
#include "Color.h"
#include "Move.h"

template<class DerivedState, class DerivedMove>
class Game
{
public:
	virtual DerivedState nextState(const DerivedState s, DerivedMove m) = 0;
	virtual std::vector<DerivedMove> getLegalMoves(const DerivedState s, const Color c) = 0;
	virtual DerivedState getStartingState() = 0;
	virtual bool isGameEnded(const DerivedState s) = 0;
	virtual float getGameReward(const DerivedState s) = 0;
};

