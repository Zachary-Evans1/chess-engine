#pragma once
#include "Piece.h"

class Queen : public Piece {
    public:
    Queen(Color c, int r, int col) : Piece(c, QUEEN, r, col) {}

    std::vector<Position>getLegalMoves(Piece* board[8][8]) override
    {
        return {}; //For later
    }
};