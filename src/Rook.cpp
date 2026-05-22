#include "Rook.h"

std::vector<Piece::Position> Rook::getLegalMoves(Piece* board[8][8])
{
    int r = pos.row;
    int c = pos.col;
    Piece::Position legal = {0,0};
    std::vector<Piece::Position> legalMoves;

    for (int i = c+1; i < 8; i++) //Move Right
    {
        if (board[r][i] == nullptr) { //Legal move to empty space
            legal = {r,i};
            legalMoves.push_back(legal);
        }
        else if (board[r][i]->getColor() != color)  {//Legal move to enemy
            legal = {r,i};
            legalMoves.push_back(legal);
            break; //Break loop when hitting other pieces
        }
        else {
            break; //Friendly piece
        }
    }

    for (int i = c-1; i >= 0; i--) //Move Left
    {
        if (board[r][i] == nullptr) { //Legal move to empty space
            legal = {r,i};
            legalMoves.push_back(legal);
        }
        else if (board[r][i]->getColor() != color)  {//Legal move to enemy
            legal = {r,i};
            legalMoves.push_back(legal);
            break; //Break loop when hitting other pieces
        }
        else {
            break; //Friendly piece
        }
    }

    for (int i = r+1; i < 8; i++) //Move Up
    {
        if (board[i][c] == nullptr) { //Legal move to empty space
            legal = {i,c};
            legalMoves.push_back(legal);
        }
        else if (board[i][c]->getColor() != color)  {//Legal move to enemy
            legal = {i,c};
            legalMoves.push_back(legal);
            break; //Break loop when hitting other pieces
        }
        else {
            break; //Friendly piece
        }
    }

    for (int i = r-1; i >= 0; i--) //Move Down
    {
        if (board[i][c] == nullptr) { //Legal move to empty space
            legal = {i,c};
            legalMoves.push_back(legal);
        }
        else if (board[i][c]->getColor() != color)  {//Legal move to enemy
            legal = {i,c};
            legalMoves.push_back(legal);
            break; //Break loop when hitting other pieces
        }
        else {
            break; //Friendly piece
        }
    }
    return legalMoves;
}