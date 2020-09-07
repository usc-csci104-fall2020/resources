#include "token_list.h"
#include <iostream>
#include <string>

using namespace std;


int main() {
    TokenList test;

    test.push_back(Token(TokenKind::NUMBER, 1));
    test.push_back(Token(TokenKind::NUMBER, 2));
    test.push_back(Token(TokenKind::NUMBER, 3));
    cout << "After push back: " << test << endl;

    test.reverse();
    cout << "After reverse: " << test << endl;

    TokenList test2 = test;
    cout << "Original after copy: " << test << endl;
    cout << "Copy after copy: " << test2 << endl;

    test.remove(0);
    cout << "Original after removing 1: " << test << endl;
    cout << "Copy after removing 1 from original: " << test2 << endl;

    test.at(1) = Token(TokenKind::NUMBER, 2);
    cout << "After replace 3 with 3: " << test << endl;

    return 0;
}
