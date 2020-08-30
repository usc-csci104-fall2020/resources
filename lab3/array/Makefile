all: tests

tests: FORCE array_tests
	valgrind --leak-check=yes ./array_tests

FORCE: ;

array_tests: array_tests.cpp array.o
	g++ -Wall -std=c++11 -g array.o array_tests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o array_tests

array.o: array.h array.cpp
	g++ -Wall -std=c++11 -g -c array.cpp -o array.o

clean:
	rm array_tests
	rm array.o
