#include "tile_kind.h"


bool operator<(const TileKind lhs, const TileKind rhs) {
    return lhs.letter < rhs.letter;
}

bool operator==(const TileKind lhs, const TileKind rhs) {
    return lhs.letter == rhs.letter;
}
