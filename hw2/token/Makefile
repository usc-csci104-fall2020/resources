COMPILER=g++
OPTIONS=-g -std=c++17 -Wall -Wextra
COMPILE=$(COMPILER) $(OPTIONS)

all: token_list.o token_stack.o token.o

token_stack_tests: token_stack_tests.cpp token_stack.o token_list.o token.o
	$(COMPILE) $^ -o $@
	./$@

token_list_tests: token_list_tests.cpp token_list.o token.o
	$(COMPILE) $^ -o $@
	./$@

token_stack.o: token_stack.cpp token_stack.h
	$(COMPILE) -c $< -o $@

token_list.o: token_list.cpp token_list.h
	$(COMPILE) -c $< -o $@

token.o: token.cpp token.h
	$(COMPILE) -c $< -o $@

clean:
	rm -f *.o token_list_tests token_stack_tests

.PHONY: all test clean
