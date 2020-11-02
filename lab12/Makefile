CC = g++
CPPFLAGS = -g -Wall -std=c++17
TEST_DIR = tests
BIN_DIR = bin
GTEST_LL = -I /usr/include/gtest/ -l gtest -l gtest_main -pthread

all test tests: $(BIN_DIR) $(BIN_DIR)/HashtableTest
	valgrind --leak-check=yes ./$(BIN_DIR)/HashtableTest

HashtableTest: $(BIN_DIR) $(BIN_DIR)/HashtableTest
	valgrind --leak-check=yes  ./$(BIN_DIR)/HashtableTest

$(BIN_DIR)/HashtableTest: $(TEST_DIR)/HashtableTest.cpp $(BIN_DIR)/hashtable.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/hashtable.o: hashtable.cpp hashtable.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR): 
	mkdir $(BIN_DIR)

.phony: clean test

clean:
	rm -rf $(BIN_DIR)
