#include "hypercube.h"

using namespace std;


void HyperCube::read(istream& input) {
    // TODO: implement
}

SearchResult HyperCube::search(const string& start) const {
    // TODO: implement

    // Initialize ending node of all 1's.
    std::string end(start.size(), '1');

    // Instantiate priority queue to use for A* algorithm.
    std::priority_queue<Node, std::vector<Node>, NodePriority> unvisited;

    // Initialize the number of expansions used by the algorithm and path.
    size_t expansions = 0;
    std::vector<std::string> path;

    // Add any variables needed for A* algorithm

    // Implement A* algorithm. Remember to add node label strings on the path
    // to the results vector. Order of the strings in the vector matters. Make
    // sure to return a SearchResult object.
}
