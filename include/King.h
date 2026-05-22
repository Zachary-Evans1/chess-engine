#pragma once
#include "Piece.h"

class King : public Piece {
    public:

    King(Color c, int r, int col) : Piece(c, KING, r, col) {}
    
    std::vector<Position>getLegalMoves(Piece* board[8][8]) override
    {
        return {}; //For later
    }
};