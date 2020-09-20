#ifndef PLAYER_H
#define PLAYER_H

#include "move.h"
#include "board.h"
#include "dictionary.h"
#include "tile_collection.h"
#include <string>
#include <vector>

class Player {
public:
    Player(const std::string& name, size_t hand_size) // Used for testing
        : name(name)
        , hand_size(hand_size)
        , points(0) {}
    virtual ~Player() {};

    /* Adds points to player's score */
    void add_points(size_t points);

    /* Subtracts points from player's score */
    void subtract_points(size_t points);

    size_t get_points() const; // Used for testing

    const std::string& get_name() const;

    /* Returns a VALID move that can be executed (can be placed, exchanged, or passed).*/
    virtual Move get_move(const Board& board, const Dictionary& d) const = 0;

    /* Returns the number of tiles in a player's hand */
    size_t count_tiles() const; // Used for testing

    /* Removes tiles from player's hand */
    void remove_tiles(const std::vector<TileKind>& tiles); // Used for testing

    /* Adds tiles to player's hand. */
    void add_tiles(const std::vector<TileKind>& tiles); // Used for testing
	
    /* Checks if player has a matching tile */
    bool has_tile(TileKind tile); // Used for testing

    /* Returns the total points of all tiles in the players hand */
    unsigned int get_hand_value() const; // Used for testing
    
    size_t get_hand_size() const;

protected:
 // Add any protected data members or functions here
private:
 // Add any private data members or functions here
    std::string name;
    size_t hand_size;
    size_t points;
};

#endif
