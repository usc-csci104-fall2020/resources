#ifndef Sudoku_H
#define Sudoku_H

class Sudoku {

public:
	Sudoku(int puzzle[9][9]);
	~Sudoku();

	void solve(); // solves the puzzle
	void print(); // prints the puzzle
	void verify(); // verifies the puzzle is valid

private:
	bool isValid(int row, int col);
	bool solveHelper(int row, int col);
	int board[9][9];

	// add extra helper functions here
};

#endif