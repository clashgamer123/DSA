#include <iostream>
#include <map>
#include <vector>
#include "rdtsc.h"

// Let's consider vectors again. When a vector is declared without specifying
// a size, it starts empty. However, there needs to be some initial allocation
// of space in anticipation of new elements being added. As we begin filling
// the vector, there will come a point when the allocated memory runs out.
// At this stage, the vector needs to allocate more memory. Your task is to
// write code that detects at what size the new allocation occurs and determine
// the amount of extra memory being allocated.

// Hint: Keep in mind that when a vector requires more memory, it not only
//   needs additional space but also needs to be relocated to ensure continuous
//   storage of the vector. This relocation process takes some time to execute.

using namespace std ;
int main() {
  int n;
  std :: vector<int> V  ;
  // int* pi = &V[0] ;
  // int size = 0;
  // while(pi == &V[0])
  // {
  //   V.push_back(1) ;
  //   size++ ;
  // }
  // std :: cout<<"Reallocation at size n = "<<(size-1) <<'\n' ;
  // return 0;
  cout<<&V[0]<<'\n';
  V.push_back(1);
  cout<<&V[0]<<'\n';
  V.push_back(2) ;
  cout<<&V[0]<<'\n';
}
