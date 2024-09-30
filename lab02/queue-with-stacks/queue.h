#include <cstdlib>
#include <cstddef>
#include "stack.h"
#pragma once

/*
 * You must NOT add ANY other includes than what is already here.
 * The purpose of this file is to implement the functioning of a queue in C++.
 * The task is to implement a Queue using stacks. This requires two stacks.
 * Ensure that ALL of them are on average constant time. Amortized O(1) is OK.
 * You must NOT change the data members or ANY of the method signatures.
 * NOR are you allowed to add any additional methods or data members.
 * You are free to use the PUBLIC methods of the Stack class here.
 */

template <typename T>
class Queue {
    class Stack<T> first_stack;
    class Stack<T> second_stack;
public:
    Queue();
    ~Queue();
    void enqueue(T value);
    T dequeue();
    T peek();
    bool isEmpty();
    size_t getSize();
};

// ENTER YOUR IMPLEMENTATIONS OF METHODS BELOW

template <typename T> Queue<T> :: Queue() { } // Because the stacks are initialized by their constructors.

template <typename T> Queue<T> :: ~Queue() { } // When queue is destroyed then so are the stacks and their destructors are called.

template <typename T> void Queue<T> :: enqueue(T value) 
{
    // At any given time only firststack is filled and it conatins the queue.
    first_stack.push(value) ;
}

template <typename T> T Queue<T> :: dequeue()
{
    if (first_stack.isEmpty())
    {
        throw std :: invalid_argument("Empty queue dequeue error.") ;
    }

    else 
    {
        while(!first_stack.isEmpty())
        {
            second_stack.push(first_stack.pop()) ;
        }
        T val = second_stack.pop() ;

        while(!second_stack.isEmpty())
        {
            first_stack.push(second_stack.pop()) ;
        }
        return val ;
    }
}

template <typename T> T Queue<T> :: peek()
{
    if(!first_stack.isEmpty())
    {
        while(!first_stack.isEmpty())
        {
            second_stack.push(first_stack.pop()) ;
        }
        T value = second_stack.peek() ;
        while(!second_stack.isEmpty())
        {
            first_stack.push(second_stack.pop()) ;
        }
        return value ;
    }
    else
    {
        throw std :: invalid_argument("Empty queue peek error.") ;
    }
}

template <typename T> bool Queue<T> :: isEmpty()
{
    return first_stack.isEmpty() ;
}

template <typename T> size_t Queue<T> :: getSize()
{
    return first_stack.getSize() ;
}