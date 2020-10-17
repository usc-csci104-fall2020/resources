#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_set>
#include <string>
#include <map>
#include <memory>
#include <vector>



class Dictionary {
public:
    struct TrieNode {
        // when a node in trie is created 
        // initialized to not be for a valid word
        // in the dictionary
        bool is_final = false;
        std::map<char, std::shared_ptr<TrieNode>> nexts;
    };

    /*
    Creates a dictionary based on the specified config file

    Adds all the words into the Trie datastructures.
    */
    static Dictionary read(const std::string& file_path);

    /*
    Returns whether `word` is in the dictionary or not. 
    */
    bool is_word(const std::string& word) const;

    /*
    This function returns a vector of letters that could possibly follow prefix. 

    If a letter is a key in a node's `nexts`, it should be possible to make a word using it. 
    */
    std::vector<char> next_letters(const std::string& prefix) const; // Used for testing

    /*
    Returns root
    */
    std::shared_ptr<TrieNode> get_root() const {return root;}; // Used for testing

    /*
    This function returns the node associated with prefix.

    This method starts with the current node as the root node (a.k.a the node associated with the empty string "").
    The algorithm then iterates through each letter in prefix and for each letter
        It moves the current node pointer to the child associated with that letter.
        i.e. The node pointer in the current node's `nexts` keyed by the letter
    It then returns that node.
    If at any point the node cannot be found, return nullptr. 
    */
    std::shared_ptr<TrieNode> find_prefix(const std::string& prefix) const; // Used for testing

private:
    std::shared_ptr<TrieNode> root;

    void add_word(const std::string& word);
};

#endif
