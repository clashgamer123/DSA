#include <cstdlib>
#include <cstddef>
#pragma once

/*
 * You must NOT add ANY other includes than this.
 * The purpose of this file is to implement the functioning of a stack in C++.
 * Implement all the method functions in this file, your way.
 * Ensure that ALL of them are on average constant time. Amortized O(1) is OK.
 * You must NOT change the method signature of any of the methods.
 * You may add any additional methods or data members as you need.
 * Those methods and data members should be protected.
 */

#define INIT_SIZE 1 ;
#define SCALE 2 ;

template <typename T>
class Stack {
    protected:
    unsigned int N; // The size of the stack at any time.
    unsigned int head;
    unsigned int nextSize() { return N*SCALE ;}
    T* A ; // The array base STACK.

    void Expand() ;

public:
    Stack();
    ~Stack();
    void push(T value);
    T pop();
    T peek();
    bool isEmpty();
    size_t getSize();
};

// ENTER YOUR IMPLEMENTATIONS OF METHODS BELOW

template<typename T>  Stack<T> :: Stack(){
    N = INIT_SIZE ;
    head = 0;
    A = new T[N] ; // A is our array stack
} 

template<typename T> Stack<T> :: ~Stack(){
    delete[] A ;
    A = nullptr ;
}

template<typename T> bool Stack<T> :: isEmpty(){
    return (head == 0) ;
}

template<typename T> size_t Stack<T> :: getSize(){
    return (head) ;
}

template<typename T> void Stack<T> :: push(T value) {
    if(getSize() == N)
    {
        this->Expand() ;
        A[head] = value ;
        head++ ;
        return ;
    }
    else
    {
        A[head] = value ;
        head ++ ;
        return ;
    }
}

template<typename T> T Stack<T> :: peek(){
    if(isEmpty()) 
    {
        throw std :: invalid_argument("Empty stack peek error.") ;
    }
    else { return A[head-1] ;}
}

template<typename T> T Stack<T> :: pop(){
    if(isEmpty())
    {
        throw std :: invalid_argument("Empty stack pop error.") ;
    }
    else
    {
        head--;
        return A[head] ;
    }
}

template<typename T> void Stack<T> :: Expand()
{
    // increase the size by 2.
    unsigned int old_size  = N ;
    N = nextSize() ;
    T* B = new T[N] ;
    for(int i = 0; i<old_size; i++)
    {
        B[i] = A[i] ;
    }
    delete[] A ;
    A = B ;
    return ;
}

