#pragma once

#include "Board.h"

class AI {
public:
    static Board::Move chooseMove(Board& board, Piece::Color color);
    
private:
    static int getPieceValue(Piece::Type type);
    static int scoreMove(Board& board, Board::Move move);
    static int minimax(Board& board, int depth, Piece::Color aiColor, Piece::Color turn);

};