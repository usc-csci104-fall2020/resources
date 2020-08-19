#include "flexible.h"

using namespace std;


// The constructor creates a unique_ptr to a dynamically allocated array of two
// CharacterBlocks using the initialization list syntax. No need to change this
// unless you add fields to the FlexibleCharacterManager.
FlexibleCharacterManager::FlexibleCharacterManager() : blocks(new CharacterBlock[2] {}) {}

char* FlexibleCharacterManager::alloc_chars(size_t n) {
	// TODO: your implementation here
}

void FlexibleCharacterManager::free_chars(char* p) {
	// TODO: your implementation here
}
