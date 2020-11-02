#include "hashtable.h"
#include <iostream>

using namespace std;

#define A 54059 
#define B 76963 
#define C 86969 

/**
Hash function for the CS104 hash table.
*/
unsigned hash_str(const char* s)
{
   unsigned h = 31;
   while (*s) {
     h = (h * A) ^ (s[0] * B);
     s++;
   }
   return h % C; 
}

/**
Creates a hash table of the given input size. Creates the array and vectors used for the hash table.
*/
HashTable::HashTable(int size) {
	this->size = size;
	data.resize(size);
}

/**
No clean up necessary if we are using smart pointers!
*/
HashTable::~HashTable() {

}

/**
Inserts key and value pair to HashTable, unless it is a duplicate key.
@param key is the key.
@param value is the value.
Note: insert should do nothing if the key already exists in the hash table.
*/
void HashTable::insert(string str) {
	unsigned hash = hash_str(str.c_str());
	hash = hash % size;
	// TODO
}

/**
Finds if key exists and returns true if it does.
@param key is the key to find.
*/
bool HashTable::find(string key) {
	unsigned hash = hash_str(key.c_str());
	hash = hash % size;
	// TODO
}

/**
Removes key if it exists.
@param key is key to remove.
Note: remove should do nothing if the key does not exist in the hash table.
*/
void HashTable::remove(string str) {
	unsigned hash = hash_str(str.c_str());
	hash = hash % size;
	// TODO
}

void HashTable::print() {
	for(int i = 0; i < size; i++) {
		cout << i << ": " << (data[i] == nullptr ? " " : *data[i]) << endl;
	}
}
