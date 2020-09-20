#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <unordered_set>
#include <string>


class Dictionary {
public:
    // Reads each word from file, adds it to a Dictionary, and returns the Dictionary.
    static Dictionary read(const std::string& file_path);

    bool is_word(const std::string& word) const;

private:
    std::unordered_set<std::string> words;
};

#endif
