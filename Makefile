CXX = g++
CXXFLAGS = -std=c++17 -Wall -I include

SRCS := $(wildcard src/*.cpp)

TARGET = chess

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

.PHONY: clean

clean:
	del /Q $(TARGET).exe