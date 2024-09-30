#include <stdlib.h>
#include "queue.h"

using namespace std;

template <typename T> bool DynamicQueue<T> :: isEmpty() {
  return (head == tail) ;
}

template <typename T> bool DynamicQueue<T> :: isFull() {
  return (size() == N-1); // dummy return
}

template <typename T> void DynamicQueue<T> :: grow() {
  if(isFull()) 
  {
    unsigned int old_size = this->N ;
    N = nextSize() ;
    T* B = new T[N] ;
    for(int i = 0; i<old_size-1; i++)
    {
      B[i] = A[i] ;
    }
    delete[] A ;
    A = B;
  }
  else return ;
}

template <typename T> unsigned int DynamicQueue<T> :: size() {
  return (tail-head) ;
}

template <typename T> void DynamicQueue<T> :: QInsert(T x) {
  if (tail == N-1)
  {
    if(isFull()) 
    {
      this->grow();
    }
    else
    {
      for(int i = head; i<tail; i++)
      {
        A[i-head] = A[i] ;
      }
      tail-=head ;
      head = 0;
    }
  }
  
  A[tail] = x ;
  tail++;
}

template <typename T> bool DynamicQueue<T> :: QDelete(T* x) {
  if (this->isEmpty()) { return false ;}
  *x = this->A[head] ;
  head++;
  return true; 
}
