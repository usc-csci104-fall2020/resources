#ifndef TILE_COLLECTION_H
#define TILE_COLLECTION_H

#include "tile_kind.h"
#include <map>
#include <vector>


typedef std::map<TileKind, size_t> TileMap;

/*
 Special data structure used for storing tiles.  Allows you to store individual
 instances of a tile and keeps track of how many are currently in the collection.
*/
class TileCollection {
public:
    class const_iterator;

    /*
     Adds one of the given tile to the collection.
     */
    void add_tile(TileKind kind);

    /*
     Adds n of the given tile to the collection.
     */
    void add_tiles(TileKind kind, size_t n);

    /*
     Removes one of the given tile from the collection.
     If this tile does not exist in the collection, an std::out_of_range exception is thrown.
     */
    void remove_tile(TileKind kind);

    /*
     Removes n of the given tile from the collection.
     If this tile does not exist in the collection, or if not enough exist to satisfy the request,
     an std::out_of_range exception is thrown.
     */
    void remove_tiles(TileKind kind, size_t n);

    /*
     Find the TileKind in this collection matching a given letter.
     Throws std::out_of_range if no tile with this letter exists in the collection.
     */
    TileKind lookup_tile(char letter) const;

    /*
     Get the total number of all tiles in this collection.
     */
    size_t count_tiles() const;

    /*
     Get the total number of this kind of tile that exist in the collection.
     */
    size_t count_tiles(TileKind kind) const;

    /*
     Get the sum of all point values of all tiles in the collection
     */
    unsigned int total_points() const;

    /*
     Get an iterator to the first element
     */
    const_iterator cbegin() const;

    /*
     Get an iterator past the last element
     */
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
