CXX = g++
CXXFLAGS = -g3 -O0 -Wall --std=c++11

all: game_student1 game_student2

game_student1: game_of_pointers_student1.cpp 
	$(CXX) $(CXXFLAGS) game_of_pointers_student1.cpp -o game_student1

game_student2: game_of_pointers_student2.cpp 
	$(CXX) $(CXXFLAGS) game_of_pointers_student2.cpp -o game_student2

test: test_game1 test_game2

test_game1: game_student1
	@echo "******************************************************************"
	@echo "                   Testing Student 1's Game"
	@echo "******************************************************************"
	./game_student1 input1.txt output1-stu1.txt
	@diff -s  output1.check output1-stu1.txt

	./game_student1 input2.txt output2-stu1.txt
	@diff -s  output2.check output2-stu1.txt

	./game_student1 input3.txt output3-stu1.txt
	@diff -s  output3.check output3-stu1.txt

	@echo "Passed all tests!"
	@echo ""

test_game2: game_student2
	@echo "******************************************************************"
	@echo "                   Testing Student 2's Game"
	@echo "******************************************************************"
	./game_student2 input1.txt output1-stu2.txt
	@diff -s  output1.check output1-stu2.txt

	./game_student2 input2.txt output2-stu2.txt
	@diff -s  output2.check output2-stu2.txt

	./game_student2 input3.txt output3-stu2.txt
	@diff -s  output3.check output3-stu2.txt

	@echo "Passed all tests!"
	@echo ""

clean: 
	rm -rf output*.txt game_student1 game_student2

.PHONY: test test_game1 test_game2 clean