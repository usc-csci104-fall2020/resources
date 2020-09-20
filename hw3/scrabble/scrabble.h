#ifndef SCRABBLE_H
#define SCRABBLE_H

#include "exceptions.h"
#include "board.h"
#include "tile_bag.h"
#include "dictionary.h"
#include "human_player.h"
#include "scrabble_config.h"
#include "rang.h"
#include "move.h"
#include "colors.h"
#include <cmath>
#include <memory>


class Scrabble {
public:
    Scrabble(const ScrabbleConfig& config);

    void main();

    static const size_t EMPTY_HAND_BONUS = 50;

    static void final_subtraction(std::vector<std::shared_ptr<Player>>& players); // public for testing

private:
    // TODO: you may add more private members.

    size_t hand_size;
    size_t minimum_word_length;

    TileBag tile_bag;
    Board board;
    Dictionary dictionary;
    std::vector<std::shared_ptr<Player>> players;

    void add_players();
    void game_loop();
    void print_result();
};

#endif
