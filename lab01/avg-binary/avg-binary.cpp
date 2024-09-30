#include <iostream>

// Consider the binary search algorithm presented in class. We are interested
// in determining the average execution time of the binary search. To
// accomplish this, let's conduct an experiment.

// Suppose we have an array of size 1024, which contains distinct elements
// arranged in non-increasing order. We have already analyzed the running
// time when the element being searched for is not present in the array.
// Now, let's assume that we are only searching for elements that we know
// exist in the array.

// Our goal is to experimentally calculate the average number of
// iterations required to search for all 1024 elements in the array.

// In the following,
//   -- Implement BinarySearch that can handle non-increasing array
//   -- Harness BinarySearch such that we can compute avarage number
//      of iterations


int BinarySearch( int*S, int n, int e) 
{
  int f = 0, l = n-1 ;
  int m = (f+l)/2 ;
  int time = 0;
  
  while( f <= l)
  {
    time+=1 ;
    if (S[m]==e) { return time ;}
    else if (S[m]>e) 
    {
      f = m + 1;
    }
    else
    {
      l = m - 1 ;
    }
    m = (f+l)/2 ;
  }
  return -1; 
}

int main()
{
  int n = 1024 ;
  int S[n] ;
  for(int i=0; i<n; i++)
  {
    S[i] = n - i ;
  }

  int sum = 0;
  for (int e=1; e<=n; e++)
  {
    sum+=(BinarySearch(S, n, e)) ;
  }
  std :: cout<< "Average Time = " << sum/n << '\n' ;
}