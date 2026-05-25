// Chess-Engine/include/Board.h
// Created by Zachary Evans on 5/21/2026.
// Class for Board object in Chess-Engine project
// Defines a Board object for chess

#pragma once
#include "Piece.h"
#include <string>

class Board {
    private:

    Piece* board[8][8]; //Sets up 8x8 chessboard

    char getPieceChar(Piece* p);

    Piece::Position findKing(Piece::Color color);

    bool isInCheck(Piece::Color color);

    bool gameOver = false;
    
    bool simulateMove(Piece::Position from, Piece::Position to, Piece::Color color);

    
    void printBoard();

    void movePiece(Piece::Position from, Piece::Position to);

    Piece::Position parseInput(std::string s);

    bool isValidMove(Piece::Position from, Piece::Position to, Piece::Color turn);

    void setupBoard();

    bool isInCheckmate(Piece::Color color);

    void checkPromotion(Piece::Color color, Piece::Position pawn);

    public:

    Board();

    void play();
};