#include "tile_bag.h"
#include "tile_collection.h"
#include "exceptions.h"
#include <fstream>
#include <iostream>

using namespace std;


TileBag TileBag::read(std::string file_path, uint32_t seed) {
    TileBag bag(seed);

    std::ifstream file(file_path);
    if (!file) {
        throw FileException("cannot open bag file!");
    }

    char letter;
    unsigned short points;
    size_t count;

    while (!file.eof()) {
        file >> letter >> points >> count;
        TileKind kind(letter, points);
        bag.add_tiles(kind, count);
        bag.kinds.emplace(letter, kind);
    }

    return bag;
}

std::vector<TileKind> TileBag::remove_random_tiles(size_t count) {
    size_t total_count = this->count_tiles();

    std::vector<TileKind> result;
    for (size_t i = 0; i < count; ++i) {
        size_t index = std::uniform_int_distribution<size_t>(0, total_count - 1)(this->random);
        for (TileMap::iterator it = this->tiles.begin(); it != this->tiles.end(); ++it) {
            if (index < it->second) {
                it->second -= 1;
                total_count -= 1;
                result.push_back(it->first);
                break;
            }
            index -= it->second;
        }
    }

    return result;
}

const unordered_map<char, TileKind>& TileBag::get_kinds() const {
    return this->kinds;
}
