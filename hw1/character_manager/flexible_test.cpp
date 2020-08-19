#include "flexible.h"
#include <iostream>
#include <string.h>

// While debugging, change the buffer size by redefining it here.
#undef BUFFER_SIZE
#define BUFFER_SIZE 20

using namespace std;


// This is the fragmentation exercise.
int main(int argc, char* argv[]) {
    FlexibleCharacterManager manager;

    // Sample driver code to test your FlexibleCharacterManager.
    char* word1 = manager.alloc_chars(3);
    if (word1 != nullptr) {
        strncpy(word1, "in ", 3);
        cout << word1 << endl;
    }

    // Do not want to overwrite start of buffer, so save in a new address.
    char* word2 = manager.alloc_chars(7);
    if (word2 != nullptr) {
        strncpy(word2, "French ", 7);

        // You can check the contents of the buffer and the actually address of
        // the buffer (i.e. word1 and word2) using GDB. No need to print. What
        // would go wrong if there are no null characters and we tried this?
        cout << word2 << endl;
        cout << word1 << endl;
    }

    char* word3 = manager.alloc_chars(7);
    if (word3 != nullptr) {
        strncpy(word3, "chapeau", 7);
        cout << word3 << endl;
        cout << word1 << endl;
    }

    // Good practice would be to set word1 to nullptr, but we can use this to
    // help debug the flexible character manager.
    manager.free_chars(word1);

    char* word4 = manager.alloc_chars(3);
    if (word4 != nullptr) {
        strncpy(word4, "top", 3);

        // This should print true. Why?
        cout << boolalpha << (word1 == word4) << endl;
        cout << word4 << endl;
    }

    manager.free_chars(word2);

    word2 = manager.alloc_chars(8);

    // This request should fail and the following statement should print true.
    cout << boolalpha << (word2 == nullptr) << endl;

    if (word2) {
        strncpy(word2, "sombrero", 8);
    }

    word2 = manager.alloc_chars(3);
    if (word2) {
        strncpy(word2, "hat", 3);
    }

    // This will print the contents of the first 20 characters of the buffer.
    // If the buffer size has been changed to 20, this is the same as the
    // fragmentation exercise.
    for (int i = 0; i < 20; i++) {
        if (word4[i] == '\0') {
            word4[i] = '0';  // prints 0 for null character
        }
        cout << word4[i];
    }
    cout << endl;

    return 0;
}
