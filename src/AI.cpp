#include "AI.h"
#include <cstdlib>
#include <ctime>

int AI::getPieceValue(Piece::Type type) {
    switch (type) {
        case Piece::PAWN: return 100;
        case Piece::KNIGHT: return 320;
        case Piece::BISHOP: return 330;
        case Piece::ROOK: return 500;
        case Piece::QUEEN: return 900;
        case Piece::KING: return 20000; 
    }
    return 0;
}

int AI::scoreMove(Board& board, Board::Move move) {
    int score = 0;

    Piece* captured = board.getPieceAt(move.to);
    if (captured != nullptr) {
        score += getPieceValue(captured->getType());
    }

    Piece* moving = board.getPieceAt(move.from);
    if (moving != nullptr && moving->getType() == Piece::PAWN) {
        if (move.to.row == 0 || move.to.row == 7) {
            score += getPieceValue(Piece::QUEEN);
        }
    }

    return score;
}

Board::Move AI::chooseMove(Board& board, Piece::Color color) {
    std::vector<Board::Move> moves = board.getLegalMovesForColor(color);

    Board::Move bestMove = moves[0];
    int bestScore = -1000000;

    Piece::Color opponent = color == Piece::WHITE ? Piece::BLACK : Piece::WHITE;

    for (const Board::Move& move : moves) {
        Board::MoveRecord record = board.makeMove(move);
        int score = minimax(board, 2, color, opponent);
        board.undoMove(record);

        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }
    }

    return bestMove;
}

int AI::minimax(Board& board, int depth, Piece::Color aiColor, Piece::Color turn) {
    if (depth == 0) {
        return board.evaluate(aiColor);
    }

    std::vector<Board::Move> moves = board.getLegalMovesForColor(turn);

    if (moves.empty()) {
        return board.evaluate(aiColor);
    }

    Piece::Color nextTurn = turn == Piece::WHITE ? Piece::BLACK : Piece::WHITE;

    if (turn == aiColor) {
        int bestScore = -1000000;

        for (const Board::Move& move : moves) {
            Board::MoveRecord record = board.makeMove(move);
            int score = minimax(board, depth - 1, aiColor, nextTurn);
            board.undoMove(record);

            bestScore = std::max(bestScore, score);
        }

        return bestScore;
    } else {
        int bestScore = 1000000;

        for (const Board::Move& move : moves) {
            Board::MoveRecord record = board.makeMove(move);
            int score = minimax(board, depth - 1, aiColor, nextTurn);
            board.undoMove(record);

            bestScore = std::min(bestScore, score);
        }

        return bestScore;
    }
}