#include "Board.h"
#include "Piece.h"


Board::Board() { //Default constructor
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
}

void Board::movePiece(Piece::Position from, Piece::Position to) {

}

void Board::setupBoard() {
    for(int r = 0; r < 2; r++) {
        for(int c = 0; c < 8; c++) {
            if(r == 0 && c == 1 || r == 0 && c == 7)
            {
                board[r][c] = new Rook(Piece::WHITE, Piece::ROOK, r, c);
            }
        }
    }
}