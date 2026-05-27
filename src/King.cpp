#include "King.h"

std::vector<Piece::Position> King::getLegalMoves(Piece* board[8][8], bool enPassant, Position enPassantTarget) {

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
    if(color == Piece::WHITE) //Castle for white
    {
        //Kingside
        if(hasMoved == false &&
            board[0][7] != nullptr &&
            board[0][7]->getType() == Piece::ROOK &&
            !board[0][7]->getHasMoved() &&
            board[0][5] == nullptr
            && board[0][6] == nullptr)
        {
            legal = {0,6};
            legalMoves.push_back(legal);
        }
        //Queenside
        if(hasMoved == false &&
            board[0][0] != nullptr &&
            board[0][0]->getType() == Piece::ROOK &&
            !board[0][0]->getHasMoved() &&
            board[0][1] == nullptr &&
            board[0][2] == nullptr &&
            board[0][3] == nullptr)
        {
            legal = {0,2};
            legalMoves.push_back(legal);
        }
    }
    if(color == Piece::BLACK) //Castle for Black
    {
        //Kingside
        if(hasMoved == false &&
            board[7][7] != nullptr &&
            board[7][7]->getType() == Piece::ROOK &&
            !board[7][7]->getHasMoved() &&
            board[7][5] == nullptr
            && board[7][6] == nullptr)
        {
            legal = {7,6};
            legalMoves.push_back(legal);
        }
        //Queenside
        if(hasMoved == false &&
            board[7][0] != nullptr &&
            board[7][0]->getType() == Piece::ROOK &&
            !board[7][0]->getHasMoved() &&
            board[7][1] == nullptr &&
            board[7][2] == nullptr &&
            board[7][3] == nullptr)
        {
            legal = {7,2};
            legalMoves.push_back(legal);
        }
    }

    return legalMoves;
}