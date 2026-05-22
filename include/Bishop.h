#pragma once
#include "Piece.h"

class Bishop : public Piece {
    public:

    Bishop(Color c, int r, int col) : Piece(c, BISHOP, r, col) {}

    std::vector<Position>getLegalMoves(Piece* board[8][8]) override
    {
        return {}; //For later
    }
};