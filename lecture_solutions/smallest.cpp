#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Let n be the number of elements on the list

//partition of quicksort -- This is O(n)
template <typename T>
int partition(vector<T>& a, int l, int r)
{	 
      int i= l; 
      // set pivot         
      T p = a [ r ] ; 
      for ( int j = l ; j < r ; j++) {
      // moving pivot to correct position
         if ( a [ j ] <= p ) {
             swap ( a[i] ,a[j] ) ; 
             i ++; 
         } 
      } 
      swap ( a[i] ,a[r]  ) ; 
   // return index where pivot is in correct position
     return i ; 
}


// returns the (k+1)-th smallest element
// What is the runtime of quantile?
// Set up the recurrence
// Solve the recurrence
// You may assume that sort on a very small list on line 43
// takes O(1).

template <typename T>
T quantile (vector<T>& a, int left, int right, int k)
{ 

  if (right <= left + 10) //Sort small array directly
  {  
     sort(a.begin()+left, a.begin()+right);  // Sorts a between left and right. // T(n) when n <= 10 O(1)
    return a[k+left];
  }
    else   // we still have a pretty big array left
  {
    int smallsize = (right-left)/5;
    vector<T> b(smallsize);

 
    // we will call quantile on n/5 sublists of size 5
     //  T(5)*n/5 = O(n)
    for (int i = 0; i < smallsize; i ++)
       b[i] = quantile (a, left+5*i, left+5*(i+1)-1, 2);

   
    // Now we call quantile on list of size n/5 -  T(n/5)
    T pivot = quantile (b, 0, smallsize-1, smallsize/2);

    sub
          
    int p;  // linear search for the pivot O(n)
    for (p = left; p <= right; p++)
    {
        if (a[p] == pivot) break;
    }
   
    swap (a[p], a[right]);

    // partition list around the pivot O(n)
    int m = partition (a, left, right);
     
     // Where is the pivot after the partition?
     // the pivot is the median of the median of sublists of size 5
     //  SO that means that there are at least n/5*1/2  elements smaller than the
     //pivot >= n/10 but that is too small...why?
     // the list of medians was the medians of groups of size 5, so there were 3 elements
     // less than or equal to the median on each list -> the pivot is >= 3n/10 elements in a
     // and <= 3n/10 elements in a. Why does this matter? It affects the size of the recursive
     // calls below. Since m is at least 3n/10 elements from left or right endpoint of a
     // the max size of the recurive call will be on a sublist of size at most 7n/10 -> T(7n/10)
          
    if (left+k == m) return a[m];
    else if (left+k < m) return quantile (a, left, m-1, k);
    else return quantile (a, m+1, right, k-(m+1-left));
  }
      
      // To summarize the recurrence relation we need only add up all of the work above:
      // T(n) = T(7n/10) + T(n/5) + cn for n > 10
      // Base cases: T(n) = O(1) for n <= 10 
      // How do we solve this?
      // sum_{i=0}^{log_{10/7}} (9/10)^i*n
}



int main()
{
    vector<int> test;
    for (int i= 1; i <= 100; i++){
         test.push_back(2*i);
    }
    
    int testing = quantile(test, 0,99, 0);
    cout << testing << endl;
    return 0;
}

