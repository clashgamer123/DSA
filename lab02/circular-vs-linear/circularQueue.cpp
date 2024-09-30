#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return (size() == 0 ) ;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return (this->size() == N - 1) ;
}

template <typename T> void DynamicQueue<T> :: grow() {
  if(isFull())
  {
    unsigned int old_size = N ;
    N = nextSize() ;
    T* B = new T[N] ;
    int j = 0;
    for( int i = head; i!=tail; i = (i+old_size+1)%old_size )
    {
      B[j] = A[i] ;
      j++;
    }
    delete[] A ;
    A = B ;
    head = 0;
    tail = old_size - 1;
  }
  else return ;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return ((tail-head+N)%N) ;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if (isFull())
  {
    this->grow() ;
    A[tail] = x ;
    tail++ ;
  }
  else 
  {
    A[tail] = x ;
    tail = (tail+1)%N ;
  }
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if (isEmpty()) { return false ; }
  *x = A[head] ;
  head = (head+1)%N ;
  return true ;
}
