#pragma once
#include "Piece.h"

class Knight : public Piece {
    public:
    
    Knight(Color c, int r, int col) : Piece(c, KNIGHT, r, col) {}

    std::vector<Position>getLegalMoves() override
    {
        return {}; //For later
    }
};