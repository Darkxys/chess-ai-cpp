#include <iostream>
#include <vector>
#include "ChessState.h"
#include "Bitboard.h"

int main() {
	ChessState state = ChessState("rnbqkbnr/pppppppp/8/8/2B5/8/PPPPPPPP/RNBQKBNR");
	ChessState state1 = ChessState("r3k2r/p1ppqpb1/bn2pnp1/3PN3/1p2P3/2N2Q1p/PPPBBPPP/R3K2R");
	state.displayState();
	std::cout << std::endl << state.toFEN() << std::endl << std::endl;
	return 0;
}