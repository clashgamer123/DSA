#include <iostream>



/*
In this exercise, we will implement heap as discussed in the class.
We need to implement the following functions.


ONLY THIS FILE MUST BE MODIFIED FOR SUBMISSION

You may edit main.cpp for writing more test cases.
But your code must continue to work with the original main.cpp


THERE IS ONLY ONE TEST CASE ONLY FOR YOUR UNDERSTANDING.

-- You may need to generate more random tests to get your tests right
-- Print will not work until you have a good printing function
*/


#include "heap.h"

// auxillary function
int Maxindex(vector<int> T, int a, int b, int c)
{
  if (T[a]>=T[b] && T[a]>=T[c])
  {
    return a;
  }
  else if (T[b]>=T[a] && T[b]>=T[c])
  {
    return b;
  }
  else
  {
    return c;
  }
}

int Heap::parent(int i) {
  return ((i-1)/2) ;
}

int Heap::left(int i) {
  return (2*i + 1) ;
}

int Heap::right(int i) {
  return (2*i + 2) ;
}

int Heap::max() {
  if (sz == 0)
  {
    throw std :: out_of_range("Max in a empty heap.") ;
  }
  return store[0] ;
}

void Heap::swap(int i, int j) 
{
  int temp = store[i] ;
  store[i] = store[j] ;
  store[j] = temp ;
  return ;
}

void Heap::insert(int v) 
{
  // Use auxillary func append as it takes care of any size defeciency.
  this->append(v) ;
  int i = sz - 1 ;
  while(i>0 && store[parent(i)]<store[i])
  {
    swap(i, parent(i)) ;
    this->swap_count++;
    i = parent(i) ;
  }
  return ;
}

void Heap::heapify(int i) 
{
  // both left and right subtrees are already valid heaps.
  // Heapify on a leaf should just return.
  if (left(i)>=int(sz) && right(i)>=int(sz))
  {
    return ;
  }
  
  // ***** BUG*******
  // In the following step we need to check if both left and right are in heap.
  // This is because right i may not exit due to delete max.
  // int c = Maxindex(this->store, i, left(i), right(i)) ;
  
  int  c ;

  if (right(i)>=int(sz))
  {
    c = (store[i]>=store[left(i)]) ? i : left(i) ;
  }
  else
  {
    c = Maxindex(this->store, i, left(i), right(i));
  }
  // now we are good to go.
  if (c == i)
  {
    return ;
  }
  this->swap(c, i) ;
  this->swap_count++;
  heapify(c) ;
}


void Heap::deleteMax() 
{
  swap(0, sz-1) ;
  this->swap_count++;
  // Decrease the size and heapify
  sz = sz - 1;
  heapify(0);
  return ;
}

void Heap::buildHeap() 
{
  // When we append instead of insert the heap propertied may be lost.
  // Hence this function.
  for(int i = sz-1; i>=0; i--)
  {
    heapify(i) ;
  }
  return ;
}

void Heap::heapSort() 
{
  this->buildHeap() ;
  int initsize = this->sz ;
  while(sz>0)
  {
    deleteMax() ;
  }
  // // We are just sorting not deleting the heap.
  // // hence restore sz.
  this->sz = initsize ;
  return ;
}


