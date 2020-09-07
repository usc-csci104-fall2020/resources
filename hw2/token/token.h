#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>

// You can ignore the specifics of this file until you get to arithmetic. All
// you need to worry about for now is passing Tokens in and out of your linked
// list and stack implementation.


// An enum is basically a collection of constants that have some additional
// properties, such as compatibility with switch statements. We'll use this
// enum to indicate what kind of token we're dealing with. To refer to a member
// of an enum class, you'd write EnumName::MEMBER_NAME, i.e. TokenKind::NUMBER.
enum class TokenKind {
    INVALID,
    NUMBER,
    LP = '(',
    RP = ')',
    PLUS = '+',
    MINUS = '-',
    TIMES = '*',
    DIVIDE = '/',
};

// A token marks its type in the context of the overall grammar rules. It is
// bundled with any associated data, which in this case is only necessary when
// we tokenize a number.
struct Token {
    TokenKind kind;
    int value;

    // Constructors for convenience
    Token(TokenKind kind, int value) : kind(kind), value(value) {}
    Token(TokenKind kind) : kind(kind), value(0) {}
};

// Output formatting for convenience.
std::ostream& operator<<(std::ostream& out, const Token& token);

#endif
