// Chess-Engine/include/Board.h
// Created by Zachary Evans on 5/21/2026.
// Class for Board object in Chess-Engine project
// Defines a Board object for chess

#pragma once
#include "Piece.h"

class Board {
    private:

    Piece* board[8][8]; //Sets up 8x8 chessboard

    public:

    Board();

    void printBoard();

    void movePiece(Piece::Position from, Piece::Position to);

    void setupBoard();

};