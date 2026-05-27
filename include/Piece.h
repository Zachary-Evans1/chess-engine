// Chess-Engine/include/Piece.h
// Created by Zachary Evans on 5/21/2026.
// Class for Piece object in Chess-Engine project
// Defines a Piece object for chess

#pragma once

#include <vector>

class Piece {
    public:

    //Setting up attributes of pieces
    enum Color {WHITE, BLACK};
    enum Type { PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING };
    struct Position
    {
        int row;
        int col;

        bool operator==(const Position& other) const {
            return row == other.row && col == other.col;
        }
    };

    //Setting up varibles
    Color color;
    Type type;
    Position pos;
    bool hasMoved = false;

    Piece() : color(WHITE), type(PAWN), pos{0, 0} {} //Default Constructor

    Piece(Color c, Type t, int r, int col); //Constructor

    virtual ~Piece() {};

    //Setters
    void setColor(Color c) {color = c;}
    void setType(Type t) {type = t;}
    void setPosition(Position p) {pos = p;}
    void setHasMoved(bool moved) {hasMoved = moved;}

    //Getters
    Color getColor() const {return color;}
    Type getType() const {return type;}
    Position getPosition() const {return pos;}
    bool getHasMoved() const {return hasMoved;}



    virtual std::vector<Position>getLegalMoves(Piece* board[8][8], bool enPassant, Position enPassantTarget) = 0;
};