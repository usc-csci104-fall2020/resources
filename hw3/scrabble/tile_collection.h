#ifndef TILE_COLLECTION_H
#define TILE_COLLECTION_H

#include "tile_kind.h"
#include <map>
#include <vector>


typedef std::map<TileKind, size_t> TileMap;

class TileCollection {
public:
    class const_iterator;

    void add_tile(TileKind kind);
    void add_tiles(TileKind kind, size_t n);

    void remove_tile(TileKind kind);
    void remove_tiles(TileKind kind, size_t n);

    TileKind lookup_tile(char letter) const;

    size_t count_tiles() const;
    size_t count_tiles(TileKind kind) const;

    unsigned int total_points() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    class const_iterator
    {
        public:
            typedef const_iterator self_type;
            typedef TileKind value_type;
            typedef TileKind& reference;
            typedef TileKind* pointer;
            typedef int difference_type;
            typedef std::forward_iterator_tag iterator_category;
            const_iterator(TileMap::const_iterator it) : map_itr(it), temp('\0', 0) {
                while (map_itr->second == 0) // if amount is 0, pair should have been erased. This is a second check.
                    map_itr++;
            }
            self_type operator++();
            self_type operator++(int junk);
            reference operator*() {temp = map_itr->first; return temp;}
            const value_type* operator->() { return &(map_itr->first); }
            bool operator==(const self_type& rhs) { return map_itr == rhs.map_itr && repeat_count == rhs.repeat_count; }
            bool operator!=(const self_type& rhs) { return map_itr != rhs.map_itr || repeat_count != rhs.repeat_count;}
        private:
            size_t repeat_count = 0;
            TileMap::const_iterator map_itr;
            TileKind temp;
    };

protected:
    TileMap tiles;
};

#endif
