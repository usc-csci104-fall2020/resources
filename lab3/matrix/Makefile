all: tests

tests: FORCE matrix_tests
	valgrind --leak-check=yes ./matrix_tests

FORCE: ;

matrix_tests: matrix_tests.cpp matrix.o
	g++ -Wall -std=c++11 -g matrix.o matrix_tests.cpp -I /usr/include/gtest/ -l gtest -l gtest_main -pthread -o matrix_tests

matrix.o: matrix.h matrix.cpp
	g++ -Wall -std=c++11 -g -c matrix.cpp -o matrix.o

clean:
	rm matrix_tests
	rm matrix.o
