#ifndef SCRABBLE_CONFIG
#define SCRABBLE_CONFIG

#include <string>
#include <cstdint>


class ScrabbleConfig {
public:
    uint32_t seed;
    size_t hand_size;
    size_t minimum_word_length;
    std::string board_file_path;
    std::string tile_bag_file_path;
    std::string dictionary_file_path;

    static ScrabbleConfig read(std::string file_path);
};

#endif
