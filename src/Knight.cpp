#include "Knight.h"

std::vector<Piece::Position> Knight::getLegalMoves(Piece* board[8][8]) {

    int r = pos.row;
    int c = pos.col;
    Piece::Position legal = {0,0};
    std::vector<Piece::Position> legalMoves;
    
    if(r+2 < 8 && c+1 < 8 && (board[r+2][c+1] == nullptr || board[r+2][c+1]->getColor() != color))
    {
        legal = {r+2,c+1};
        legalMoves.push_back(legal);
    }

    if(r+2 < 8 && c-1 >= 0 && (board[r+2][c-1] == nullptr || board[r+2][c-1]->getColor() != color))
    {
        legal = {r+2,c-1};
        legalMoves.push_back(legal);
    }

    if(r-2 >= 0 && c+1 < 8 && (board[r-2][c+1] == nullptr || board[r-2][c+1]->getColor() != color))
    {
        legal = {r-2,c+1};
        legalMoves.push_back(legal);
    }

    if(r-2 >= 0 && c-1 >= 0 && (board[r-2][c-1] == nullptr || board[r-2][c-1]->getColor() != color))
    {
        legal = {r-2,c-1};
        legalMoves.push_back(legal);
    }

    if(r+1 < 8 && c+2 < 8 && (board[r+1][c+2] == nullptr || board[r+1][c+2]->getColor() != color))
    {
        legal = {r+1,c+2};
        legalMoves.push_back(legal);
    }

    if(r+1 < 8 && c-2 >= 0 && (board[r+1][c-2] == nullptr || board[r+1][c-2]->getColor() != color))
    {
        legal = {r+1,c-2};
        legalMoves.push_back(legal);
    }

    if(r-1 >= 0 && c+2 < 8 && (board[r-1][c+2] == nullptr || board[r-1][c+2]->getColor() != color))
    {
        legal = {r-1,c+2};
        legalMoves.push_back(legal);
    }

    if(r-1 >= 0 && c-2 >= 0 && (board[r-1][c-2] == nullptr || board[r-1][c-2]->getColor() != color))
    {
        legal = {r-1,c-2};
        legalMoves.push_back(legal);
    }
    return legalMoves;
}