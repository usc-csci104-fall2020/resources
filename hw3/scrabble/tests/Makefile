STU_PATH = ..

BIN_DIR = bin
CC = g++
CPPFLAGS = -Wall -g -I$(STU_PATH)
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/.dirstamp scrabble_test
	./scrabble_test

scrabble_test: scrabble_test.cpp $(BIN_DIR)/human_player.o $(BIN_DIR)/player.o $(BIN_DIR)/scrabble_config.o $(BIN_DIR)/dictionary.o $(BIN_DIR)/board.o  $(BIN_DIR)/board_square.o $(BIN_DIR)/move.o $(BIN_DIR)/tile_bag.o $(BIN_DIR)/tile_collection.o $(BIN_DIR)/tile_kind.o $(BIN_DIR)/formatting.o $(BIN_DIR)/scrabble.o
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/scrabble.o:	$(STU_PATH)/scrabble.cpp $(STU_PATH)/scrabble.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/human_player.o: $(STU_PATH)/human_player.cpp $(STU_PATH)/human_player.h $(STU_PATH)/move.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/player.o: $(STU_PATH)/player.cpp $(STU_PATH)/player.h $(STU_PATH)/move.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/scrabble_config.o: $(STU_PATH)/scrabble_config.cpp $(STU_PATH)/scrabble_config.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/dictionary.o: $(STU_PATH)/dictionary.cpp $(STU_PATH)/dictionary.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/board.o: $(STU_PATH)/board.cpp $(STU_PATH)/board.h $(STU_PATH)/board_square.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/board_square.o: $(STU_PATH)/board_square.cpp $(STU_PATH)/board_square.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/move.o: $(STU_PATH)/move.cpp $(STU_PATH)/move.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/tile_bag.o: $(STU_PATH)/tile_bag.cpp $(STU_PATH)/tile_bag.h $(STU_PATH)/tile_kind.h $(STU_PATH)/tile_collection.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/tile_collection.o: $(STU_PATH)/tile_collection.cpp $(STU_PATH)/tile_collection.h $(STU_PATH)/tile_kind.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/tile_kind.o: $(STU_PATH)/tile_kind.cpp $(STU_PATH)/tile_kind.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/formatting.o: $(STU_PATH)/formatting.cpp $(STU_PATH)/formatting.h
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean
clean:
	rm -rf $(BIN_DIR)
	rm scrabble_test


