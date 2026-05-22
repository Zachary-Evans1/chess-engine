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
    };

    //Setting up varibles
    Color color;
    Type type;
    Position pos;

    Piece() : color(WHITE), type(PAWN), pos{0, 0} {} //Default Constructor

    Piece(Color c, Type t, int r, int col); //Constructor

    virtual ~Piece() {};

    //Setters
    void setColor(Color c) {color = c;}
    void setType(Type t) {type = t;}
    void setPosition(Position p) {pos = p;}

    //Getters
    Color getColor() const {return color;}
    Type getType() const {return type;}
    Position getPosition() const {return pos;}



    virtual std::vector<Position>getLegalMoves(Piece* board[8][8]) = 0;
};