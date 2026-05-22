#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <cctype>
#include <algorithm>


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

Piece::Position Board::parseInput(std::string s) {
    int col = s[0] - 'a';
    int row = s[1] - '1';
    Piece::Position pos{row, col};
    return pos;
}


bool Board::isValidMove(Piece::Position from, Piece::Position to, Piece::Color turn) {
    
    if (board[from.row][from.col] == nullptr) {
        return false;
    }

    if (board[from.row][from.col]->getColor() != turn) {
        return false;
    }

    std::vector<Piece::Position> validMoves = board[from.row][from.col]->getLegalMoves(board);
    
    std::cout << std::endl;
    
    for(const Piece::Position& p : validMoves)
    {
        if(p == to) return true;
    }

    return false;
}

void Board::movePiece(Piece::Position from, Piece::Position to) {

    if(board[to.row][to.col] != nullptr) {
        delete board[to.row][to.col];
    }

    board[to.row][to.col] = board[from.row][from.col];

    board[from.row][from.col] = nullptr;

    board[to.row][to.col]->setPosition(to);
}

void Board::play() {

    Piece::Color turn = Piece::WHITE; 

    while(true)
    {

        printBoard();

        std::cout << (turn == Piece::WHITE ? "White" : "Black") << "'s turn." << std::endl;

        std::string f;

        std::string t;
        
        std::cout << "Enter 'q' to quit." << std::endl;

        std::cout << "Enter in chess notiation the postion of the piece you'd like to move: ";
        std::cin >> f;

        if(f == "quit" || f == "q") break;

        std::cout << "\n Enter in chess notation the postion youd like to move your piece: ";
        std::cin >> t;

        if(t == "quit" || t == "q") break;

        Piece::Position to = parseInput(t);
        Piece::Position from = parseInput(f);



        bool valid = isValidMove(from, to, turn);

        if(valid)
        {
            movePiece(from, to);

            if(turn == Piece::WHITE)
            {
                turn = Piece::BLACK;
            }
            else if(turn == Piece::BLACK)
            {
                turn = Piece::WHITE;
            }
        }

        else
        {
            std::cout << "That is not a valid move!, Try again." << std::endl;
        }
    }
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