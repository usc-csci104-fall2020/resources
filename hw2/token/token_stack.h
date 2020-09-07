#ifndef TOKEN_STACK_H
#define TOKEN_STACK_H

#include "token_list.h"


class TokenStack {
public:
    // TODO: return how many tokens are in the stack
    size_t size() const;

    // TODO: check whether the stack is empty
    bool empty() const;

    // TODO: push a new token on top of the stack.
    void push(const Token& t);

    // TODO: return the top value on the stack.
    // The starter code throws an exception for attempting 
    // to get the top of an empty stack for you
    const Token& top() const;

    // TODO: remove the top element on the stack.
    // If the stack is empty, this function should do nothing
    void pop();

    // TODO: reverse the contents of the stack.
    void reverse();

    // Help debugging
    friend std::ostream& operator<<(std::ostream& out, const TokenStack& stack);

private:
    // Our internal container for our data. Using the TokenList this way is
    // called composition; we are building functionality around an internal
    // data structure that offers its own members and methods.
    TokenList list;
};

#endif
