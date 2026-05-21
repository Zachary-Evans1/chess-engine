#pragma once
#include "Piece.h"

class Bishop : public Piece {
    public:

    Bishop(Color c, int r, int col) : Piece(c, BISHOP, r, col) {}

    std::vector<Position>getLegalMoves() override
    {
        return {}; //For later
    }
};