#include "gtest/gtest.h"
#include <iostream>
#include <string>

#include "scrabble.h"
#include "scrabble_config.h"
#include "board.h"
#include "dictionary.h"
#include "tile_kind.h"
#include "human_player.h"
#include "tile_bag.h"

#define DICT_PATH "config/english-dictionary.txt"

using namespace std;

class PlaceTest : public testing::Test {
protected:
	PlaceTest() {}
	virtual ~PlaceTest() {}
	size_t hand_size = 7;
};

TEST_F(PlaceTest, place_empty_board_all_1_pts) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t;
	t.push_back(TileKind('G', 1));
	t.push_back(TileKind('O', 1));
	t.push_back(TileKind('O', 1));
	t.push_back(TileKind('D', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 4);
}

TEST_F(PlaceTest, place_empty_board_pts) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t;
	t.push_back(TileKind('G', 2));
	t.push_back(TileKind('O', 3));
	t.push_back(TileKind('O', 3));
	t.push_back(TileKind('D', 5));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 13);
}

TEST_F(PlaceTest, place_letter_2x) {
	Board b = Board::read("config/board1.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 6);
}

TEST_F(PlaceTest, place_letter_3x) {
	Board b = Board::read("config/board1.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::DOWN);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 7);
}

TEST_F(PlaceTest, place_word_2x) {
	Board b = Board::read("config/board2.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 10);
}

TEST_F(PlaceTest, place_word_3x) {
	Board b = Board::read("config/board2.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::DOWN);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 15);
}

TEST_F(PlaceTest, place_simple_word_letter_mult) {
	Board b = Board::read("config/board3.txt");

	vector<TileKind> t;
	t.push_back(TileKind('Y', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('S', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	// (1 + 1*3 +1)*2
	EXPECT_EQ(result.points, 10);
}

TEST_F(PlaceTest, place_word_letter_mult) {
	Board b = Board::read("config/board3.txt");

	vector<TileKind> t;
	t.push_back(TileKind('Y', 2));
	t.push_back(TileKind('E', 3));
	t.push_back(TileKind('S', 4));

	Move m = Move(t, 7, 7, Direction::DOWN);
	PlaceResult result = b.place(m);
	// (2 + 3*2 +4)*3
	EXPECT_EQ(result.points, 36);
}

TEST_F(PlaceTest, place_word_3x_2x) {
	Board b = Board::read("config/board4.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	// (1+1+1+1+1)*2*3
	EXPECT_EQ(result.points, 30);
}

TEST_F(PlaceTest, place_letter_3x_2x) {
	Board b = Board::read("config/board4.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 2));
	t.push_back(TileKind('L', 3));
	t.push_back(TileKind('L', 3));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::DOWN);
	PlaceResult result = b.place(m);
	// (1+2*2+3+3*3+1)
	EXPECT_EQ(result.points, 18);
}

TEST_F(PlaceTest, place_wildcard) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t;
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('L', 1));
	t.push_back(TileKind('?', 1, 'L'));
	t.push_back(TileKind('O', 1));

	Move m = Move(t, 7, 7, Direction::DOWN);
	PlaceResult result = b.place(m);
	EXPECT_EQ(result.points, 5);
}


TEST_F(PlaceTest, place_word_sharing_first_letter) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('O', 1));
	Move m1 = Move(t1, 7, 7, Direction::DOWN);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('D', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 7, 8, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	 //b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 4);
}

TEST_F(PlaceTest, place_word_sharing_middle_letter) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('O', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('F', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 6, 9, Direction::DOWN);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 4);
}

TEST_F(PlaceTest, place_word_extend) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('R', 1));
	Move m1 = Move(t1, 7, 5, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('W', 1));
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('S', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 7, 10, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 9);
}

TEST_F(PlaceTest, place_word_extend_front) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('R', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('G', 1));
	t2.push_back(TileKind('R', 1));
	t2.push_back(TileKind('A', 1));
	t2.push_back(TileKind('N', 1));
	t2.push_back(TileKind('D', 1));
	t2.push_back(TileKind('M', 1));



	Move m2 = Move(t2, 7, 1, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 11);
}

TEST_F(PlaceTest, place_word_extend_both) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('R', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('C', 1));
	t2.push_back(TileKind('R', 1));
	t2.push_back(TileKind('Y', 1));
	t2.push_back(TileKind('A', 1));
	t2.push_back(TileKind('P', 1));
	t2.push_back(TileKind('Y', 1));

	Move m2 = Move(t2, 7, 4, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 11);
}


TEST_F(PlaceTest, place_word_sharing_letters_diff_values) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 3));
	t1.push_back(TileKind('L', 2));
	t1.push_back(TileKind('L', 2));
	t1.push_back(TileKind('O', 9));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 3));
	t2.push_back(TileKind('F', 3));
	t2.push_back(TileKind('E', 3));
	Move m2 = Move(t2, 8, 10, Direction::DOWN);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 11);
}


TEST_F(PlaceTest, place_word_make_two) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('O', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('D', 1));
	Move m2 = Move(t2, 8, 7, Direction::DOWN);
	b.place(m2);

	vector<TileKind> t3;
	t3.push_back(TileKind('O', 1));
	t3.push_back(TileKind('S', 1));
	t3.push_back(TileKind('T', 1));
	Move m3 = Move(t3, 8, 9, Direction::DOWN);
	b.place(m3);

	vector<TileKind> t4;
	t4.push_back(TileKind('E', 1));
	t4.push_back(TileKind('N', 1));
	t4.push_back(TileKind('R', 1));
	t4.push_back(TileKind('Y', 1));
	Move m4 = Move(t4, 10, 7, Direction::ACROSS);
	PlaceResult result = b.place(m4);

	//b.print(std::cout);
	
	// HIDE + ENTRY = 10
	EXPECT_EQ(result.points, 9);
}

TEST_F(PlaceTest, place_word_sharing_lose_mult) {
	Board b = Board::read("config/board1.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('O', 1));
	Move m1 = Move(t1, 7, 7, Direction::DOWN);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 9, 8, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 3);
}

TEST_F(PlaceTest, place_word_sharing_lose_mult_use_other) {
	Board b = Board::read("config/board1.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('E', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('O', 1));
	Move m1 = Move(t1, 7, 7, Direction::DOWN);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('D', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 7, 8, Direction::ACROSS);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 5);
}

TEST_F(PlaceTest, place_word_sharing_lose_2_mult_use_other_2) {
	Board b = Board::read("config/board6.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('H', 1));
	t1.push_back(TileKind('I', 1));
	Move m1 = Move(t1, 7, 7, Direction::DOWN);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('E', 1));
	t2.push_back(TileKind('M', 1));
	t2.push_back(TileKind('P', 1));
	t2.push_back(TileKind('I', 1));
	t2.push_back(TileKind('R', 1));
	t2.push_back(TileKind('E', 1));
	Move m2 = Move(t2, 7, 8, Direction::DOWN);
	PlaceResult result = b.place(m2);

	//b.print(std::cout);

	// (1+1+1+1), should get points for previously places h
	EXPECT_EQ(result.points, 24+6+4);
}

TEST_F(PlaceTest, place_bad_start) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t;
	t.push_back(TileKind('B', 1));
	t.push_back(TileKind('A', 1));
	t.push_back(TileKind('D', 1));

	Move m = Move(t, 8, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_TRUE(!result.valid);
}

TEST_F(PlaceTest, place_bad_overlap) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('G', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('D', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('B', 1));
	t2.push_back(TileKind('A', 1));
	t2.push_back(TileKind('D', 1));


	Move m2 = Move(t2, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m2);
	EXPECT_TRUE(!result.valid);
}

TEST_F(PlaceTest, place_bad_out_of_bounds) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t;
	t.push_back(TileKind('A', 1));
	t.push_back(TileKind('T', 1));
	t.push_back(TileKind('M', 1));
	t.push_back(TileKind('O', 1));
	t.push_back(TileKind('S', 1));
	t.push_back(TileKind('P', 1));
	t.push_back(TileKind('H', 1));
	t.push_back(TileKind('E', 1));
	t.push_back(TileKind('R', 1));
	t.push_back(TileKind('E', 1));

	Move m = Move(t, 7, 7, Direction::ACROSS);
	PlaceResult result = b.place(m);
	EXPECT_TRUE(!result.valid);
}

TEST_F(PlaceTest, place_bad_no_adjacent) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('G', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('D', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('B', 1));
	t2.push_back(TileKind('A', 1));
	t2.push_back(TileKind('D', 1));


	Move m2 = Move(t2, 10, 2, Direction::ACROSS);
	PlaceResult result = b.place(m2);
	EXPECT_TRUE(!result.valid);
}

TEST_F(PlaceTest, place_bad_corner_adjacent) {
	Board b = Board::read("config/board0.txt");

	vector<TileKind> t1;
	t1.push_back(TileKind('G', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('D', 1));
	Move m1 = Move(t1, 7, 7, Direction::ACROSS);
	b.place(m1);

	vector<TileKind> t2;
	t2.push_back(TileKind('B', 1));
	t2.push_back(TileKind('A', 1));
	t2.push_back(TileKind('D', 1));


	Move m2 = Move(t2, 8, 11, Direction::DOWN);
	PlaceResult result = b.place(m2);
	EXPECT_TRUE(!result.valid);
}


// Test manipulating tiles in the players hand
class HandTest : public testing::Test {
protected:
	HandTest() {}
	virtual ~HandTest() {}
	size_t hand_size = 7;
};

TEST_F(HandTest, hand_empty_add) {
	HumanPlayer p = HumanPlayer("p", hand_size);
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 3052);
	vector<TileKind> draw = tb.remove_random_tiles(hand_size);
	
	p.add_tiles(draw);
	EXPECT_EQ(p.count_tiles(), hand_size);
	for(size_t i=0; i<draw.size(); i++) {
		EXPECT_TRUE(p.has_tile(draw[i]));
	}
}

TEST_F(HandTest, hand_remove) {
	HumanPlayer p = HumanPlayer("p", hand_size);
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 4412);
	vector<TileKind> draw = tb.remove_random_tiles(hand_size);
	
	p.add_tiles(draw);
	
	// Drop the last tiles from the hand (and draw vector)
	size_t num_pops = 3;
	vector<TileKind> removed_tiles;
	for(size_t i=0; i<num_pops; i++) {
		removed_tiles.push_back(draw[draw.size()-1]);
		draw.pop_back();
	}
	p.remove_tiles(removed_tiles);
	
	EXPECT_EQ(p.count_tiles(), hand_size-num_pops);
	for(size_t i=0; i<draw.size(); i++) {
		EXPECT_TRUE(p.has_tile(draw[i]));
	}
}

TEST_F(HandTest, hand_remove_no_tiles) {
	HumanPlayer p = HumanPlayer("p", hand_size);
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 7152);
	vector<TileKind> draw = tb.remove_random_tiles(hand_size);
	
	p.add_tiles(draw);
	
	vector<TileKind> remove;
	remove.push_back(TileKind('X', 1));

	EXPECT_ANY_THROW(p.remove_tiles(remove));
}

TEST_F(HandTest, hand_remove_not_enough) {
	HumanPlayer p = HumanPlayer("p", hand_size);
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 7152);
	vector<TileKind> draw = tb.remove_random_tiles(hand_size);
	
	p.add_tiles(draw);
	
	vector<TileKind> remove;
	remove.push_back(TileKind('B', 1));
	remove.push_back(TileKind('B', 1));
	remove.push_back(TileKind('B', 1));

	EXPECT_ANY_THROW(p.remove_tiles(remove));
}


TEST_F(HandTest, hand_replace_all) {
	HumanPlayer p = HumanPlayer("p", hand_size);
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 6598);
	vector<TileKind> draw = tb.remove_random_tiles(hand_size);
	
	p.add_tiles(draw);
	EXPECT_EQ(p.count_tiles(), 7);
	for(size_t i=0; i<draw.size(); i++) {
		EXPECT_TRUE(p.has_tile(draw[i]));
	}
	
	p.remove_tiles(draw);
	EXPECT_EQ(p.count_tiles(), 0);
	for(size_t i=0; i<draw.size(); i++) {
		EXPECT_FALSE(p.has_tile(draw[i]));
	}

	draw = tb.remove_random_tiles(hand_size);
	p.add_tiles(draw);
	EXPECT_EQ(p.count_tiles(), 7);
	for(size_t i=0; i<draw.size(); i++) {
		EXPECT_TRUE(p.has_tile(draw[i]));
	}
}

class DictionaryTest : public testing::Test {
protected:
	DictionaryTest() {}
	virtual ~DictionaryTest() {}
	Dictionary d = Dictionary::read(DICT_PATH);
};

TEST_F(DictionaryTest, bad_word) {
	bool upper = !d.is_word("QPFKATD");
	bool lower = !d.is_word("qpfkatd");
	bool result = upper && lower; // One should fail bc of case, other should fail bc not found
	EXPECT_TRUE(result);
}

TEST_F(DictionaryTest, good_word) {
	bool upper = d.is_word("GOOD");
	bool lower = d.is_word("good");
	bool result = upper || lower; // One might fail, thats OK
	EXPECT_TRUE(result);
}

class FinalSubtractionTest : public testing::Test {
protected:
	FinalSubtractionTest() {}
	virtual ~FinalSubtractionTest() {}
	Dictionary d = Dictionary::read(DICT_PATH);
	size_t hand_size=5;
};


TEST_F(FinalSubtractionTest, no_empty_hand) {
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 6598);
	vector<shared_ptr<Player>> players;
	vector<size_t> hand_values;
	vector<size_t> points;

	for(size_t i=0; i<4; i++) {
		shared_ptr<Player> player = make_shared<HumanPlayer>(to_string(i), hand_size);
		player->add_tiles(tb.remove_random_tiles(this->hand_size));
		player->add_points(i*50);

		points.push_back(player->get_points());
		hand_values.push_back(player->get_hand_value());
		players.push_back(player);
	}
	
	Scrabble::final_subtraction(players);
	
	for(size_t i=0; i<4; i++) {
		if(hand_values[i] >= points[i]) {
			EXPECT_EQ(players[i]->get_points(), 0);
		} else {
			EXPECT_EQ(players[i]->get_points(), points[i]-hand_values[i]);
		}
	}
}

TEST_F(FinalSubtractionTest, player_0_empty_hand) {
	TileBag tb = TileBag::read("config/english-tile-bag.txt", 6598);
	vector<shared_ptr<Player>> players;
	vector<size_t> hand_values;
	vector<size_t> points;


	shared_ptr<Player> player0 = make_shared<HumanPlayer>("0", hand_size);
	player0->add_points(1);
	points.push_back(player0->get_points());
	hand_values.push_back(player0->get_hand_value());
	players.push_back(player0);

	size_t hand_points_sum=0;
	for(size_t i=1; i<6; i++) {
		shared_ptr<Player> player = make_shared<HumanPlayer>(to_string(i), hand_size);
		player->add_tiles(tb.remove_random_tiles(this->hand_size));
		player->add_points(i*50);

		points.push_back(player->get_points());
		hand_values.push_back(player->get_hand_value());
		hand_points_sum += player->get_hand_value();
		players.push_back(player);
	}
	
	Scrabble::final_subtraction(players);
	
	EXPECT_EQ(players[0]->get_points(), hand_points_sum+1);

	for(size_t i=1; i<6; i++) {
		EXPECT_EQ(players[i]->get_points(), points[i]-hand_values[i]);
	}
}

