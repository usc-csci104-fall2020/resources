#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <vector>
#include <memory>

/**
Hash Table for CS104 lab 12. Only stores strings.
*/
class HashTable {
public:
	HashTable(int size);
	~HashTable();

	void  insert(std::string str);
	bool  find(std::string str);
	void  remove(std::string str);
	void  print();

private:
	// Data is a vector of smart pointers to strings
	std::vector<std::unique_ptr<std::string>> data;
	int size;
};

#endif
