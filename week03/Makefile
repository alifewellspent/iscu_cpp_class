CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra -pedantic -g

TARGET = main
SRC = main.cpp

build:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run: build
	./$(TARGET)

check: build
	bash check.sh

clean:
	rm -f $(TARGET)
