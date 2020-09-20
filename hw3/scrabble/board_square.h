#ifndef BOARD_SQUARE_H
#define BOARD_SQUARE_H

#include "tile_kind.h"


class BoardSquare {
public:
    unsigned short letter_multiplier;
    unsigned short word_multiplier;

    BoardSquare(unsigned short letter_multiplier, unsigned short word_multiplier)
        : letter_multiplier(letter_multiplier)
        , word_multiplier(word_multiplier)
        , tile(false) {}

    bool has_tile() const;
    TileKind get_tile_kind() const;
    void set_tile_kind(TileKind kind);
    unsigned int get_points() const;

private:
    bool tile;
    union { TileKind tile_kind; };
};

#endif
