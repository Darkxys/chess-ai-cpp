#include "ChessMove.h"

ChessMove::ChessMove(int source, int target, int piece, int promotion, bool capture, bool doublePush, bool enpassant, bool castling)
{
	this->source_ = source;
	this->target_ = target;
	this->piece_ = piece;
	this->promotion_ = promotion;
	this->capture_ = capture;
	this->doublePush_ = doublePush;
	this->enpassant_ = enpassant;
	this->castling_ = castling;
}

__int8 ChessMove::source()
{
	return this->source_;
}

__int8 ChessMove::target()
{
	return this->target_;
}

__int8 ChessMove::piece()
{
	return this->piece_;
}

__int8 ChessMove::promotion()
{
	return this->promotion_;
}

bool ChessMove::capture()
{
	return this->capture_;
}

bool ChessMove::doublePush()
{
	return this->doublePush_;
}

bool ChessMove::enpassant()
{
	return this->enpassant_;
}

bool ChessMove::castling()
{
	return this->castling_;
}
