// Chess-Engine/include/Board.h
// Created by Zachary Evans on 5/21/2026.
// Class for Board object in Chess-Engine project
// Defines a Board object for chess

#pragma once
#include "Piece.h"
#include <string>
#include <vector>

class Board {
    private:

    Piece* board[8][8]; //Sets up 8x8 chessboard

    bool gameOver = false;

    Piece::Position enPassantTarget;

    bool enPassantAvailable;

    char getPieceChar(Piece* p);

    Piece::Position findKing(Piece::Color color);

    bool isInCheck(Piece::Color color);
    
    bool simulateMove(Piece::Position from, Piece::Position to, Piece::Color color);

    void printBoard();

    void movePiece(Piece::Position from, Piece::Position to);

    Piece::Position parseInput(std::string s);

    bool isValidMove(Piece::Position from, Piece::Position to, Piece::Color turn);

    void setupBoard();

    bool isInCheckmate(Piece::Color color);

    void checkPromotion(Piece::Color color, Piece::Position pawn);

    

    public:

    struct Move {
        Piece::Position from;
        Piece::Position to;
        Piece::Type promotion = Piece::QUEEN;
    };

    struct MoveRecord {
        Move move;

        Piece* movedPiece = nullptr;
        Piece* capturedPiece = nullptr;
        Piece::Position capturedPiecePosition{-1, -1};

        bool movedPieceHadMoved = false;

        bool previousEnPassantAvailable = false;
        Piece::Position previousEnPassantTarget{-1, -1};

        bool wasCastle = false;
        Piece::Position rookFrom{-1, -1};
        Piece::Position rookTo{-1, -1};
        bool rookHadMoved = false;

        bool wasPromotion = false;
        Piece* promotedPiece = nullptr;
        Piece* originalPawn = nullptr;

        bool wasEnPassant = false;

        bool previousGameOver = false;
    };

    std::vector<Move> getLegalMovesForColor(Piece::Color color);
    
    MoveRecord makeMove(Move move);

    void undoMove(const MoveRecord& record);

    int evaluate(Piece::Color color);

    Piece* getPieceAt(Piece::Position postion) const;

    Board();

    void play();
};