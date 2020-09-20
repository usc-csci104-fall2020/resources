COMPILER=g++
OPTIONS=-g -std=c++17 -Wall -Wextra
COMPILE=$(COMPILER) $(OPTIONS)

main: main.cpp build/scrabble.o build/scrabble_config.o build/dictionary.o build/board.o build/board_square.o build/tile_bag.o build/tile_collection.o build/tile_kind.o build/player.o build/human_player.o build/move.o build/formatting.o
	$(COMPILE) $< build/*.o -o scrabble

build/scrabble.o: scrabble.cpp scrabble.h build/.make exceptions.h board.h tile_bag.h dictionary.h human_player.h scrabble_config.h move.h colors.h
	$(COMPILE) -c $< -o $@

build/human_player.o: human_player.cpp human_player.h build/.make place_result.h move.h exceptions.h human_player.h tile_kind.h formatting.h player.h
	$(COMPILE) -c $< -o $@

build/player.o: player.cpp player.h move.h build/.make
	$(COMPILE) -c $< -o $@

build/scrabble_config.o: scrabble_config.cpp scrabble_config.h build/.make
	$(COMPILE) -c $< -o $@

build/dictionary.o: dictionary.cpp dictionary.h build/.make
	$(COMPILE) -c $< -o $@

build/board.o: board.cpp board.h board_square.h build/.make
	$(COMPILE) -c $< -o $@

build/board_square.o: board_square.cpp board_square.h build/.make
	$(COMPILE) -c $< -o $@

build/move.o: move.cpp move.h build/.make
	$(COMPILE) -c $< -o $@

build/tile_bag.o: tile_bag.cpp tile_bag.h tile_kind.h tile_collection.h build/.make
	$(COMPILE) -c $< -o $@

build/tile_collection.o: tile_collection.cpp tile_collection.h tile_kind.h build/.make
	$(COMPILE) -c $< -o $@

build/tile_kind.o: tile_kind.cpp tile_kind.h build/.make
	$(COMPILE) -c $< -o $@

build/formatting.o: formatting.cpp formatting.h build/.make
	$(COMPILE) -c $< -o $@

build/.make:
	mkdir -p build
	touch build/.make

clean:
	rm -rf build
	rm -f scrabble
