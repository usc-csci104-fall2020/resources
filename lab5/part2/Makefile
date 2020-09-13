# In this Makefile we'll introduce the concepts of Makefile automatic variables
# Make will simply substitute these variables with the corresponding string
# $< - first dependency
# $^ - all dependencies
# $@ - target name (whatever's before colon)

# Let's declare some variables
CC       = g++
BIN_DIR  = bin
LIB_DIR  = lib
SRC_DIR  = src
CPPFLAGS = -Wall -g -I$(LIB_DIR)
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread
TARGETS = $(BIN_DIR)/player.o $(BIN_DIR)/healer.o $(BIN_DIR)/tank.o $(BIN_DIR)/fighter.o $(BIN_DIR)/inventory.o

all: $(TARGETS)
	-@echo "--- All Built!---"

# $^ is an auto variable that means "all dependencies"
# IMPORTANT: $(GTEST_LL) needs to come *after* the source files
$(BIN_DIR)/RPGTest: $(SRC_DIR)/test.cpp $(TARGETS)
	$(CC) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

# $< is an auto variable that means "the first dependency", which is player.cpp here.
$(BIN_DIR)/player.o: $(SRC_DIR)/player.cpp $(LIB_DIR)/player.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/fighter.o: $(SRC_DIR)/fighter.cpp $(LIB_DIR)/fighter.h $(LIB_DIR)/player.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/healer.o: $(SRC_DIR)/healer.cpp $(LIB_DIR)/healer.h $(LIB_DIR)/player.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/tank.o: $(SRC_DIR)/tank.cpp $(LIB_DIR)/tank.h $(LIB_DIR)/player.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

$(BIN_DIR)/inventory.o: $(SRC_DIR)/inventory.cpp $(LIB_DIR)/inventory.h $(BIN_DIR)/.dirstamp 
	$(CC) $(CPPFLAGS) -c $< -o $@

# Rule to ensure the $(BIN_DIR) directory exist or it'll create it.
# $@ is an auto variable that means "target name", which is $(BIN_DIR)/.dirstamp in this case
$(BIN_DIR)/.dirstamp:
	-@mkdir -p $(BIN_DIR)
	-@touch $@

.PHONY: clean tests

tests: clean $(BIN_DIR)/RPGTest
	-@$(BIN_DIR)/RPGTest
	-@echo "--- All Tested!---"

clean:
	-@rm -rf $(BIN_DIR)
	-@echo "--- All Clean!---"
