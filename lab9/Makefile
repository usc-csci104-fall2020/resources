CC = g++
CPPFLAGS = -g -Wall -std=c++11
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

BSTTest: $(BIN_DIR) $(BIN_DIR)/BSTTest
	valgrind --leak-check=yes ./$(BIN_DIR)/BSTTest

$(BIN_DIR)/BSTTest: $(BIN_DIR)/BSTTest.o $(BIN_DIR)/bst.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/BSTTest.o: $(TEST_DIR)/BSTTest.cpp
	$(CC) $(CPPFLAGS) -c $^ -o $@

$(BIN_DIR)/bst.o: bst.cpp bst.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)
