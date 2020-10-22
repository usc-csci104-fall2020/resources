#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <algorithm>

#include "scrabble_config.h"
#include "board.h"
#include "dictionary.h"
#include "tile_kind.h"
#include "human_player.h"
#include "computer_player.h"

#define DICT_PATH "config/english-dictionary.txt"

using namespace std;

class DictionaryTest : public testing::Test {
protected:
	DictionaryTest() {}
	virtual ~DictionaryTest() {}
	Dictionary d = Dictionary::read(DICT_PATH);
};

TEST_F(DictionaryTest, is_word0) {
	EXPECT_TRUE(d.is_word("hi"));
}

TEST_F(DictionaryTest, is_word1) {
	EXPECT_TRUE(d.is_word("hello"));
}

TEST_F(DictionaryTest, is_word2) {
	EXPECT_FALSE(d.is_word("hel"));
}

TEST_F(DictionaryTest, is_word3) {
	EXPECT_TRUE(d.is_word("abstractionists"));
}

TEST_F(DictionaryTest, is_word4) {
	EXPECT_TRUE(d.is_word("abstractionist"));
}

TEST_F(DictionaryTest, is_word5) {
	EXPECT_TRUE(d.is_word("abstract"));
}

TEST_F(DictionaryTest, is_word6) {
	EXPECT_FALSE(d.is_word("abstractio"));
}

TEST_F(DictionaryTest, is_word7) {
	EXPECT_FALSE(d.is_word("abstr"));
}

TEST_F(DictionaryTest, is_word8) {
	EXPECT_TRUE(d.is_word("a"));
}

TEST_F(DictionaryTest, next_letters_all_found) {
	vector<char> n = d.next_letters("a");
	EXPECT_TRUE(find(n.begin(), n.end(), 'b') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'i') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'q') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'k') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'x') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'z') != n.end());
}

TEST_F(DictionaryTest, next_letters_missing) {
	vector<char> n = d.next_letters("abstrac");
	EXPECT_TRUE(find(n.begin(), n.end(), 't') != n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'k') == n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'p') == n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'x') == n.end());
	EXPECT_TRUE(find(n.begin(), n.end(), 'z') == n.end());
}

TEST_F(DictionaryTest, find_prefix_incomplete) {
	std::shared_ptr<Dictionary::TrieNode> pre = d.find_prefix("hel");
	EXPECT_FALSE(pre->is_final);
	EXPECT_TRUE(pre->nexts.find('l') != pre->nexts.end());
	EXPECT_TRUE(pre->nexts.find('z') == pre->nexts.end());
}

TEST_F(DictionaryTest, find_prefix_complete) {
	std::shared_ptr<Dictionary::TrieNode> pre = d.find_prefix("hello");
	EXPECT_TRUE(pre->is_final);
	EXPECT_TRUE(pre->nexts.find('s') != pre->nexts.end());
	EXPECT_TRUE(pre->nexts.find('i') != pre->nexts.end());
	EXPECT_TRUE(pre->nexts.find('f') == pre->nexts.end());
	EXPECT_TRUE(pre->nexts.find('z') == pre->nexts.end());
}

TEST_F(DictionaryTest, find_prefix_empty) {
	std::shared_ptr<Dictionary::TrieNode> pre = d.find_prefix("abstractionists");
	EXPECT_TRUE(pre->is_final);
	EXPECT_TRUE(pre->nexts.empty());
}

TEST_F(DictionaryTest, find_prefix_null) {
	std::shared_ptr<Dictionary::TrieNode> pre = d.find_prefix("asdgadfg");
	EXPECT_TRUE(pre == nullptr);
}


// Helper functions for placing words in get_anchors() and get_move() tests
void print_words(PlaceResult res, Move m){
	std::cout << m.row + 1 << ' ' << m.column + 1 << ' ';
	if (m.direction == Direction::ACROSS)
		std::cout << "- ";
	else
		std::cout << "| ";
	for (auto word : res.words)
		std::cout << word << " ";
	std::cout << std::endl;
}

void place_simple_word(Board &b) {
	vector<TileKind> t;
    t.push_back(TileKind('H', 1));
    t.push_back(TileKind('I', 1));

    Move m = Move(t, 7, 7, Direction::ACROSS);
    b.place(m);
}

void place_two_words(Board &b) {
	vector<TileKind> t1;
    t1.push_back(TileKind('H', 1));
    t1.push_back(TileKind('I', 1));

    Move m1 = Move(t1, 7, 7, Direction::ACROSS);
    b.place(m1);

	vector<TileKind> t2;
    t2.push_back(TileKind('A', 1));
    t2.push_back(TileKind('A', 1));

    Move m2 = Move(t2, 5, 7, Direction::DOWN);
    b.place(m2);
}

void place_long_word(Board &b) {
	vector<TileKind> t1;
    t1.push_back(TileKind('B', 1));
    t1.push_back(TileKind('L', 1));
	t1.push_back(TileKind('I', 1));
	t1.push_back(TileKind('Z', 1));
	t1.push_back(TileKind('Z', 1));
	t1.push_back(TileKind('A', 1));
	t1.push_back(TileKind('R', 1));
	t1.push_back(TileKind('D', 1));

    Move m1 = Move(t1, 7, 7, Direction::ACROSS);
    b.place(m1);
}

void place_concave_words(Board &b) {
	vector<TileKind> t1;
    t1.push_back(TileKind('A', 1));
    t1.push_back(TileKind('U', 1));
	t1.push_back(TileKind('N', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('Y', 1));
    Move m1 = Move(t1, 7, 7, Direction::ACROSS);
    b.place(m1);

	vector<TileKind> t2;
    t2.push_back(TileKind('B', 1));
    t2.push_back(TileKind('E', 1));
    t2.push_back(TileKind('R', 1));
    Move m2 = Move(t2, 5, 7, Direction::DOWN);
    b.place(m2);

	vector<TileKind> t3;
    t3.push_back(TileKind('A', 1));
    t3.push_back(TileKind('N', 1));
    t3.push_back(TileKind('L', 1));
	t3.push_back(TileKind('E', 1));
	t3.push_back(TileKind('R', 1));
    Move m3 = Move(t3, 5, 10, Direction::DOWN);
    b.place(m3);

	vector<TileKind> t4;
    t4.push_back(TileKind('I', 1));
    Move m4 = Move(t4, 6, 9, Direction::DOWN);
    b.place(m4);
}

class AnchorTest : public testing::Test {
protected:
	AnchorTest() {}
	virtual ~AnchorTest() {}
	size_t hand_size = 7;
	bool anchor_lookup(const vector<Board::Anchor> a, Board::Anchor anchor);
};

bool AnchorTest::anchor_lookup(const vector<Board::Anchor> a, Board::Anchor anchor) {
	bool found = false;
	for(size_t i=0; (i<a.size() && !found); ++i) {
		if (
		a[i].position == anchor.position &&
		a[i].direction == anchor.direction &&
		a[i].limit == anchor.limit )
			found = true;
	}
	return found;
}

TEST_F(AnchorTest, start) {
	Board b = Board::read("config/standard-board.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7, 7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7, 7), Direction::DOWN, 7)));
}

TEST_F(AnchorTest, weird_start) {
	Board b = Board::read("config/board-weird-start.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2, 8), Direction::ACROSS, 8)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2, 8), Direction::DOWN, 2)));
}

TEST_F(AnchorTest, top_right_start) {
	Board b = Board::read("config/board-tr-start.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0, 14), Direction::ACROSS, 14)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0, 14), Direction::DOWN, 0)));
}

TEST_F(AnchorTest, top_left_start) {
	Board b = Board::read("config/board-tl-start.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0, 0), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0, 0), Direction::DOWN, 0)));
}

TEST_F(AnchorTest, bottom_right_start) {
	Board b = Board::read("config/board-br-start.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14, 14), Direction::ACROSS, 14)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14, 14), Direction::DOWN, 14)));
}

TEST_F(AnchorTest, bottom_left_start) {
	Board b = Board::read("config/board-bl-start.txt");
	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 2);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14, 0), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14, 0), Direction::DOWN, 14)));
}

TEST_F(AnchorTest, simple_word) {
	Board b = Board::read("config/standard-board.txt");
	
	place_simple_word(b);

	vector<Board::Anchor> a = b.get_anchors();

	//b.print(cout);

	EXPECT_EQ(a.size(), 12);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 7))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::DOWN, 7))); 
}

TEST_F(AnchorTest, two_words_1) {
	Board b = Board::read("config/standard-board.txt");
	place_two_words(b);	
	//b.print(cout);

	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 18);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,7), Direction::DOWN, 4))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::DOWN, 5)));		
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::DOWN, 7))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 0))); 	
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::DOWN, 5))); 	
}

TEST_F(AnchorTest, two_words_2) {
	Board b = Board::read("config/standard-board.txt");
	
	vector<TileKind> t1;
    t1.push_back(TileKind('H', 1));
    t1.push_back(TileKind('I', 1));

    Move m1 = Move(t1, 7, 7, Direction::ACROSS);
    b.place(m1);

	vector<TileKind> t2;
    t2.push_back(TileKind('C', 1));
    t2.push_back(TileKind('E', 1));

    Move m2 = Move(t2, 8, 8, Direction::DOWN);
    b.place(m2);

	//b.print(cout);

	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 18);
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 6)));		
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,9), Direction::DOWN, 7))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,8), Direction::ACROSS, 8)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,7), Direction::DOWN, 0))); 	
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 7))); 	
}

TEST_F(AnchorTest, long_word) {
	Board b = Board::read("config/standard-board.txt");
	place_long_word(b);	

	//b.print(cout);

	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 34); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,14), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,14), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,13), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,13), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,12), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,12), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,11), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,10), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,10), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,9), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,7), Direction::DOWN, 6))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 7))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,7), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,10), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,10), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,11), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,12), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,12), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,13), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,13), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,14), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,14), Direction::DOWN, 0))); 
}

TEST_F(AnchorTest, xtra_long_word) {
	Board b = Board::read("config/standard-board.txt");
	
	vector<TileKind> t1;
    t1.push_back(TileKind('A', 1));
    t1.push_back(TileKind('B', 1));
	t1.push_back(TileKind('S', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('R', 1));
	t1.push_back(TileKind('A', 1));
	t1.push_back(TileKind('C', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('I', 1));
	t1.push_back(TileKind('O', 1));
	t1.push_back(TileKind('N', 1));
	t1.push_back(TileKind('I', 1));
	t1.push_back(TileKind('S', 1));
	t1.push_back(TileKind('T', 1));
	t1.push_back(TileKind('S', 1));

    Move m1 = Move(t1, 0, 7, Direction::DOWN);
    b.place(m1);

	//b.print(cout);

	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 60); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(1,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(1,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(3,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(3,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(12,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(12,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(13,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(13,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(14,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(13,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(13,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(12,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(12,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(3,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(3,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(2,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(1,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(1,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(0,8), Direction::DOWN, 0))); 
}

TEST_F(AnchorTest, concave) {
	Board b = Board::read("config/standard-board.txt");
	place_concave_words(b);

	//b.print(cout);

	vector<Board::Anchor> a = b.get_anchors();

	EXPECT_EQ(a.size(), 42); // failing - should be 44 when I draw it out?
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,7), Direction::DOWN, 4))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,8), Direction::DOWN, 5)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,9), Direction::DOWN, 5))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,10), Direction::ACROSS, 2)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(4,10), Direction::DOWN, 4))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,11), Direction::DOWN, 5))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,11), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,12), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,12), Direction::DOWN, 7))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,11), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,11), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,11), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,11), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,10), Direction::ACROSS, 10)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(11,10), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,9), Direction::ACROSS, 9)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(10,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,9), Direction::ACROSS, 1)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,9), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::ACROSS, 0)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,8), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,7), Direction::ACROSS, 7)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(9,7), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(8,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(7,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(6,6), Direction::DOWN, 0))); 
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::ACROSS, 6)));
	EXPECT_TRUE(anchor_lookup(a, Board::Anchor(Board::Position(5,6), Direction::DOWN, 5))); 
}


class ComputerPlayerTest : public testing::Test {
protected:
	ComputerPlayerTest() {}
	virtual ~ComputerPlayerTest() {}
	void crappy_print_hand();
	void test_pts(PlaceResult res, unsigned int exp_pts);
};

void ComputerPlayerTest::test_pts(PlaceResult res, unsigned int exp_pts) {
	bool pass = false;
	if(res.points == exp_pts) {
		pass = true;		
	} else if(res.points == exp_pts+50) {
		pass = true;
	}

	if(!pass) {
		std::cerr << "TEST FAILED: res.points = " << res.points << std::endl;
		std::cerr << "    EXPECTED: " << exp_pts << " or " << exp_pts+50 << std::endl;
	}
	EXPECT_TRUE(pass);
}


TEST_F(ComputerPlayerTest, empty_no_multipliers_no_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	vector<TileKind> t;
    t.push_back(TileKind('A', 3));
    t.push_back(TileKind('B', 1));
	t.push_back(TileKind('F', 2));
	t.push_back(TileKind('T', 1));
	t.push_back(TileKind('N', 3));
	t.push_back(TileKind('O', 7));
	t.push_back(TileKind('S', 4));

	cpu.add_tiles(t);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 8 8 - batons
	test_pts(res, 19);
}

// Multipliers make no difference from the first move... so have a free one :)
TEST_F(ComputerPlayerTest, empty_with_multipliers_no_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	vector<TileKind> t;
    t.push_back(TileKind('A', 3));
    t.push_back(TileKind('B', 1));
	t.push_back(TileKind('F', 2));
	t.push_back(TileKind('T', 1));
	t.push_back(TileKind('N', 3));
	t.push_back(TileKind('O', 7));
	t.push_back(TileKind('S', 4));

	cpu.add_tiles(t);


	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 8 8 - batons
	test_pts(res, 19);
}

TEST_F(ComputerPlayerTest, empty_no_multipliers_one_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	vector<TileKind> t;
    t.push_back(TileKind('A', 3));
    t.push_back(TileKind('B', 1));
	t.push_back(TileKind('F', 2));
	t.push_back(TileKind('T', 1));
	t.push_back(TileKind('N', 3));
	t.push_back(TileKind('?', 1));
	t.push_back(TileKind('S', 4));

	cpu.add_tiles(t);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 8 8 - faints
	test_pts(res, 14);
}

TEST_F(ComputerPlayerTest, empty_no_multipliers_two_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	vector<TileKind> t;
    t.push_back(TileKind('?', 1));
    t.push_back(TileKind('B', 1));
	t.push_back(TileKind('?', 1));
	t.push_back(TileKind('T', 1));
	t.push_back(TileKind('N', 3));
	t.push_back(TileKind('O', 7));
	t.push_back(TileKind('S', 4));

	cpu.add_tiles(t);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 8 8 - bastion
	test_pts(res, 18);
}

TEST_F(ComputerPlayerTest, simple_no_multipliers_no_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_simple_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 9 5 - ho in batons
	test_pts(res, 31);
}

TEST_F(ComputerPlayerTest, simple_no_multipliers_one_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_simple_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 9 7 - ho in confab
	test_pts(res, 29);
}

TEST_F(ComputerPlayerTest, simple_with_multipliers_no_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_simple_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 7 6 - ah si boast
	test_pts(res, 40);
}

TEST_F(ComputerPlayerTest, simple_with_multipliers_one_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_simple_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 6 10 | hit oaten
	test_pts(res, 38);
}

TEST_F(ComputerPlayerTest, two_words_no_multipliers_no_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_two_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 2 7 | na sa batons
	test_pts(res, 28);
}

TEST_F(ComputerPlayerTest, two_words_no_multipliers_one_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_two_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 4 9 | an at fontina
	test_pts(res, 24);
}

TEST_F(ComputerPlayerTest, two_words_with_multipliers_no_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_two_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 6 5 - sonata
	test_pts(res, 39);
}

TEST_F(ComputerPlayerTest, two_words_with_multipliers_one_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_two_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 6 10 | hit oaten
	test_pts(res, 38);
}

TEST_F(ComputerPlayerTest, long_no_multipliers_no_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_long_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 2));
    t0.push_back(TileKind('B', 3));
	t0.push_back(TileKind('K', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);		
	// 7 7 - ob al si boas
	test_pts(res, 32);
}

TEST_F(ComputerPlayerTest, long_with_multipliers_no_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_long_word(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 2));
    t0.push_back(TileKind('B', 3));
	t0.push_back(TileKind('K', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 9 6 - bb lo it sabot
	test_pts(res, 47);
}

TEST_F(ComputerPlayerTest, concave_words_no_multipliers_no_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_concave_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 10 10 | se or sofa
	test_pts(res, 29);
}

TEST_F(ComputerPlayerTest, concave_words_no_multipliers_one_blank) {
	Board b = Board::read("config/board0.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_concave_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 5 7 | ab ne jaunty or banjo
	test_pts(res, 37);
}

TEST_F(ComputerPlayerTest, concave_words_with_multipliers_no_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_concave_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('S', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 11 12 | rf fatso
	test_pts(res, 51);
}

TEST_F(ComputerPlayerTest, concave_words_with_multipliers_one_blank) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 7);

	place_concave_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
    t0.push_back(TileKind('B', 1));
	t0.push_back(TileKind('F', 2));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('N', 3));
	t0.push_back(TileKind('O', 7));
	t0.push_back(TileKind('?', 1));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 5 7 | ab ne jaunty or banjo
	test_pts(res, 57);
}

TEST_F(ComputerPlayerTest, stress_test) {
	Board b = Board::read("config/standard-board.txt");	
	Dictionary d = Dictionary::read(DICT_PATH);
	ComputerPlayer cpu("cpu", 10);

	place_concave_words(b);
	//b.print(cout);

	vector<TileKind> t0;
    t0.push_back(TileKind('A', 3));
	t0.push_back(TileKind('?', 1));
	t0.push_back(TileKind('T', 1));
	t0.push_back(TileKind('M', 3));
	t0.push_back(TileKind('?', 1));
	t0.push_back(TileKind('S', 4));
	t0.push_back(TileKind('Z', 7));
	t0.push_back(TileKind('P', 2));
	t0.push_back(TileKind('D', 3));
	t0.push_back(TileKind('F', 4));

	cpu.add_tiles(t0);

	Move m = cpu.get_move(b, d);
	PlaceResult res = b.test_place(m);
	// 3 10 | ma el se flamines
	test_pts(res, 57);
}

