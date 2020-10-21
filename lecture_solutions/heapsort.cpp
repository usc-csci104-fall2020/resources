#include <iostream> 
#include <queue> 
#include <stdlib.h>
using namespace std; 

int main () 
{
  

  priority_queue<int, vector<int>, greater<int>> pq;
  // how to get a random integer between 0 and 999
 for (int i = 0; i < 10; i++){
      int k = rand()%1000;
      pq.push(k);
}
    
  
  cout<< "Sorting elements..." << endl;
 // print integers in order from smallest to largest
 while(!pq.empty()){
     cout << pq.top() << " ";
     pq.pop();
     
 }   
 cout << endl;
}
