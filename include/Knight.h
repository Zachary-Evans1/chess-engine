#pragma once
#include "Piece.h"

class Knight : public Piece {
    public:
    
    Knight(Color c, int r, int col) : Piece(c, KNIGHT, r, col) {}

    std::vector<Position>getLegalMoves(Piece* board[8][8]) override
    {
        return {}; //For later
    }
};