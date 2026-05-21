#pragma once
#include "Piece.h"

class Queen : public Piece {
    public:
    Queen(Color c, int r, int col) : Piece(c, QUEEN, r, col) {}

    std::vector<Position>getLegalMoves() override
    {
        return {}; //For later
    }
};