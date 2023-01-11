#include "ChessState.h"

// Static variable definitions
Bitboard ChessState::s_ROOK_MASKS[64] = {};
Bitboard ChessState::s_BISHOP_MASKS[64] = {};
Bitboard ChessState::s_ROOK_ATTACKS[64][4096] = {};
Bitboard ChessState::s_BISHOP_ATTACKS[64][512] = {};
bool ChessState::isAttacksInitialized = false;

// Constant array for lookups
const int c_BISHOP_INDEX_BITS[64] = {
	6, 5, 5, 5, 5, 5, 5, 6,
	5, 5, 5, 5, 5, 5, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 9, 9, 7, 5, 5,
	5, 5, 7, 7, 7, 7, 5, 5,
	5, 5, 5, 5, 5, 5, 5, 5,
	6, 5, 5, 5, 5, 5, 5, 6
};
const int c_ROOK_INDEX_BITS[64] = {
	12, 11, 11, 11, 11, 11, 11, 12,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	11, 10, 10, 10, 10, 10, 10, 11,
	12, 11, 11, 11, 11, 11, 11, 12
};
const U64 c_ROOK_MAGICS[64] = {
	0x8a80104000800020ULL,
	0x140002000100040ULL,
	0x2801880a0017001ULL,
	0x100081001000420ULL,
	0x200020010080420ULL,
	0x3001c0002010008ULL,
	0x8480008002000100ULL,
	0x2080088004402900ULL,
	0x800098204000ULL,
	0x2024401000200040ULL,
	0x100802000801000ULL,
	0x120800800801000ULL,
	0x208808088000400ULL,
	0x2802200800400ULL,
	0x2200800100020080ULL,
	0x801000060821100ULL,
	0x80044006422000ULL,
	0x100808020004000ULL,
	0x12108a0010204200ULL,
	0x140848010000802ULL,
	0x481828014002800ULL,
	0x8094004002004100ULL,
	0x4010040010010802ULL,
	0x20008806104ULL,
	0x100400080208000ULL,
	0x2040002120081000ULL,
	0x21200680100081ULL,
	0x20100080080080ULL,
	0x2000a00200410ULL,
	0x20080800400ULL,
	0x80088400100102ULL,
	0x80004600042881ULL,
	0x4040008040800020ULL,
	0x440003000200801ULL,
	0x4200011004500ULL,
	0x188020010100100ULL,
	0x14800401802800ULL,
	0x2080040080800200ULL,
	0x124080204001001ULL,
	0x200046502000484ULL,
	0x480400080088020ULL,
	0x1000422010034000ULL,
	0x30200100110040ULL,
	0x100021010009ULL,
	0x2002080100110004ULL,
	0x202008004008002ULL,
	0x20020004010100ULL,
	0x2048440040820001ULL,
	0x101002200408200ULL,
	0x40802000401080ULL,
	0x4008142004410100ULL,
	0x2060820c0120200ULL,
	0x1001004080100ULL,
	0x20c020080040080ULL,
	0x2935610830022400ULL,
	0x44440041009200ULL,
	0x280001040802101ULL,
	0x2100190040002085ULL,
	0x80c0084100102001ULL,
	0x4024081001000421ULL,
	0x20030a0244872ULL,
	0x12001008414402ULL,
	0x2006104900a0804ULL,
	0x1004081002402ULL,
};
const U64 c_BISHOP_MAGICS[64] = {
	0x40040844404084ULL,
	0x2004208a004208ULL,
	0x10190041080202ULL,
	0x108060845042010ULL,
	0x581104180800210ULL,
	0x2112080446200010ULL,
	0x1080820820060210ULL,
	0x3c0808410220200ULL,
	0x4050404440404ULL,
	0x21001420088ULL,
	0x24d0080801082102ULL,
	0x1020a0a020400ULL,
	0x40308200402ULL,
	0x4011002100800ULL,
	0x401484104104005ULL,
	0x801010402020200ULL,
	0x400210c3880100ULL,
	0x404022024108200ULL,
	0x810018200204102ULL,
	0x4002801a02003ULL,
	0x85040820080400ULL,
	0x810102c808880400ULL,
	0xe900410884800ULL,
	0x8002020480840102ULL,
	0x220200865090201ULL,
	0x2010100a02021202ULL,
	0x152048408022401ULL,
	0x20080002081110ULL,
	0x4001001021004000ULL,
	0x800040400a011002ULL,
	0xe4004081011002ULL,
	0x1c004001012080ULL,
	0x8004200962a00220ULL,
	0x8422100208500202ULL,
	0x2000402200300c08ULL,
	0x8646020080080080ULL,
	0x80020a0200100808ULL,
	0x2010004880111000ULL,
	0x623000a080011400ULL,
	0x42008c0340209202ULL,
	0x209188240001000ULL,
	0x400408a884001800ULL,
	0x110400a6080400ULL,
	0x1840060a44020800ULL,
	0x90080104000041ULL,
	0x201011000808101ULL,
	0x1a2208080504f080ULL,
	0x8012020600211212ULL,
	0x500861011240000ULL,
	0x180806108200800ULL,
	0x4000020e01040044ULL,
	0x300000261044000aULL,
	0x802241102020002ULL,
	0x20906061210001ULL,
	0x5a84841004010310ULL,
	0x4010801011c04ULL,
	0xa010109502200ULL,
	0x4a02012000ULL,
	0x500201010098b028ULL,
	0x8040002811040900ULL,
	0x28000010020204ULL,
	0x6000020202d0240ULL,
	0x8918844842082200ULL,
	0x4010011029020020ULL,
};
const U64 FILE_H = 0x8080808080808080ull;
const U64 FILE_G = 0x4040404040404040ull;
const U64 FILE_B = 0x202020202020202ull;
const U64 FILE_A = 0x101010101010101ull;
U64 nonSlidingAttacks[ChessState::c_PIECES_AMOUNT][64];

ChessState::ChessState(std::string fen)
{
	int square = 0;
	for (size_t index = 0; index < fen.size() && fen[index] != ' '; index++) {
		if (fen[index] == '/') continue;

		if (fen[index] >= '1' && fen[index] <= '8') {
			square += fen[index] - '1';
		}

		switch (fen[index]) {
		case 'P':
			this->bitboards[Pieces::P].setBit(square);
			break;
		case 'R':
			this->bitboards[Pieces::R].setBit(square);
			break;
		case 'B':
			this->bitboards[Pieces::B].setBit(square);
			break;
		case 'N':
			this->bitboards[Pieces::N].setBit(square);
			break;
		case 'Q':
			this->bitboards[Pieces::Q].setBit(square);
			break;
		case 'K':
			this->bitboards[Pieces::K].setBit(square);
			break;
		case 'p':
			this->bitboards[Pieces::p].setBit(square);
			break;
		case 'r':
			this->bitboards[Pieces::r].setBit(square);
			break;
		case 'b':
			this->bitboards[Pieces::b].setBit(square);
			break;
		case 'n':
			this->bitboards[Pieces::n].setBit(square);
			break;
		case 'q':
			this->bitboards[Pieces::q].setBit(square);
			break;
		case 'k':
			this->bitboards[Pieces::k].setBit(square);
			break;
		}

		square++;
	}

	// Generate color, castling_rules and enpassant square from fen
	this->side_ = Color::White;
	this->castle_ = 0b1111;
	this->enpassant_ = 0;

	if (!this->isAttacksInitialized) {
		this->isAttacksInitialized = true;

		// Initialize rook and bishop attack array
		this->initializeSliderAttacks();
		this->initializeNonSliderAttacks();
	}

	this->occupancies_ = this->generateOccupancyBoard();
}

void ChessState::displayState()
{
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int piece = 0;
			int square = row * 8 + col;

			for (int index = 0; index < this->c_PIECES_AMOUNT; index++) {
				if (this->bitboards[index].getBit(square)) {
					piece = index + 1;
					break;
				}
			}
			std::cout << piece << "\t";
		}
		std::cout << std::endl;
	}
}

std::string ChessState::toFEN()
{
	std::string fen = "";
	int counter = 0;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			int piece = -1;
			int square = row * 8 + col;

			for (int index = 0; index < this->c_PIECES_AMOUNT; index++) {
				if (this->bitboards[index].getBit(square)) {
					piece = index;
					break;
				}
			}

			if (counter > 0 && piece != -1) {
				fen += std::to_string(counter);
				counter = 0;
			}

			switch (piece) {
			case Pieces::P: fen += 'P';
				break;
			case Pieces::R: fen += 'R';
				break;
			case Pieces::B: fen += 'B';
				break;
			case Pieces::N: fen += 'N';
				break;
			case Pieces::Q: fen += 'Q';
				break;
			case Pieces::K: fen += 'K';
				break;
			case Pieces::p: fen += 'p';
				break;
			case Pieces::r: fen += 'r';
				break;
			case Pieces::b: fen += 'b';
				break;
			case Pieces::n: fen += 'n';
				break;
			case Pieces::q: fen += 'q';
				break;
			case Pieces::k: fen += 'k';
				break;
			default:
				counter++;
			}
		}

		if (counter > 0) {
			fen += std::to_string(counter);
			counter = 0;
		}

		if (row + 1 < 8) fen += '/';
	}

	return fen;
}

Bitboard ChessState::getOccupancyBoard()
{
	return this->occupancies_;
}

void ChessState::initializeSliderAttacks()
{
	for (int square = 0; square < 64; square++) {
		this->s_BISHOP_MASKS[square] = this->generateBishopAttackMask(square);
		this->s_ROOK_MASKS[square] = this->generateRookAttackMask(square);

		int bishopCounts = this->s_BISHOP_MASKS[square].countBits();
		int rookCounts = this->s_ROOK_MASKS[square].countBits();

		int bishopOccupancyIndex = (1 << bishopCounts);
		int rookOccupancyIndex = (1 << rookCounts);

		// Loop to generate possible moves for bishop at square
		for (int index = 0; index < bishopOccupancyIndex; index++) {
			Bitboard occupancy = this->setOccupancy(index,bishopCounts, this->s_BISHOP_MASKS[square]);
			U64 magicIndex = (occupancy.getBoard() * c_BISHOP_MAGICS[square]) >> (64 - c_BISHOP_INDEX_BITS[square]);
			this->s_BISHOP_ATTACKS[square][magicIndex] = getBishopAttacksSlow(square, occupancy);
		}

		// Loop to generate possible moves for bishop at square
		for (int index = 0; index < rookOccupancyIndex; index++) {
			Bitboard occupancy = this->setOccupancy(index,rookCounts, this->s_ROOK_MASKS[square]);
			U64 magicIndex = (occupancy.getBoard() * c_ROOK_MAGICS[square]) >> (64 - c_ROOK_INDEX_BITS[square]);
			this->s_ROOK_ATTACKS[square][magicIndex] = getRookAttacksSlow(square, occupancy);
		}
	}
}

void ChessState::initializeNonSliderAttacks()
{
	for (int i = 0; i < 64; i++) {
		U64 start = 1ULL << i;

		// Get king attack mask from square 'i'
		U64 attackKing = (((start << 7) | (start >> 9) | (start >> 1)) & (~FILE_H)) |
			(((start << 9) | (start >> 7) | (start << 1)) & (~FILE_A)) |
			((start >> 8) | (start << 8));

		// Get knight attack masks from square 'i'
		U64 attackKnights = (((start << 10) | (start >> 6)) & ~(FILE_A | FILE_B)) |
			(((start >> 10) | (start << 6)) & ~(FILE_H | FILE_G)) | 
			(((start << 17) | (start >> 15)) & ~(FILE_A)) | 
			(((start >> 17) | (start << 15)) & ~(FILE_H));

		// Get pawn attack masks from square 'i'
		U64 attackPawnW = ((start >> 7) & ~FILE_A) | ((start >> 9) & ~FILE_H) | (start >> 8) | (i / 8 == 6 ? (start >> 16) : 0ULL);
		U64 attackPawnB = ((start << 7) & ~FILE_H) | ((start << 9) & ~FILE_A) | (start << 8) | (i / 8 == 1 ? (start << 16) : 0ULL);

		nonSlidingAttacks[Pieces::K][i] = attackKing;
		nonSlidingAttacks[Pieces::k][i] = attackKing;

		nonSlidingAttacks[Pieces::N][i] = attackKnights;
		nonSlidingAttacks[Pieces::n][i] = attackKnights;

		nonSlidingAttacks[Pieces::P][i] = attackPawnW;
		nonSlidingAttacks[Pieces::p][i] = attackPawnB;
	}
}

Bitboard ChessState::getBishopAttacksSlow(int square, Bitboard block)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// generate bishop atacks
	for (r = tr + 1, f = tf + 1; r <= 7 && f <= 7; r++, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr - 1, f = tf + 1; r >= 0 && f <= 7; r--, f++)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr + 1, f = tf - 1; r <= 7 && f >= 0; r++, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	for (r = tr - 1, f = tf - 1; r >= 0 && f >= 0; r--, f--)
	{
		attacks |= (1ULL << (r * 8 + f));
		if ((1ULL << (r * 8 + f)) & block.getBoard()) break;
	}

	// return attack map
	return attacks;
}

Bitboard ChessState::getRookAttacksSlow(int square, Bitboard block)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// generate rook attacks
	for (r = tr + 1; r <= 7; r++)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block.getBoard()) break;
	}

	for (r = tr - 1; r >= 0; r--)
	{
		attacks |= (1ULL << (r * 8 + tf));
		if ((1ULL << (r * 8 + tf)) & block.getBoard()) break;
	}

	for (f = tf + 1; f <= 7; f++)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block.getBoard()) break;
	}

	for (f = tf - 1; f >= 0; f--)
	{
		attacks |= (1ULL << (tr * 8 + f));
		if ((1ULL << (tr * 8 + f)) & block.getBoard()) break;
	}

	// return attack map
	return attacks;
}

Bitboard ChessState::getBishopAttacks(int square)
{
	U64 occupancy = this->occupancies_;
	// get bishop attacks assuming current board occupancy
	occupancy &= s_BISHOP_MASKS[square].getBoard();
	occupancy *= c_BISHOP_MAGICS[square];
	occupancy >>= 64 - c_BISHOP_INDEX_BITS[square];

	// return bishop attacks
	return s_BISHOP_ATTACKS[square][occupancy];
}

Bitboard ChessState::getRookAttacks(int square)
{
	U64 occupancy = this->occupancies_;
	// get bishop attacks assuming current board occupancy
	occupancy &= s_ROOK_MASKS[square].getBoard();
	occupancy *= c_ROOK_MAGICS[square];
	occupancy >>= 64 - c_ROOK_INDEX_BITS[square];

	// return bishop attacks
	return s_ROOK_ATTACKS[square][occupancy];
}

Bitboard ChessState::getQueenAttacks(int square)
{
	return this->getBishopAttacks(square).getBoard() | this->getRookAttacks(square).getBoard();
}

Bitboard ChessState::getNonSlidingPieceAttacks(Pieces piece, int square)
{
	return nonSlidingAttacks[piece][square];
}

std::vector<ChessMove> ChessState::generateLegalMoves()
{
	std::vector<ChessMove> allMoves = this->generateAllMoves();
	std::vector<ChessMove> legalMoves = std::vector<ChessMove>();

	for (ChessMove move : allMoves) {
		if (this->makeMove(move))
			legalMoves.push_back(move);
	}

	return legalMoves;
}

std::unique_ptr<ChessState> ChessState::getNextState(ChessMove m)
{
	return this->makeMove(m);
}

Bitboard ChessState::generateBishopAttackMask(int square)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// mask relevant bishop occupancy bits
	for (r = tr + 1, f = tf + 1; r <= 6 && f <= 6; r++, f++) 
		attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf + 1; r >= 1 && f <= 6; r--, f++) attacks |= (1ULL << (r * 8 + f));
	for (r = tr + 1, f = tf - 1; r <= 6 && f >= 1; r++, f--) attacks |= (1ULL << (r * 8 + f));
	for (r = tr - 1, f = tf - 1; r >= 1 && f >= 1; r--, f--) attacks |= (1ULL << (r * 8 + f));

	// return attack map
	return attacks;
}

Bitboard ChessState::generateRookAttackMask(int square)
{
	// result attacks bitboard
	U64 attacks = 0ULL;

	// init ranks & files
	int r, f;

	// init target rank & files
	int tr = square / 8;
	int tf = square % 8;

	// mask relevant rook occupancy bits
	for (r = tr + 1; r <= 6; r++) attacks |= (1ULL << (r * 8 + tf));
	for (r = tr - 1; r >= 1; r--) attacks |= (1ULL << (r * 8 + tf));
	for (f = tf + 1; f <= 6; f++) attacks |= (1ULL << (tr * 8 + f));
	for (f = tf - 1; f >= 1; f--) attacks |= (1ULL << (tr * 8 + f));

	// return attack map
	return attacks;
}

U64 ChessState::generateOccupancyBoard()
{
	U64 occ = 0ULL;

	for (int i = 0; i < this->c_PIECES_AMOUNT; i++) {
		occ |= this->bitboards[i].getBoard();
	}

	return occ;
}

Bitboard ChessState::setOccupancy(int index, int bitsInMask, Bitboard attackMask)
{
	U64 blockers = 0ULL;
	for (int i = 0; i < bitsInMask; i++) {
		int bitPos = attackMask.popLsb();
		if (index & (1 << i)) {
			blockers |= (1ULL << bitPos);
		}
	}
	return blockers;
}

std::unique_ptr<ChessState> ChessState::makeMove(ChessMove m)
{
	return std::unique_ptr<ChessState>();
}

std::vector<ChessMove> ChessState::generateAllMoves()
{
	std::vector<ChessMove> allMoves = std::vector<ChessMove>();

	for (int piece = 0; piece < this->c_PIECES_AMOUNT; piece++) {
		U64 bitboard = this->bitboards[piece].getBoard();

		// We need to do special king castling rules and pawn movement for the specific side
		if (this->side_ == Color::White) {
			// Generate white pawn moves

			// Generate white king moves + castling

		}
		else {
			// Generate black pawn moves

			// Generate black king moves + castling

		}

		// Generate bishop moves

		// Generate rook moves

		// Generate queen moves

		// Generate knight moves
	}

	return allMoves;
}
