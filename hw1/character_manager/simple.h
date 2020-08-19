#ifndef SIMPLE_MANAGER_H
#define SIMPLE_MANAGER_H

#include "manager.h"

class SimpleCharacterManager : AbstractCharacterManager {
public:
    // Default constructor and destructor suffice

    // Implement our required methods
    virtual char* alloc_chars(size_t size);
    virtual void free_chars(char* address);

private:
    // Instantiate the buffer with the size defined in manager.h and zero
    char buffer[BUFFER_SIZE] {};

    // The first available position is at the
    char* first_available_address = buffer;
};

#endif
