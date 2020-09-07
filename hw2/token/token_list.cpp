#include "token_list.h"
#include <stdexcept>


size_t TokenList::size() const {
    return this->_size;
}

// TODO: implement the TokenList methods.

Token& TokenList::at(size_t index) {
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    // TODO: complete this function here
}

const Token& TokenList::at(size_t index) const {
    if (this->size() == 0) {
        throw std::out_of_range("no items");
    }

    // TODO: complete this function here
}


std::ostream& operator<<(std::ostream& out, const TokenList& list)  {
    out << "{";
    std::shared_ptr<TokenList::Item> cursor = list.head;
    if (cursor != nullptr) {
        for (size_t i = 0; i < list.size() - 1; i++) {
            out << cursor->value << ", ";
            cursor = cursor->next;
        }
        out << cursor->value;
    }
    return out << "}";
}
