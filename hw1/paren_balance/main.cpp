#include <iostream>
#include <string>

using namespace std;

// Implement below
bool are_paren_balanced(const string& expression);

// We have suggested a helper method, but feel free to write whatever you see fit
bool are_paren_balanced(const string& expression, size_t& i, char expected_closing);

// Do not change this method
int main(int argc, char* argv[]) {

    // Check if an expression has been passed to the program
    if (argc != 2) {
        cerr << "error: expected expression to check!" << endl;
        return -1;
    }

    // The second argument is the expression string in the format specified and
    // promised in the assignment page. You do not need to do any error checking
    // except for checking the parentheses.
    string expression(argv[1]);
    if (are_paren_balanced(expression)) {
        cout << "correct" << endl;
    } else {
        cout << "incorrect" << endl;
    }

    return 0;
}

// Some notes:
// - This method must be implemented recursively.
// - When debugging, make sure to output to cerr rather than cout. This will
//   prevent any leftover debug statements from confusing the automated
//   grading and will make sure output is guaranteed to be written to the
//   terminal in case your program crashes.
bool are_paren_balanced(const string& expression) {
    // TODO: your code here
}

// Add any additional function implementations here.
//
// If you want to use the suggested helper method, you'll have to write its
// definition here.
