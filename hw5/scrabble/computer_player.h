#ifndef COMPUTER_PLAYER_H 
#define COMPUTER_PLAYER_H

#include "move.h"
#include "player.h"



class ComputerPlayer : public Player {
public:
    /* HW5: DECLARE AND IMPLEMENT THIS
    Should have one parameterized constructor that takes a string name (const reference) and a size_t hand size. 
    */
   ComputerPlayer(){}; // <--- FIX THIS LINE


    /* HW5: IMPLEMENT THIS
    Returns the move found by running the algorithm given here:
        https://www.cs.cmu.edu/afs/cs/academic/class/15451-s06/www/lectures/scrabble.pdf
    
    See assignment for more details.
    */
    Move get_move(const Board& board, const Dictionary& dictionary) const override; // Used For Testing

	bool is_human() const { return false; }

private:
    // The following functions may be modified in any way. 
    // e.g. You may decide you'd prefer to pass in a Dictionary reference rather than std::shared_ptr<Dictionary::TrieNode>

    /* 
    Searches all possible prefixes of size up to limit and calls extend_right for each one

    anchor: The board position for the anchor square
    partial_word: the partial word that has already been searched
    partial_move: the Move object associated with the partial word (has tiles for each letter in partial_word)
    node: The node in the Dictionary associated with partial_word
    limit: The max prefix size to consider
    remaining_tiles: The tiles that can still be used to form a move
        Passed by reference
        Tiles should be removed when every searching forward on that tile
        Tiles should be put back in remaining_tiles when backtracking
    legal_moves: A vector that accumulates Moves that create a valid word
        Note: Does not necessarily need to check perpendicular words while searching
              but it can if you prefer. 
    board: a reference to the scrabble board
    */
    void left_part(Board::Position anchor_pos,
                   std::string partial_word,
                   Move partial_move, 
                   std::shared_ptr<Dictionary::TrieNode> node, 
                   size_t limit,
                   TileCollection& remaining_tiles,
                   std::vector<Move>& legal_moves,
                   const Board& board) const;

    /* 
    Given a square (not necessarily an anchor square) and a prefix finds all legal ways to extend the word to make valid words.

    square: The board position to search from
    partial_word: the partial word that has already been formed
    partial_move: the Move object associated with the partial word 
        (has tiles for each letter in partial_word, unless that tile was already on the board)
    node: The node in the Dictionary associated with partial_word
    remaining_tiles: The tiles that can still be used to form a move
        Passed by reference
        Tiles should be removed when every searching forward on that tile
        Tiles should be put back in remaining_tiles when backtracking
    legal_moves: A vector that accumulates Moves that create a valid word
        Note: Does not necessarily need to check perpendicular words while searching
              but it can if you prefer. 
    board: a reference to the scrabble board
    */
    void extend_right(Board::Position square,
                      std::string partial_word,
                      Move partial_move, 
                      std::shared_ptr<Dictionary::TrieNode> node,
                      TileCollection& remaining_tiles,
                      std::vector<Move>& legal_moves,
                      const Board& board) const;


    /* 
	Searches the vector of legal moves for the highest scoring move
    Ties broken arbitrarily
    */
    Move get_best_move(std::vector<Move> legal_moves, 
                       const Board& board, 
                       const Dictionary& dictionary) const;
};


#endif
