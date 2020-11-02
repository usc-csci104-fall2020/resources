CXX=g++
CXXFLAGS=-g -Wall -std=c++11 
# Uncomment for parser DEBUG
#DEFS=-DDEBUG


all: bst-test

bst-test: bst-test.cpp bst.h avlbst.h
	$(CXX) $(CXXFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o bst-test
