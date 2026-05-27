#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"

std::vector<Piece::Position> Queen::getLegalMoves(Piece* board[8][8], bool enPassant, Position enPassantTarget) {

    Rook tempRook(color, pos.row, pos.col);
    Bishop tempBishop(color, pos.row, pos.col);

    std::vector<Piece::Position> legalMoves = tempRook.getLegalMoves(board, false, {-1,-1});
    std::vector<Piece::Position> bishopMoves = tempBishop.getLegalMoves(board, false, {-1,-1});

    legalMoves.insert(legalMoves.end(), bishopMoves.begin(), bishopMoves.end());

    return legalMoves;
}