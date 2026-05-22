#pragma once
#include "Piece.h"

class Rook : public Piece {
    public:
    
    Rook(Color c, int r, int col) : Piece(c, ROOK, r, col) {}

    std::vector<Position>getLegalMoves(Piece* board[8][8]) override
    {
        
    }
};