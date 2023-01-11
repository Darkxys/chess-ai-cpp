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
	ChessState nextState(const ChessState s, ChessMove m);
	std::vector<ChessMove> getLegalMoves(const ChessState s, const Color c);
	ChessState getStartingState();
	bool isGameEnded(const ChessState s);
	float getGameReward(const ChessState s);
};

