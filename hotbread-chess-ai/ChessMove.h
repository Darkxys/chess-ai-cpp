#pragma once
#include "Move.h"

class ChessMove : Move<ChessMove>
{
private:
	// Properties
	__int8 source_;
	__int8 target_;
	__int8 piece_;
	__int8 promotion_;
	bool capture_;
	bool doublePush_;
	bool enpassant_;
	bool castling_;
public:

	// Constructor
	ChessMove() : ChessMove(0,0,0,0) {};
	ChessMove(int source, int target, int piece, int promotion, bool capture = false, bool doublePush = false, bool enpassant = false, bool castling = false);

	// Getters
	__int8 source();
	__int8 target();
	__int8 piece();
	__int8 promotion();
	bool capture();
	bool doublePush();
	bool enpassant();
	bool castling();
};

