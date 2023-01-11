#pragma once
#include <string>
#include "Bitboard.h"
#include "Pieces.h"
#include "State.h"
#include "Color.h"
#include "ChessMove.h"

struct ChessState : State<ChessState, ChessMove>
{
	static const int c_PIECES_AMOUNT = 12;

	ChessState() : ChessState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR") {};
	ChessState(std::string fen);

	void displayState();
	std::string toFEN();
	Bitboard getOccupancyBoard();

	Bitboard getBishopAttacks(int square);
	Bitboard getRookAttacks(int square);
	Bitboard getQueenAttacks(int square);
	Bitboard getNonSlidingPieceAttacks(Pieces piece, int square);

	std::vector<ChessMove> generateLegalMoves();
	std::unique_ptr<ChessState> getNextState(ChessMove m);

private:
	static bool isAttacksInitialized;
	Bitboard bitboards[c_PIECES_AMOUNT];
	U64 occupancies_;
	Color side_;		// Current player playing
	int castle_;		// Castle rights
	int enpassant_;	// Enpassant square

	// Init sliders attack masks
	static Bitboard s_ROOK_MASKS[64];
	static Bitboard s_BISHOP_MASKS[64];

	// Init sliders attacks
	static Bitboard s_ROOK_ATTACKS[64][4096];
	static Bitboard s_BISHOP_ATTACKS[64][512];

	void initializeSliderAttacks();
	void initializeNonSliderAttacks();

	Bitboard generateBishopAttackMask(int square);
	Bitboard generateRookAttackMask(int square);

	U64 generateOccupancyBoard();
	Bitboard getBishopAttacksSlow(int square, Bitboard blockers);
	Bitboard getRookAttacksSlow(int square, Bitboard blockers);
	Bitboard setOccupancy(int index, int bitsInMask, Bitboard attackMask);

	std::unique_ptr<ChessState> makeMove(ChessMove m);
	std::vector<ChessMove> generateAllMoves();
};

