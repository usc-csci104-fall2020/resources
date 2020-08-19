#include "simple.h"
#include <iostream>
#include <string.h>

using namespace std;


int main(int argc, char* argv[]) {
    SimpleCharacterManager manager;

    char* word1 = manager.alloc_chars(14);

    // Make sure memory was successfully allocated.
    if (word1 != nullptr) {

        // Storing one char at a time is not concise, but it works.
        word1[0] = 'H';
        word1[1] = 'e';
        word1[2] = 'l';
        word1[3] = 'l';
        word1[4] = 'o';
        word1[5] = ' ';
        word1[6] = 'W';
        word1[7] = 'o';
        word1[8] = 'r';
        word1[9] = 'l';
        word1[10] = 'd';
        word1[11] = '!';
        word1[12] = '\n';
        word1[13] = '\0';

        cout << word1 << endl;

        // Hint: you can check address of word1 in the GDB debugger.
        manager.free_chars(word1 + 6);
    }

    char* word2 = manager.alloc_chars(11);
    if (word2) {

        // Old fashioned C-library string copy will automatically copy the null
        // character, so make sure there is space allocated. As we progress, we
        // want to avoid this if we can, but it is better than copying each
        // character.
        strcpy(word2, "moon! Bye.\n");

        // You can check the address of word2 in the GDB debugger.
    }

    if (word1) {
        cout << word1 << endl;
    }

    return 0;
}
