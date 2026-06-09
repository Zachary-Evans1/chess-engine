#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "AI.h"
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
    enPassantAvailable = false;
    enPassantTarget = {-1, -1}; 
}

std::vector<Board::Move> Board::getLegalMovesForColor(Piece::Color color) {
    std::vector<Move> moves;

    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            Piece* piece = board[r][c];

            if (piece == nullptr || piece->getColor() != color) {
                continue;
            }

            Piece::Position from{r, c};

            std::vector<Piece::Position> destinations =
                piece->getLegalMoves(board, enPassantAvailable, enPassantTarget);

            for (const Piece::Position& to : destinations) {
                if (simulateMove(from, to, color)) {
                    moves.push_back({from, to});
                }
            }
        }
    }

    return moves;
}

Board::MoveRecord Board::makeMove(Move move) {
    MoveRecord record;

    Piece::Position from = move.from;
    Piece::Position to = move.to;

    Piece* movingPiece = board[from.row][from.col];

    record.move = move;
    record.movedPiece = movingPiece;
    record.movedPieceHadMoved = movingPiece->getHasMoved();
    record.previousEnPassantAvailable = enPassantAvailable;
    record.previousEnPassantTarget = enPassantTarget;
    record.previousGameOver = gameOver;

    bool destinationWasEmpty = board[to.row][to.col] == nullptr;

    record.capturedPiece = board[to.row][to.col];
    record.capturedPiecePosition = to;

    board[to.row][to.col] = movingPiece;
    board[from.row][from.col] = nullptr;

    movingPiece->setPosition(to);
    movingPiece->setHasMoved(true);

    if (movingPiece->getType() == Piece::KING) {
        if (to.col - from.col == 2) {
            record.wasCastle = true;
            record.rookFrom = {to.row, 7};
            record.rookTo = {to.row, 5};

            Piece* rook = board[to.row][7];
            record.rookHadMoved = rook->getHasMoved();

            board[to.row][5] = rook;
            board[to.row][7] = nullptr;

            if (board[to.row][5] != nullptr) {
                board[to.row][5]->setPosition({to.row, 5});
                board[to.row][5]->setHasMoved(true);
            }
        } else if (from.col - to.col == 2) {
            record.wasCastle = true;
            record.rookFrom = {to.row, 0};
            record.rookTo = {to.row, 3};

            Piece* rook = board[to.row][0];
            record.rookHadMoved = rook->getHasMoved();

            board[to.row][3] = rook;
            board[to.row][0] = nullptr;

            if (board[to.row][3] != nullptr) {
                board[to.row][3]->setPosition({to.row, 3});
                board[to.row][3]->setHasMoved(true);
            }
        }
    }

    if (movingPiece->getType() == Piece::PAWN &&
        abs(to.col - from.col) == 1 &&
        destinationWasEmpty) {
        record.wasEnPassant = true;
        record.capturedPiece = board[from.row][to.col];
        record.capturedPiecePosition = {from.row, to.col};

        board[from.row][to.col] = nullptr;
    }

    if (movingPiece->getType() == Piece::PAWN &&
        (to.row == 0 || to.row == 7)) {
        record.wasPromotion = true;
        record.originalPawn = movingPiece;

        Piece::Color color = movingPiece->getColor();

        board[to.row][to.col] = new Queen(color, to.row, to.col);
        record.promotedPiece = board[to.row][to.col];
    }

    if (movingPiece->getType() == Piece::PAWN &&
        abs(to.row - from.row) == 2) {
        enPassantAvailable = true;
        enPassantTarget = {(from.row + to.row) / 2, to.col};
    } else {
        enPassantAvailable = false;
        enPassantTarget = {-1, -1};
    }

    return record;
}

void Board::undoMove(const MoveRecord& record)
{
    Piece::Position from = record.move.from;
    Piece::Position to = record.move.to;

    if (record.wasPromotion) {
        delete record.promotedPiece;

        board[from.row][from.col] = record.originalPawn;
        board[to.row][to.col] = nullptr;

        record.originalPawn->setPosition(from);
        record.originalPawn->setHasMoved(record.movedPieceHadMoved);
    } else {
        board[from.row][from.col] = record.movedPiece;
        board[to.row][to.col] = nullptr;

        record.movedPiece->setPosition(from);
        record.movedPiece->setHasMoved(record.movedPieceHadMoved);
    }

    if (record.wasEnPassant) {
        board[record.capturedPiecePosition.row][record.capturedPiecePosition.col] =
            record.capturedPiece;
    } else {
        board[to.row][to.col] = record.capturedPiece;
    }

    if (record.capturedPiece != nullptr) {
        record.capturedPiece->setPosition(record.capturedPiecePosition);
    }

    if (record.wasCastle) {
        Piece* rook = board[record.rookTo.row][record.rookTo.col];

        board[record.rookFrom.row][record.rookFrom.col] = rook;
        board[record.rookTo.row][record.rookTo.col] = nullptr;

        if (rook != nullptr) {
            rook->setPosition(record.rookFrom);
            rook->setHasMoved(record.rookHadMoved);
        }
    }

    enPassantAvailable = record.previousEnPassantAvailable;
    enPassantTarget = record.previousEnPassantTarget;
    gameOver = record.previousGameOver;
}

int Board::evaluate(Piece::Color color) {
    int score = 0;

    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            Piece* piece = board[r][c];
            if (piece == nullptr) continue;

            int value = 0;

            switch (piece->getType()) {
            case Piece::PAWN: value = 100; break;
            case Piece::KNIGHT: value = 320; break;
            case Piece::BISHOP: value = 330; break;
            case Piece::ROOK: value = 500; break;
            case Piece::QUEEN: value = 900; break;
            case Piece::KING: value = 20000; break;
            }

            if (piece->getColor() == color) {
                score += value;
            } else {
                score -= value;
            }
        }
    }

    return score;
}

Piece* Board::getPieceAt(Piece::Position position) const {
    if (position.row < 0 || position.row > 7 ||
        position.col < 0 || position.col > 7) {
        return nullptr;
    }

    return board[position.row][position.col];
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
    std::cout << "   a  b  c  d  e  f  g  h" << std::endl; //column lables
    for(int r = 7; r >=0; r--) {
        std::cout << r+1 << " "; //row labels
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
    if(s.length() != 2) return {-1, -1};
    int col = tolower(s[0]) - 'a';
    int row = tolower(s[1]) - '1';
    Piece::Position pos{row, col};
    return pos;
}

bool Board::simulateMove(Piece::Position from, Piece::Position to, Piece::Color color) {
    // 1. save the pieces at both squares
    Piece* fromPiece = board[from.row][from.col];
    Piece* toPiece = board[to.row][to.col];

    // 2. temporarily make the move (don't delete anything yet)
    board[to.row][to.col] = board[from.row][from.col];
    board[from.row][from.col] = nullptr;

    // 3. test if our king is in check
    bool inCheck = isInCheck(color);

    // 4. restore the board
    board[from.row][from.col] = fromPiece;
    board[to.row][to.col] = toPiece;

    // 5. return true if the move is safe (not in check)
    return !inCheck;
}


bool Board::isValidMove(Piece::Position from, Piece::Position to, Piece::Color turn) {
    if(from.row < 0 || from.row > 7 || from.col < 0 || from.col > 7) return false;
    if(to.row < 0 || to.row > 7 || to.col < 0 || to.col > 7) return false;

    if (board[from.row][from.col] == nullptr) {
        return false;
    }

    if (board[from.row][from.col]->getColor() != turn) {
        return false;
    }

    std::vector<Piece::Position> validMoves = board[from.row][from.col]->getLegalMoves(board, enPassantAvailable, enPassantTarget);
    
    //std::cout << std::endl;
    
    for(const Piece::Position& p : validMoves)
    {
        if(p == to) return simulateMove(from, to, turn);
    }

    return false;
}

void Board::movePiece(Piece::Position from, Piece::Position to) {

    bool wasEmpty = (board[to.row][to.col] == nullptr);

    if(board[to.row][to.col] != nullptr) {

        if(board[to.row][to.col]->getType() == Piece::KING) {
            Piece::Color winner = board[from.row][from.col]->getColor();
            std::cout << (winner == Piece::WHITE ? "White" : "Black") << " has won the game!" << std::endl;
            gameOver = true;
        }

         delete board[to.row][to.col];
    }

    board[to.row][to.col] = board[from.row][from.col];

    board[from.row][from.col] = nullptr;

    board[to.row][to.col]->setPosition(to);

    if(board[to.row][to.col]->getType() == Piece::KING)
    {
        // kingside
        if(to.col - from.col == 2)
        {
            // move rook from h file to f file
            board[to.row][5] = board[to.row][7];
            board[to.row][7] = nullptr;
            board[to.row][5]->setPosition({to.row, 5});
        }
        // queenside
        else if(from.col - to.col == 2)
        {
            // move rook from a file to d file
            board[to.row][3] = board[to.row][0];
            board[to.row][0] = nullptr;
            board[to.row][3]->setPosition({to.row, 3});
        }
    }

    if(board[to.row][to.col]->getType() == Piece::PAWN &&
    abs(to.col - from.col) == 1 &&
    to.row != from.row && wasEmpty)
    {
        // pawn moved diagonally but destination was empty - en passant
        // captured pawn is on same row as 'from', same col as 'to'
        if(board[from.row][to.col] != nullptr)
        {
            delete board[from.row][to.col];
            board[from.row][to.col] = nullptr;
        }
    }

    board[to.row][to.col]->setHasMoved(true);
}

void Board::checkPromotion(Piece::Color color, Piece::Position pawn)
{
    bool vaild = false;
    char choice;
    if(pawn.row == 7 || pawn.row == 0)
    {
        vaild = true;
        delete board[pawn.row][pawn.col];
        board[pawn.row][pawn.col] = nullptr;
    }
    while(vaild)
    {
        std::cout << "What piece would you like to promote your pawn to? Please enter the letter." << std::endl;
        std::cin >> choice;
        choice = tolower(choice);
        switch(choice)
        {
            case 'b':
            board[pawn.row][pawn.col] = new Bishop(color, pawn.row, pawn.col);
            vaild = false;
            break;
            case 'n':
            board[pawn.row][pawn.col] = new Knight(color, pawn.row, pawn.col);
            vaild = false;
            break;
            case 'q':
            board[pawn.row][pawn.col] = new Queen(color, pawn.row, pawn.col);
            vaild = false;
            break;
            case 'r':
            board[pawn.row][pawn.col] = new Rook(color, pawn.row, pawn.col);
            vaild = false;
            break;
            default:
            std::cout << "That is an invalid choice for promotion" << std::endl;
        }
    }
}

void Board::play() {

    Piece::Color turn = Piece::WHITE; 

    while(!gameOver)
    {

        printBoard();

        std::cout << (turn == Piece::WHITE ? "White" : "Black") << "'s turn." << std::endl;

        if (turn == Piece::BLACK) {
            Board::Move aiMove = AI::chooseMove(*this, Piece::BLACK);

            std::cout << "Black moves from "
                << char('a' + aiMove.from.col) << aiMove.from.row + 1
                << " to "
                << char('a' + aiMove.to.col) << aiMove.to.row + 1
                << std::endl;

            makeMove(aiMove);

            Piece::Color opponent = Piece::WHITE;

            if (isInCheckmate(opponent)) {
                printBoard();
                std::cout << "Black wins by checkmate!" << std::endl;
                break;
            } else if (isInCheck(opponent)) {
                std::cout << "White is in check!" << std::endl;
            }

            turn = Piece::WHITE;
            continue;
        }

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
            makeMove({from, to});

            if(gameOver) break;

            Piece::Color opponent = (turn == Piece::WHITE) ? Piece::BLACK : Piece::WHITE;
            
            if(isInCheckmate(opponent))
            {
                printBoard();
                std::cout << (turn == Piece::WHITE ? "White" : "Black") << " wins by checkmate!" << std::endl;
                break;
            }
            
            else if(isInCheck(opponent))
            {
                std::cout << (opponent == Piece::WHITE ? "White" : "Black") << " is in check!" << std::endl;
            }



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

Piece::Position Board::findKing(Piece::Color color) {
    for(int r = 7; r >=0; r--) {
        for(int c = 0; c < 8; c++) {
            if(board[r][c] != nullptr && board[r][c]->getType() == Piece::KING && board[r][c]->getColor() == color)
            {
                return {r,c};
            }
        }    
    }
    return {-1, -1}; //King not found (shouldn't happen)
}

bool Board::isInCheck(Piece::Color color) {
    Piece::Position kingPos = findKing(color);
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            if(board[r][c] != nullptr && board[r][c]->getColor() != color)
            {
                std::vector<Piece::Position> legalMoves = board[r][c]->getLegalMoves(board, enPassantAvailable, enPassantTarget);
                for(const Piece::Position& p : legalMoves)
                {
                    if(p == kingPos) return true;
                }
            }
        }    
    }
    return false;
}

bool Board::isInCheckmate(Piece::Color color)
{
    if(!isInCheck(color))
    {
        return false;
    }
    for(int r = 0; r < 8; r++) {
        for(int c = 0; c < 8; c++) {
            if(board[r][c] != nullptr && board[r][c]->getColor() == color)
            {
                std::vector<Piece::Position> legalMoves = board[r][c]->getLegalMoves(board, enPassantAvailable, enPassantTarget);
                for(const Piece::Position& p : legalMoves)
                {
                    if(simulateMove({r,c}, p, color))
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

void Board::setupBackRank(int row, Piece::Color color) {
    board[row][0] = new Rook(color, row, 0);
    board[row][1] = new Knight(color, row, 1);
    board[row][2] = new Bishop(color, row, 2);
    board[row][3] = new Queen(color, row, 3);
    board[row][4] = new King(color, row, 4);
    board[row][5] = new Bishop(color, row, 5);
    board[row][6] = new Knight(color, row, 6);
    board[row][7] = new Rook(color, row, 7);
}

void Board::setupBoard() {
    setupBackRank(0, Piece::WHITE);
    setupBackRank(7, Piece::BLACK);

    for(int c = 0; c < 8; c++) {
        board[1][c] = new Pawn(Piece::WHITE, 1, c);
        board[6][c] = new Pawn(Piece::BLACK, 6, c);
    }
}