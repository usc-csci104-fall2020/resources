#include "scrabble_config.h"
#include "exceptions.h"
#include <fstream>
#include <cctype>

using namespace std;


enum class ParserState {
    LOOKING_FOR_KEY,    // not inside any structures at the moment, waiting for a key or a comment character
    IN_KEY,             // inside key, waiting for equals sign or whitespace
    LOOKING_FOR_VALUE,  // just saw colon, now looking for start of value
    IN_VALUE            // inside value, waiting for newline to end it.
};

ScrabbleConfig ScrabbleConfig::read(string file_path) {
    ifstream file(file_path);
    if (!file) {
        throw FileException("cannot open scrabble config file!");
    }

    string key_buffer;
    string value_buffer;
    char cursor;
    ParserState state = ParserState::LOOKING_FOR_KEY;
    ScrabbleConfig config;

    while (!file.eof()) {
        file.get(cursor);
        if (file.eof()) {
            break;
        }

        switch (state) {
        case ParserState::LOOKING_FOR_KEY:
            if (!isspace(cursor)) {
                key_buffer = toupper(cursor);
                state = ParserState::IN_KEY;
            }
            break;
        case ParserState::IN_KEY:
            if (cursor == ':') {
                state = ParserState::LOOKING_FOR_VALUE;
            } else {
                key_buffer += toupper(cursor);
            }
            break;
        case ParserState::LOOKING_FOR_VALUE:
            if (!isspace(cursor)) {
                value_buffer = cursor;
                state = ParserState::IN_VALUE;
            }
            break;
        case ParserState::IN_VALUE:
            if (cursor == '\n') {
                if (key_buffer == "SEED") {
                    config.seed = stoul(value_buffer);
                } else if (key_buffer == "HAND_SIZE") {
                    config.hand_size = stoul(value_buffer);
                } else if (key_buffer == "MINIMUM_WORD_SIZE") {
                    config.hand_size = stoul(value_buffer);
                } else if (key_buffer == "BOARD") {
                    config.board_file_path = value_buffer;
                } else if (key_buffer == "TILE_BAG") {
                    config.tile_bag_file_path = value_buffer;
                } else if (key_buffer == "DICTIONARY") {
                    config.dictionary_file_path = value_buffer;
                }
                state = ParserState::LOOKING_FOR_KEY;
            } else {
                value_buffer += cursor;
            }
            break;
        }
    }

    return config;
}
