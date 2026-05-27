#include "Bishop.h"

std::vector<Piece::Position> Bishop::getLegalMoves(Piece* board[8][8], bool enPassant, Position enPassantTarget) {

    int r = pos.row;
    int c = pos.col;
    Piece::Position legal = {0,0};
    std::vector<Piece::Position> legalMoves;

    //Up-right
    int nr = r + 1;
    int nc = c + 1;
    while (nr < 8 && nc < 8) {

        if(board[nr][nc] == nullptr) //Legal move to empty space
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
        }

        else if (board[nr][nc]->getColor() != color) //Legal move to enemy
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
            break;
        }

        else //Illegal move
        {
            break;
        }

        nr++;
        nc++;
    }

    //Up-Left
    nr = r + 1;
    nc = c - 1;
    while (nr < 8 && nc >= 0) {

        if(board[nr][nc] == nullptr) //Legal move to empty space
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
        }

        else if (board[nr][nc]->getColor() != color) //Legal move to enemy
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
            break;
        }

        else //Illegal move
        {
            break;
        }

        nr++;
        nc--;
    }

    //Down-Right
    nr = r - 1;
    nc = c + 1;
    while (nr >= 0 && nc < 8) {

        if(board[nr][nc] == nullptr) //Legal move to empty space
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
        }

        else if (board[nr][nc]->getColor() != color) //Legal move to enemy
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
            break;
        }

        else //Illegal move
        {
            break;
        }

        nr--;
        nc++;
    }

    //Down-Left
    nr = r - 1;
    nc = c - 1;
    while (nr >= 0 && nc >= 0) {

        if(board[nr][nc] == nullptr) //Legal move to empty space
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
        }

        else if (board[nr][nc]->getColor() != color) //Legal move to enemy
        {
            legal = {nr,nc};
            legalMoves.push_back(legal);
            break;
        }

        else //Illegal move
        {
            break;
        }

        nr--;
        nc--;
    }
    return legalMoves;
}