#ifndef BOARD_H
#define BOARD_H

#include "exceptions.h"
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

    struct Anchor {
        Position position;
        Direction direction;
        size_t limit;

        Anchor(Position p, Direction d, size_t l) : 
            position(p), direction(d), limit(l) {}
    };

    Position start;

    static Board read(const std::string& file_path); // Used for testing

    size_t get_move_index() const;

    /*
    The goal of test_place() is to check what would happen if a given Move was executed on the board. It should not actually modify the board in any way. It should fill in a PlaceResult with, quoting the assignment, "whether the move is valid, what words would be generated, how many points the move would be worth... or if not valid, what error message to display"

    So, first and foremost, test_place() should determine if the given move is valid to execute on this board. If it is not valid, then return a PlaceResult with valid set to false, and set the error field to a human-readable error message that shows the user what they did wrong (there are no specific requirements for this error message as long as it describes the error).
    On the other hand, if the move is valid, then test_place() should set valid to true and the list of all created words should be returned in the words field of the PlaceResult. It should also total up all points scored by the move and return those in the PlaceResult's points field (see the Scoring section of the assignment).

    NOTE: test_place() does not (and can't) check if the words formed are actually in the dictionary. Checking if words are valid is the responsibility of the caller of test_place()!
    */
    PlaceResult test_place(const Move& move) const;

    PlaceResult place(const Move& move); // Used for testing - remember that the move struct should use 0 based indexing, NOT 1 based

    void print(std::ostream& out) const;

    // Note: These methods have been made public
    bool is_in_bounds(const Position& position) const;
    bool in_bounds_and_has_tile(const Position& position) const;

    /* HW5: IMPLEMENT THIS
    Returns the letter at a position.
    Assumes there is a tile at p
    */
    char letter_at(Position p) const;

    /* HW5: IMPLEMENT THIS
    Returns bool indicating whether position p is an anchor spot or not.
    
    A position is an anchor spot if it is 
        1) In bounds
        2) Unoccupied
        2) Either adjacent to a placed tile or is the start square
    */
    bool is_anchor_spot(Position p) const; 

    /* HW5: IMPLEMENT THIS
    Returns a vector of all the Anchors on the board.

    For every anchor sqare on the board, it should include two Anchors in the vector.
        One for ACROSS and one for DOWN
    The limit for the Anchor is the number of unoccupied, non-anchor squares preceeding the anchor square in question. 
    */
    std::vector<Anchor> get_anchors() const; // Used for testing

protected:
    Board(size_t rows, size_t columns, size_t starting_row, size_t starting_column)
        : rows(rows)
        , columns(columns)
        , start(starting_row - 1, starting_column - 1) {}

private:
    BoardSquare& at(const Position& position);
    const BoardSquare& at(const Position& position) const;

    std::vector<std::vector<BoardSquare>> squares;
    size_t move_index = 0;
};

#endif
