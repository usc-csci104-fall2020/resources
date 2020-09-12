COMPILER=g++
OPTIONS=-g -std=c++17 -Wall -Wextra -I../token/
COMPILE=$(COMPILER) $(OPTIONS)


arithmetic: arithmetic.cpp ../token/token_stack.o ../token/token_list.o ../token/token.o
	$(COMPILE) $^ -o arithmetic

../token/token_stack.o:
	make -C ../token/ token_stack.o

../token/token_list.o:
	make -C ../token/ token_list.o

../token/token.o:
	make -C ../token/ token.o

clean:
	rm -f *.o arithmetic ../token/token_stack.o ../token/token_list.o ../token/token.o

.PHONY: all test clean