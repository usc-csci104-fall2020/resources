#include "tile_collection.h"
#include <stdexcept>

using namespace std;


void TileCollection::add_tile(TileKind kind) {
    this->add_tiles(kind, 1);
}

void TileCollection::add_tiles(TileKind kind, size_t n) {
    TileMap::iterator index = this->tiles.find(kind);
    if (index == this->tiles.end()) {
        this->tiles.emplace(kind, n);
    } else {
        index->second += n;
    }
}

void TileCollection::remove_tile(TileKind kind) {
    this->remove_tiles(kind, 1);
}

void TileCollection::remove_tiles(TileKind kind, size_t n) {
    if (n == 0)
        return;
    TileMap::iterator index = this->tiles.find(kind);
    if (index == this->tiles.end()) {
        throw out_of_range("no such tile to remove");
    } else if (index->second < n) {
        throw out_of_range("not enough tiles to remove");
    } else {
        index->second -= n;
        if (index->second == 0)
            tiles.erase(index);
    }
}

TileKind TileCollection::lookup_tile(char letter) const {
    for (TileMap::const_iterator it = tiles.begin(); it != tiles.end(); it++) {
        if (it->first.letter == tolower(letter)) {
            return it->first;
        }
    }
    throw out_of_range("Tile not found.");
}

size_t TileCollection::count_tiles() const {
    size_t count {0};
    for (TileMap::const_iterator it = this->tiles.cbegin(); it != this->tiles.cend(); ++it) {
        count += it->second;
    }
    return count;
}

size_t TileCollection::count_tiles(TileKind kind) const {
    TileMap::const_iterator index = this->tiles.find(kind);
    if (index == this->tiles.end()) {
        return 0;
    } else {
        return index->second;
    }
}

unsigned int TileCollection::total_points() const {
    unsigned int sum = 0;
    for (TileMap::const_iterator map_itr = tiles.begin(); map_itr != tiles.end(); map_itr++) {
        sum += (map_itr->first.points * map_itr->second);
    }
    return sum;
}

TileCollection::const_iterator::self_type TileCollection::const_iterator::operator++(){
    repeat_count++;
    if (repeat_count == map_itr->second){
        map_itr++;
        repeat_count = 0;
    }
    while (map_itr->second == 0)
        map_itr++;
    return *this;
}

TileCollection::const_iterator::self_type TileCollection::const_iterator::operator++(int junk){
	(void)junk;  // Suppress unused variable warning.
    self_type i = *this;
    operator++();
    return i;
}

TileCollection::const_iterator TileCollection::cbegin() const {
    return const_iterator(tiles.cbegin());
}

TileCollection::const_iterator TileCollection::cend() const {
    return const_iterator(tiles.cend());
}
