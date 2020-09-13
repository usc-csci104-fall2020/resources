all: tests

tests: FORCE Person_Tests
	 ./Person_Tests

FORCE: ;

Person_Tests: tests.cpp Person.o 
	g++ -Wall -std=c++11 -g Person.o tests.cpp -o Person_Tests

Person.o: Person.h Person.cpp
	g++ -Wall -std=c++11 -g -c Person.cpp -o Person.o

clean:
	rm Person_Tests
	rm Person.o