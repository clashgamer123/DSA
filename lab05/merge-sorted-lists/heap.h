#include <iostream>
#include <memory>
#include <vector>
#pragma once

//#pragma is a preprocessor directive in C and C++ that allows you to specify additional information to the compiler beyond what is conveyed in the language itself.

// '#pragma once' is a specific directive that tells the compiler to include the current file only once,
// even if it is included multiple times in a single translation unit. 
//This is useful for preventing multiple definitions of the same symbol, which can cause linker errors.
// Same effect can be achieved by #ifndef etc.

/* You should NOT add ANY other includes in this file.
 * Do NOT add `using namespace std` in header files. It is a bad practice.
 * Do not panic on seeing `value_type`, `size_type`, `reference` etc.
 * They are just placeholders. You can replace them with actual types
 * but it is recommended to keep them as is.
 * The purpose of all this is to introduce you to more of C++ syntax.
 *
 * Your task is to implement the class `Heap` and all its methods.
 * You should not change the class definition or ANY of its PUBLIC functions.
 * You are free to add any members (should be PROTECTED) to the class.
 * You can also add PROTECTED member function signatures to the class.
 * But those should be implemented below, OUTSIDE the class definition.
 *
 * A quick intro to comparator classes in C++:
 * a class object `comp` of type `Compare` can be used to compare two values
 * like this: `comp(a, b)`. It returns `true` if `a` is less than `b` and
 * the comparator is a `std::less` object. If the comparator is a `std::greater`
 * object, it returns `true` if `a` is greater than `b`.
 * Assuming that the comparator is a `std::less` object, your implementation
 * should be that of a MIN-HEAP (top = smallest element).
 * You can create a comparator object like this: `Compare comp;`.
 *
 * A quick intro to std::move in C++:
 * `std::move` is used to convert a variable to an rvalue reference.
 * It is used to transfer ownership of a resource from one object to another.
 * For example, `b = std::move(a)` transfers the ownership of `a` to `b`.
 * After that, `a` should not be used anywhere in the code.
 * It is used in move constructors and move assignment operators.
 * That is, the ones with `heap_t&& other` as a parameter.
 * the `noexcept` keyword is used to specify that a function 
 * does not throw any exceptions and is used for optimization purposes.
 *
 * Note that your task involves completing this class as well as
 * complete the tasks in files "student.h" and "merge-sorted-lists.h".
 */

// The following is a template class and for the comparator a default value is given in case we do not instantiate it ourselves.
// We need to create an instance of the Compare object and then we can use them like Compare(a, b).
template <typename T, class Compare = std::less<T>>
class heap_t {
    // Do not modify any existing members of this class.
    using value_type = T;
    using size_type = std::size_t;
    using reference = T&;
    using const_reference = const T&;
    // These are just aliases.
    // In standard containers these aliases are already defined using typedef.
    // In custom classes we need to do this ourselves.
public:
    heap_t();
    ~heap_t();
    heap_t(const heap_t& other);
    heap_t(heap_t&& other) noexcept;
    heap_t& operator = (const heap_t& other);
    heap_t& operator = (heap_t&& other) noexcept;

    void push(const value_type& value);
    value_type pop();
    const_reference top() const;
    size_type size() const;
    bool empty() const;
    void clear();

protected:
    std::vector<value_type> data;
    size_type sz;

    // Compare object.
    Compare comp ;
    // ie comp(parent, data) must be true
    size_type getSize()
    {
      return data.size() ;
    }

    size_type left(size_type i)
    {
      return (2*i+1) ;
    }

    size_type right(size_type i)
    {
      return (2*i+2) ;
    }

    size_type parent(size_type i)
    {
      return (i-1)/2 ;
    }

    void swap(size_type a, size_type b)
    {
      value_type temp = data[a];
      data[a] = data[b];
      data[b] = temp;
      return ;
    }

    size_type comp_index(size_type a, size_type b, size_type c)
    {
      if (comp(data[a], data[b]) && comp(data[a], data[c])) { return a ;}
      else if ( comp(data[b], data[a]) && comp(data[b], data[c]) ) { return b ; }
      else { return c ;} 
    }

    void heapify(size_type i)
    {
      if (left(i)>=sz && right(i)>=sz)
      {
        return  ;
      }

      int c;

      if (right(i)>=sz)
      {
        c = (comp(data[i], data[left(i)])) ? i : left(i) ; 
      }
      else
      {
        c = comp_index(i, left(i), right(i)) ;
      }

      if (c == i)
      {
        return ;
      }
      this->swap(c, i) ;
      heapify(c) ;
    }

} ;

// TODO: Implement the class methods here.

template <typename T, class Compare>
heap_t<T, Compare>::heap_t() 
{
  this->sz = 0;
}

template <typename T, class Compare>
heap_t<T, Compare>::~heap_t() 
{}

template <typename T, class Compare>
heap_t<T, Compare>::heap_t(const heap_t& other) 
{
  // 'https://stackoverflow.com/questions/6921185/why-do-objects-of-the-same-class-have-access-to-each-others-private-data'
  // Check this out for doubts on why one object can access protected members of other objects'
  // Answer:
  // Because that's how it works in C++. In C++ access control works on per-class basis, not on per-object basis.

//Access control in C++ is implemented as a static, compile-time feature. 
//I think it is rather obvious that it is not really possible to implement any meaningful per-object access control at compile time.
//Only per-class control can be implemented that way.
//Some hints of per-object control are present in protected access specification,
//which is why it even has its own dedicated chapter in the standard (11.5). But still any per-object features described there are rather rudimentary. 
//Again, access control in C++ is meant to work on per-class basis.

  this->sz = other.sz ;
  this->data = other.data ;
}

template <typename T, class Compare>
heap_t<T, Compare>::heap_t(heap_t&& other) noexcept 
{
  this->data = std :: move(other.data);
  this->sz = std :: move(other.sz);
}

template <typename T, class Compare>
heap_t<T, Compare>& heap_t<T, Compare>::operator = (const heap_t& other)
{
  this->data = other.data;
  this->sz = other.sz ;
  return *this;
}

template <typename T, class Compare>
heap_t<T, Compare>& heap_t<T, Compare>::operator = (heap_t&& other) noexcept
{
  data = std::move(other.data);
  this->sz = std :: move(other.sz);
  return *this;
}

template <typename T, class Compare>
void heap_t<T, Compare>::push(const value_type& value) 
{
  if (sz == getSize())
  {
    data.push_back(value) ;
  }
  else
  {
    data[sz] = value ;
  }
  sz++;

  // Now correct any error in the heap wrt Compare
  size_type i = sz - 1;
  while(i>0 && comp(data[i], data[parent(i)]))
  {
    swap(i, parent(i)) ;
    i = parent(i) ;
  }
  
  return ;
}

template <typename T, class Compare>
typename heap_t<T, Compare>::value_type heap_t<T, Compare>::pop() {
    if (this->size() == 0) {
        throw std::out_of_range("Heap is empty");
    }
    value_type top_e = data[0];
    
    swap(0, sz-1) ;
    sz--;
    this->heapify(0) ;
    return top_e;
}

template <typename T, class Compare>
typename heap_t<T, Compare>::const_reference heap_t<T, Compare>::top() const {
    if (this->size() == 0) {
        throw std::out_of_range("Heap is empty");
    }
    return data[0];
}

template <typename T, class Compare>
typename heap_t<T, Compare>::size_type heap_t<T, Compare>::size() const {
  return sz ;
}

template <typename T, class Compare>
bool heap_t<T, Compare>::empty() const {
  return (sz==0) ;
}

template <typename T, class Compare>
void heap_t<T, Compare>::clear() 
{
  this->data.clear() ;
  this->sz = 0;
  return ;
}

