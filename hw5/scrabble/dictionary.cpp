#include "dictionary.h"
#include "exceptions.h"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <iostream>
#include <vector>
#include <memory>

using namespace std;


string lower(string str) {
    transform(str.cbegin(), str.cend(), str.begin(), ::tolower);
    return str;
}

// Implemented for you to read dictionary file and 
// construct dictionary trie graph for you
Dictionary Dictionary::read(const std::string& file_path) {
    ifstream file(file_path);
    if (!file) {
        throw FileException("cannot open dictionary file!");
    }
    std::string word;
    Dictionary dictionary;
    dictionary.root = make_shared<TrieNode>();

    while (!file.eof()) {
        file >> word;
        if (word.empty()) {
            break;
        }
        dictionary.add_word(lower(word));
    }

    return dictionary;
}



bool Dictionary::is_word(const string& word) const {
    shared_ptr<TrieNode> cur = find_prefix(word);
    if (cur == nullptr)
        return false;
    // HW5: IMPLEMENT HERE
    // return whether the word is a valid
    // word in the dictionary
}

shared_ptr<Dictionary::TrieNode> Dictionary::find_prefix(const string& prefix) const {
    shared_ptr<TrieNode> cur = root;
    // This is a for each loop in C++. It is equivalent to the following:
    // for (int i = 0; i < prefix.length(); i++) {
    //      char letter = prefix[i];
    for (char letter : prefix) {
        // HW5: IMPLEMENT HERE
        // if there is no child of cur using `letter`
        //     return nullptr
        // set cur to the child of cur that uses `letter`
    }
    return cur;
}


// Implemented for you to build the dictionary trie
void Dictionary::add_word(const string& word) {
    shared_ptr<TrieNode> cur = root;
    for (char letter : word) {
        if (cur->nexts.find(letter) == cur->nexts.end()) {
            cur->nexts.insert({letter, make_shared<TrieNode>()});
        }
        cur = cur->nexts.find(letter)->second;
    }
    cur->is_final = true;
}


vector<char> Dictionary::next_letters(const std::string& prefix) const {
    shared_ptr<TrieNode> cur = find_prefix(prefix);
    vector<char> nexts;
    if (cur == nullptr)
        return nexts;
    // HW5: IMPLEMENT HERE
    // add all letters in cur->nexts to `nexts`
    return nexts;
}
