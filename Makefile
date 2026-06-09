CXX = g++
CXXFLAGS = -std=c++17 -Wall -I include

SRCS = src/main.cpp src/Board.cpp src/AI.cpp src/Piece.cpp src/Pawn.cpp src/Rook.cpp src/Bishop.cpp src/Knight.cpp src/Queen.cpp src/King.cpp

TARGET = chess

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)