#pragma once
#include "Piece.h"

class Pawn : public Piece {
    public:
    
    Pawn(Color c, int r, int col) : Piece(c, PAWN, r, col) {}

    std::vector<Position>getLegalMoves(Piece* board[8][8]) override;
};