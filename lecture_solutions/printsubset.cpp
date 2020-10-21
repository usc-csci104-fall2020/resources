#include <iostream>
#include <vector>
#include <string>
using namespace std;


// Implement this function recursively.
// You may use helper functions.

void print_subsetHelper(vector<string> stringSet, vector<string> subset, int k, int indx){
    if (subset.size()== k){
        for (int i = 0; i < k; i++){
            cout << subset[i] << " ";
        }
        cout << endl;
    } else if (indx == stringSet.size()){
        return;
    } else {
        subset.push_back(stringSet[indx]);
        print_subsetHelper(stringSet,subset, k, indx+1);
        subset.pop_back();
        print_subsetHelper(stringSet,subset, k, indx+1);
    }
}

void print_subsets (vector<string> stringSet, int k){
    vector<string> s;
    print_subsetHelper(stringSet,s, k, 0);
}


int main()
{
    vector<string> s = {"cat", "dog", "rabbit", "robot"};
    print_subsets(s,3);
    return 0;
}
