#ifndef PLACE_RESULT_H
#define PLACE_RESULT_H

#include <vector>
#include <string>


struct PlaceResult {
    bool valid;
    std::string error;
    std::vector<std::string> words;
    unsigned int points;

    PlaceResult(const std::string& error)
        : valid(false)
        , error(error) {}

    PlaceResult(const std::vector<std::string>& words, unsigned int points)
        : valid(true)
        , words(words)
        , points(points) {}
};

#endif
