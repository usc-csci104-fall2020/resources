#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef struct CharacterBlock {

    // The starting index of the block we're allocating in the buffer
    char* address;

    // The number of characters allocated to the memory block
    size_t size;

} CharacterBlock;

// Write a comparator that will return true if and only if the
// first CharacterBlock has a smaller physical address

struct CharBlockComp { 
   bool operator() (const CharacterBlock& left, const CharacterBlock& right) const 
    { return left.address < right.address;} 
}; 




int main(){
    char buffer[1000];
    vector<CharacterBlock> a(3);
    
   a[0].address = buffer + 700;
   a[0].size = 20;
   a[1].address = buffer;
   a[1].size = 100;
   a[2].address = buffer+558;
   a[2].size = 75;
    
    
    
    for (int i = 0; i < 3; i++ ) {
        cout << "CharBlock " << i << " starting address: " << static_cast<const void *> (a[i].address) << endl;
    } 
    cout << endl;
    
    CharBlockComp comp;
    std::sort(a.begin(), a.end(), comp);
    
    for (int i = 0; i < 3; i++ ) {
        cout << "CharBlock " << i << " starting address: " << static_cast<const void *> (a[i].address) << endl;
    } 
    
}
