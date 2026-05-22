#include "King.h"

std::vector<Piece::Position> King::getLegalMoves(Piece* board[8][8]) {

    int r = pos.row;
    int c = pos.col;
    Piece::Position legal = {0,0};
    std::vector<Piece::Position> legalMoves;

    if (r+1 < 8 && c+1 < 8 && (board[r+1][c+1] == nullptr || board[r+1][c+1]->getColor() != color))
    {
        //Up-Right
        legal = {r+1,c+1};
        legalMoves.push_back(legal);
    }

    if (r+1 < 8 && c-1 >= 0 && (board[r+1][c-1] == nullptr || board[r+1][c-1]->getColor() != color))
    {
        //Up-Left
        legal = {r+1,c-1};
        legalMoves.push_back(legal);
    }

    if (r-1 >= 0 && c+1 < 8 && (board[r-1][c+1] == nullptr || board[r-1][c+1]->getColor() != color))
    {
        //Down-Right
        legal = {r-1,c+1};
        legalMoves.push_back(legal);
    }

    if (r-1 >= 0 && c-1 >= 0 && (board[r-1][c-1] == nullptr || board[r-1][c-1]->getColor() != color))
    {
        //Down-Left
        legal = {r-1,c-1};
        legalMoves.push_back(legal);
    }

    if (r+1 < 8 && (board[r+1][c] == nullptr || board[r+1][c]->getColor() != color))
    {
        //Up
        legal = {r+1,c};
        legalMoves.push_back(legal);
    }

     if (r-1 >= 0 && (board[r-1][c] == nullptr || board[r-1][c]->getColor() != color))
    {
        //Down
        legal = {r-1,c};
        legalMoves.push_back(legal);
    }

     if (c+1 < 8 && (board[r][c+1] == nullptr || board[r][c+1]->getColor() != color))
    {
        //Right
        legal = {r,c+1};
        legalMoves.push_back(legal);
    }

     if (c-1 >= 0 && (board[r][c-1] == nullptr || board[r][c-1]->getColor() != color))
    {
        //Left
        legal = {r,c-1};
        legalMoves.push_back(legal);
    }

    return legalMoves;
}