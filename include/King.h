#pragma once
#include "Piece.h"

class King : public Piece {
    public:

    King(Color c, int r, int col) : Piece(c, KING, r, col) {}
    
    std::vector<Position>getLegalMoves() override
    {
        return {}; //For later
    }
};