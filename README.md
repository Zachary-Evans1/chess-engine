# chess-engine

# Description
A chess engine in C++ with a playable two player mode

# How to compile and run
You can compile using the command: g++ -std=c++17 src/main.cpp src/Board.cpp src/AI.cpp src/Piece.cpp src/Pawn.cpp src/Rook.cpp src/Bishop.cpp src/Knight.cpp src/Queen.cpp src/King.cpp -I include -o chess

And then run it with: ./chess

# How to play
You play by first entering the position of the piece you want to move, and then entering the position you'd like that piece to move to.


Example:
   a  b  c  d  e  f  g  h
8  r  n  b  q  k  b  n  r 
7  p  p  p  p  p  p  p  p 
6  .  .  .  .  .  .  .  . 
5  .  .  .  .  .  .  .  . 
4  .  .  .  .  .  .  .  . 
3  .  .  .  .  .  .  .  . 
2  P  P  P  P  P  P  P  P 
1  R  N  B  Q  K  B  N  R 

For example, if white wanted to move the pawn on e2 to the e4 space they would enter the following

Enter in chess notation the position of the piece you'd like to move: e2 then press enter.

Enter in chess notation the position youd like to move your piece: e4 then press enter again.

the board would then look like this:

   a  b  c  d  e  f  g  h
8  r  n  b  q  k  b  n  r 
7  p  p  p  p  p  p  p  p 
6  .  .  .  .  .  .  .  . 
5  .  .  .  .  .  .  .  . 
4  .  .  .  .  P  .  .  . 
3  .  .  .  .  .  .  .  . 
2  P  P  P  P  .  P  P  P 
1  R  N  B  Q  K  B  N  R 

And it would then go to blacks (the AI's) turn, if you want to quit the game at any time you simply enter 'q' instead of a space.

You are playing against an AI opponent, it's not the smartest right now but it can think ahead a single turn.

Piece Legend
Uppercase = White, Lowercase = Black
P/p = Pawn, R/r = Rook, N/n = Knight
B/b = Bishop, Q/q = Queen, K/k = King

# Project Structure

Piece
This class is the base class all the other piece classes are built off of, it sets up color, type and position variable and a constructor and destructor, it also has a virtual function for getting legal moves.

Bishop, King, Knight, Pawn, Queen, and Rook
These are all the specific pieces, each has their own constructor and a function for getting legal moves.

Board
This class holds the board which is an array of Piece pointers, it can print the board, parse player input, check for valid moves, move a piece and allow you to play chess.

AI
This class holds rules for the AI opponent, It assigns values to pieces and moves and then simulates its move and your move to find the best move possible, it is currently not complete

# Roadmap
* Add promotion choice for Human (currently auto promotes to queen only).
* Add back choice for human opponent.
* Add alpha-beta pruning to AI.