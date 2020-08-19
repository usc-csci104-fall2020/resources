#ifndef FLEXIBLE_H
#define FLEXIBLE_H

#include "manager.h"
#include <memory>

// Make sure you read through the directions for this section before you start
// code, as there are significant differences between this and the Simple
// version of the manager.


// Container for each allocation we make
typedef struct CharacterBlock {

    // The starting index of the block we're allocating in the buffer
    char* address;

    // The number of characters allocated to the memory block
    size_t size;

} CharacterBlock;


class FlexibleCharacterManager : public AbstractCharacterManager
{
public:
    // We need to provide a constructor
    FlexibleCharacterManager();

    // There's no need for a destructor because the only non-primitive is destroyed by unique_ptr

    // Implement our required methods
    virtual char* alloc_chars(size_t size);
    virtual void free_chars(char* address);

private:
    // Instantiate the buffer with the size defined in manager.h and zero
    char buffer[BUFFER_SIZE] {};

    // Sorted array of CharacterBlocks
    std::unique_ptr<CharacterBlock[]> blocks;

    // Memory block array size
    size_t blocks_size = 2;

    // Memory blocks actually allocated
    size_t blocks_in_use = 0;

    // You may add additional members here if you wish
};

#endif
