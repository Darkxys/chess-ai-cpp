#pragma once
#include <map>
#include <string>
#include "Game.h"
#include "Point.h"
#include "Color.h"
#include "ChessMove.h"
#include "ChessState.h"

class ChessGame : Game<ChessState, ChessMove>
{
private:
	std::map<std::string, unsigned int> stateHistory_;
public:
	std::unique_ptr<ChessState> nextState(ChessState s, ChessMove m);
	std::vector<ChessMove> getLegalMoves(ChessState s);
	std::unique_ptr<ChessState> getStartingState();
	bool isGameEnded(ChessState s);
	float getGameReward(ChessState s);
};

