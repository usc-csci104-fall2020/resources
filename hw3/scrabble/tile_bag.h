#ifndef TILE_BAG_H
#define TILE_BAG_H

#include "tile_kind.h"
#include "tile_collection.h"
#include <vector>
#include <unordered_map>
#include <string>
#include <random>


class TileBag : public TileCollection {
public:
    static TileBag read(std::string file_path, uint32_t seed);

    std::vector<TileKind> remove_random_tiles(size_t count); // Used for testing

    const std::unordered_map<char, TileKind>& get_kinds() const;

protected:
    TileBag(uint32_t seed) : random(seed) {}

private:
    std::unordered_map<char, TileKind> kinds;
    std::mt19937 random;
};

#endif
