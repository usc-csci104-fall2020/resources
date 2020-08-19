#ifndef MANAGER_H
#define MANAGER_H

#include <cstddef>

#define BUFFER_SIZE 4096


// This enforces a correct implementation of the Simple and Flexible character
// managers. Don't worry about the syntax, you'll learn more about polymorphism
// later in the semester.
class AbstractCharacterManager {
public:
    virtual char* alloc_chars(size_t n) { return nullptr; }
    virtual void free_chars(char* p) {}
};

#endif
