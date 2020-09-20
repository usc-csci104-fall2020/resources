#include "scrabble.h"
#include "formatting.h"
#include <iostream>
#include <iomanip>
#include <map>

using namespace std;


// Given to you. this does not need to be changed
Scrabble::Scrabble(const ScrabbleConfig& config)
    : hand_size(config.hand_size)
    , minimum_word_length(config.minimum_word_length)
    , tile_bag(TileBag::read(config.tile_bag_file_path, config.seed))
    , board(Board::read(config.board_file_path))
    , dictionary(Dictionary::read(config.dictionary_file_path)) {}


// Game Loop should cycle through players and get and execute that players move
// until the game is over.
void Scrabble::game_loop() {
    // TODO: implement this.

    // Useful cout expressions with fancy colors. Expressions in curly braces, indicate values you supply.
    // cout << "You gained " << SCORE_COLOR << {points} << rang::style::reset << " points!" << endl;
    // cout << "Your current score: " << SCORE_COLOR << {points} << rang::style::reset << endl;
    // cout << endl << "Press [enter] to continue.";
}

// Performs final score subtraction. Players lose points for each tile in their
// hand. The player who cleared their hand receives all the points lost by the
// other players.
void Scrabble::final_subtraction(vector<shared_ptr<Player>> & plrs) {
    // TODO: implement this method.
    // Do not change the method signature.
}

// You should not need to change this function.
void Scrabble::print_result() {
	// Determine highest score
    size_t max_points = 0;
	for (auto player : this->players) {
		if (player->get_points() > max_points) {
			max_points = player->get_points();
        }
	}

	// Determine the winner(s) indexes
	vector<shared_ptr<Player>> winners;
	for (auto player : this->players) {
		if (player->get_points() >= max_points) {
			winners.push_back(player);
        }
	}

    cout << (winners.size() == 1 ? "Winner:" : "Winners: ");
	for (auto player : winners) {
		cout << SPACE << PLAYER_NAME_COLOR << player->get_name();
	}
	cout << rang::style::reset << endl;

	// now print score table
    cout << "Scores: " << endl;
    cout << "---------------------------------" << endl;

	// Justify all integers printed to have the same amount of character as the high score, left-padding with spaces
    cout << setw(static_cast<uint32_t>(floor(log10(max_points) + 1)));

	for (auto player : this->players) {
		cout << SCORE_COLOR << player->get_points() << rang::style::reset << " | " << PLAYER_NAME_COLOR << player->get_name() << rang::style::reset << endl;
	}
}

// You should not need to change this.
void Scrabble::main() {
    add_players();
    game_loop();
    final_subtraction(this->players);
    print_result();
}
