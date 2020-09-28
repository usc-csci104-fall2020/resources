all: pokedex

pokedex: main.cpp llist.h
	g++ -g -Wall -std=c++11 main.cpp -o pokedex
	valgrind --leak-check=yes ./pokedex
