#include "token_stack.h"
#include <stdexcept>


// TODO: return the top value on the stack.
const Token& TokenStack::top() const{
    if (this->empty()) {
        throw std::out_of_range("empty stack");
    }

    // TODO: complete function here
}

// TODO: implement the TokenStack methods.
