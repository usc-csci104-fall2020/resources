all: sudoku

sudoku: sudoku.o main.cpp
	g++ -g -Wall main.cpp sudoku.o -o sudoku

sudoku.o: sudoku.cpp sudoku.h
	g++ -g -Wall -c sudoku.cpp -o sudoku.o

clean:
	-@rm sudoku 
	-@rm sudoku.o