#include "token.h"


// Convenience method for debugging.
std::ostream& operator<<(std::ostream& out, const Token& token)  {
    if (token.kind == TokenKind::NUMBER) {
        return out << token.value;
    } else {
        return out << (char)token.kind;
    }
}
