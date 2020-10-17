
#include <memory>

#include "computer_player.h"
#include <string>



void ComputerPlayer::left_part(Board::Position anchor_pos, 
                               std::string partial_word,
                               Move partial_move, 
                               std::shared_ptr<Dictionary::TrieNode> node, 
                               size_t limit,
                               TileCollection& remaining_tiles,
                               std::vector<Move>& legal_moves,
                               const Board& board) const {
    // HW5: IMPLEMENT THIS
}

void ComputerPlayer::extend_right(Board::Position square,
                                  std::string partial_word,
                                  Move partial_move, 
                                  std::shared_ptr<Dictionary::TrieNode> node,
                                  TileCollection& remaining_tiles,
                                  std::vector<Move>& legal_moves,
                                  const Board& board) const {
    // HW5: IMPLEMENT THIS
}

Move ComputerPlayer::get_move(const Board& board, const Dictionary& dictionary) const {
	std::vector<Move> legal_moves;
    std::vector<Board::Anchor> anchors = board.get_anchors();
    // HW5: IMPLEMENT THIS
	
	
	return get_best_move(legal_moves, board, dictionary);
}

Move ComputerPlayer::get_best_move(std::vector<Move> legal_moves, const Board& board, const Dictionary& dictionary) const {
    Move best_move = Move(); // Pass if no move found	
	// HW5: IMPLEMENT THIS
	
	
	return best_move();	
}
