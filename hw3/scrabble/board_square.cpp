#include "board_square.h"


bool BoardSquare::has_tile() const {
    return this->tile;
}

TileKind BoardSquare::get_tile_kind() const {
    return this->tile_kind;
}

void BoardSquare::set_tile_kind(TileKind kind) {
    this->tile = true;
    this->tile_kind = kind;
}

unsigned int BoardSquare::get_points() const {
    return this->has_tile() ? this->tile_kind.points * this->letter_multiplier : 0;
}
