#include "Pawn.h"

std::vector<Piece::Position> Pawn::getLegalMoves(Piece* board[8][8]) {

    int r = pos.row;
    int c = pos.col;
    Piece::Color team = color;
    std::vector<Piece::Position> legalMoves;

    if(team == WHITE)
    {
        //Move to empty
        if(r+1 < 8 && board[r+1][c] == nullptr)
        {
            legalMoves.push_back({r+1,c});

            if(r == 1 && board[r+2][c] == nullptr)
            {
                legalMoves.push_back({r+2,c});
            }
        }

        //Capture
        if(r+1 < 8 && c+1 < 8 && board[r+1][c+1] != nullptr && board[r+1][c+1]->getColor() != color)
        {
            legalMoves.push_back({r+1,c+1});
        }

        if(r+1 < 8 && c-1 >= 0 && board[r+1][c-1] != nullptr && board[r+1][c-1]->getColor() != color)
        {
            legalMoves.push_back({r+1,c-1});
        }
    }
    else
    {
        //Move to empty
        if(r-1 >= 0 && board[r-1][c] == nullptr)
        {
            legalMoves.push_back({r-1,c});

            if(r == 6 && board[r-2][c] == nullptr)
            {
                legalMoves.push_back({r-2,c});
            }
        }

        //Capture
        if(r-1 >= 0 && c+1 < 8 && board[r-1][c+1] != nullptr && board[r-1][c+1]->getColor() != color)
        {
            legalMoves.push_back({r-1,c+1});
        }

        if(r-1 >= 0 && c-1 >= 0 && board[r-1][c-1] != nullptr && board[r-1][c-1]->getColor() != color)
        {
            legalMoves.push_back({r-1,c-1});
        }
    }
    return legalMoves;
}