CC = g++
CPPFLAGS = -g -Wall -std=c++17
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all: EvenOddTest NumLeavesTest

EvenOddTest: $(BIN_DIR) $(BIN_DIR)/EvenOddTest
	valgrind --leak-check=yes ./$(BIN_DIR)/EvenOddTest

NumLeavesTest: $(BIN_DIR) $(BIN_DIR)/NumLeavesTest
	valgrind --leak-check=yes ./$(BIN_DIR)/NumLeavesTest

$(BIN_DIR)/EvenOddTest: $(BIN_DIR)/EvenOddTest.o $(BIN_DIR)/evenOdd.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/EvenOddTest.o: $(TEST_DIR)/EvenOddTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/evenOdd.o: evenOdd.cpp evenOdd.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/NumLeavesTest: $(BIN_DIR)/NumLeavesTest.o $(BIN_DIR)/numLeaves.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/NumLeavesTest.o: $(TEST_DIR)/NumLeavesTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/numLeaves.o: numLeaves.cpp numLeaves.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean

clean:
	rm -rf $(BIN_DIR)
