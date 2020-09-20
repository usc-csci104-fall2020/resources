#ifndef BOARD_H
#define BOARD_H

#include "tile_kind.h"
#include "board_square.h"
#include "move.h"
#include "place_result.h"
#include <string>
#include <vector>
#include <ostream>


class Board {
public:
    size_t rows;
    size_t columns;

    struct Position {
        size_t row;
        size_t column;

        Position(size_t row, size_t column) : row(row), column(column) {}

        bool operator==(const Position& other) const;
        bool operator!=(const Position& other) const;
        Position translate(Direction direction) const;
        Position translate(Direction direction, ssize_t distance) const;
    };

    Position start;

    static Board read(const std::string& file_path);

    size_t get_move_index() const;

    // Test_place should verify that the move given as an argument can be placed on the board
    // It should return a valid PlaceResult object with appropriate words if so
    // and an invalid PlaceResult object with error message otherwise.
    PlaceResult test_place(const Move& move) const;

    // If the move given is valid and can be placed on the board, this method
    // will make the changes to the board for the move and return the
    // PlaceResult object. The result returned by this method should be exactly
    // what test_place would return, so consider simply using test_place then
    // modifying the board.
    PlaceResult place(const Move& move);

    // Remember that the move struct should use 0-based indexing, not 1-based.
    // This is because the move struct uses C++ indexing, which starts with 0,
    // whereas the game uses 1 based indexing for human players

    void print(std::ostream& out) const;

protected:
    Board(size_t rows, size_t columns, size_t starting_row, size_t starting_column)
        : rows(rows)
        , columns(columns)
        , start(starting_row - 1, starting_column - 1) {}

private:
    BoardSquare& at(const Position& position);
    const BoardSquare& at(const Position& position) const;

    bool is_in_bounds(const Position& position) const;
    bool in_bounds_and_has_tile(const Position& position) const;

    std::vector<std::vector<BoardSquare>> squares;
    size_t move_index = 0;
};

#endif
