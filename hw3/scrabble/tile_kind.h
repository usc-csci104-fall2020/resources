#ifndef TILE_KIND_H
#define TILE_KIND_H

#include <cctype>


struct TileKind {
    unsigned short points;
    char letter;
    char assigned;

    static const char BLANK_LETTER = '?';

    TileKind(char letter, unsigned short points) :
        points(points),
        letter(std::tolower(letter)),
        assigned('\0') {}
    TileKind(char letter, unsigned short points, char assigned) :
        points(points),
        letter(std::tolower(letter)),
        assigned(std::tolower(assigned)) {};
};

bool operator<(const TileKind lhs, const TileKind rhs);
bool operator==(const TileKind lhs, const TileKind rhs);

#endif
