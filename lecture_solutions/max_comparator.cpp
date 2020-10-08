
#include <iostream>
#include <vector>
#include <numeric>

using namespace std;

template <typename T, typename comp>
   T mymax(const T& a, const T& b, comp test)
{
   if(test(a,b)) return a;
   return b;
}
   
 struct SizeComp {
      bool operator()(const vector<int>& a, const vector<int>& b) const {
         return a.size() > b.size();
      }
   };
 struct SumComp {
      bool operator()(const vector<int>& a, const vector<int>& b) const {
         int asum = std::accumulate(a.begin(),a.end(),0);
         int bsum = std::accumulate(b.begin(),b.end(),0);
         return asum > bsum;
      }
   };

int main(){
    vector<int> a(10);
    vector<int> b(11);
    
    for (int i = 0; i < 10; i++ ) {
        a[i] = 2*(i+1);
        b[i] = i+1;
    }
    
    b[10] = 11;

    SizeComp more_mem;
    SumComp more_value;
    vector<int> test = mymax(a, b, more_mem);
    // Should print b
    for (int i = 0; i < test.size(); i++) cout << test[i] << " ";
    cout << endl;
    
    test = mymax(a, b, more_value);
    // Should print a
    for (int i = 0; i < test.size(); i++) cout << test[i] << " ";
    cout << endl;
}
