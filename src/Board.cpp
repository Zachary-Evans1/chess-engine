#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <cctype>


Board::Board() { //Default constructor
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }
    setupBoard();
}

char Board::getPieceChar(Piece* p)
{
    char c;
        switch (p->getType())
        {
            case Piece::PAWN: c = 'P'; break;
            case Piece::ROOK: c = 'R'; break;
            case Piece::KNIGHT: c = 'N'; break;
            case Piece::BISHOP: c = 'B'; break;
            case Piece::QUEEN: c = 'Q'; break;
            case Piece::KING: c = 'K'; break;
        }
    if(p->getColor() == Piece::BLACK) {
        c = tolower(c);
    }
    return c;
}

void Board::printBoard() {
    for(int r = 7; r >=0; r--) {
        for(int c = 0; c < 8; c++) {
            if(board[r][c] == nullptr) {
                std::cout << " . ";
            }
            else {
                std::cout << " " << getPieceChar(board[r][c]) << " ";
            }
        }
        std::cout << "\n";
    }
}

void Board::movePiece(Piece::Position from, Piece::Position to) {

}

void Board::setupBoard() {
    for(int r = 0; r < 2; r++) {
        for(int c = 0; c < 8; c++) {
            if(r == 0 && c == 0 || r == 0 && c == 7)
            {
                board[r][c] = new Rook(Piece::WHITE, r, c);
            }
            else if(r == 0 && c == 1 || r == 0 && c == 6)
            {
                board[r][c] = new Knight(Piece::WHITE, r, c);
            }
            else if(r == 0 && c == 2 || r == 0 && c == 5)
            {
                board[r][c] = new Bishop(Piece::WHITE, r, c);
            }
            else if(r == 0 && c == 3)
            {
                board[r][c] = new Queen(Piece::WHITE, r, c);
            }
            else if(r == 0 && c == 4)
            {
                board[r][c] = new King(Piece::WHITE, r, c);
            }
            else if(r == 1)
            {
                board[r][c] = new Pawn(Piece::WHITE, r, c);
            }
        }
    }

    for(int r = 6; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            if(r == 7 && c == 0 || r == 7 && c == 7)
            {
                board[r][c] = new Rook(Piece::BLACK, r, c);
            }
            else if(r == 7 && c == 1 || r == 7 && c == 6)
            {
                board[r][c] = new Knight(Piece::BLACK, r, c);
            }
            else if(r == 7 && c == 2 || r == 7 && c == 5)
            {
                board[r][c] = new Bishop(Piece::BLACK, r, c);
            }
            else if(r == 7 && c == 3)
            {
                board[r][c] = new Queen(Piece::BLACK, r, c);
            }
            else if(r == 7 && c == 4)
            {
                board[r][c] = new King(Piece::BLACK, r, c);
            }
            else if(r == 6)
            {
                board[r][c] = new Pawn(Piece::BLACK, r, c);
            }
        }
    }
}