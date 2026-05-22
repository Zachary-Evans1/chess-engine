// Chess-Engine/include/Piece.cpp
// Created by Zachary Evans on 5/21/2026.
// Class for Piece object in Chess-Engine project
// Defines a Piece object for chess

#include "Piece.h"

Piece::Piece(Color c, Type t, int r, int col) : color(c), type(t), pos{r, col} {}