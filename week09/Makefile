CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

TARGET = main
SRC = main.cpp

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

clean:
	rm -f $(TARGET)
