// $Id: xvector.h,v 1.46 2015-02-03 13:06:33-08 - - $

//
// Vector explicitly managing memory
// using allocate/deallocate/construct/destroy.
// with iterator/const_iterator.
//

#ifndef __XVECTOR_H__
#define __XVECTOR_H__

#include <initializer_list>
#include <iterator>

template <typename Type> class xvector_base;
template <typename Type> class xvector;
template <typename Type> class xvector_iterator;

// Base class guarantees all xvector ctors no uninit pointers.
// Manages allocation/deallocation of memory.
template <typename Type>
class xvector_base {
   friend class xvector<Type>;

private:
   allocator<Type> alloc;
   Type* begin {nullptr};
   Type* end {nullptr};
   Type* limit {nullptr};
   xvector_base(): begin(nullptr), end(nullptr), limit(nullptr) {}
   xvector_base (const xvector_base&) = delete;
   xvector_base& operator= (const xvector_base&) = delete;
   xvector_base (xvector_base&& that);
   xvector_base& operator= (xvector_base&&);
   ~xvector_base() { alloc.deallocate (begin, limit - begin); }
   explicit xvector_base (size_t capacity);
};


// Uses xvector_base to construct/destroy elements 
// and provide access to elements.
template <typename Type>
class xvector {

public:
   using value_type = Type;
   using reference = value_type&;
   using const_reference = const value_type&;
   using pointer = value_type*;
   using const_pointer = const value_type*;
   using difference_type = ptrdiff_t;
   using size_type = size_t;
   using iterator = xvector_iterator<value_type>;
   using const_iterator = xvector_iterator<const value_type>;

private:
   static constexpr size_type MIN_RESERVE = 4;
   xvector_base<value_type> base;
   void deallocate_this();
   void copy_from_that (const xvector&);


public:
   // Replace implicit members.
   xvector(): base() {}
   xvector (const xvector&);
   xvector (xvector&&);
   xvector& operator= (const xvector&);
   xvector& operator= (xvector&&);
   ~xvector() { resize (0); }

   // More constructors.
   explicit xvector (size_type size,
                     const value_type& val = value_type{});
   explicit xvector (initializer_list<value_type> ilist);

   // Capacity.
   size_type size() const     { return base.end - base.begin; }
   size_type capacity() const { return base.limit - base.begin; }
   bool empty() const         { return size() == 0; }
   void reserve (size_type);
   void resize (size_type, const value_type &val = value_type());

   // Modifiers: push_back, pop_back.
   void push_back (const value_type&);
   void push_back (value_type&&);
   void pop_back();

   // Iterators: begin, cbegin, end, cend.
   iterator begin()              { return iterator (base.begin); }
   const_iterator begin() const  { return iterator (base.begin); }
   const_iterator cbegin() const { return iterator (base.begin); }
   iterator end()                { return iterator (base.end); }
   const_iterator end() const    { return iterator (base.end); }
   const_iterator cend() const   { return iterator (base.end); }

   // Access: [], front, back.
   reference operator[] (size_type pos) { return base.begin[pos]; }
   const_reference operator[] (size_type pos) const
                                        { return base.begin[pos]; }
   reference front()                    { return base.begin[0]; }
   const_reference front() const        { return base.begin[0]; }
   reference back()                     { return base.end[-1]; }
   const_reference back() const         { return base.end[-1]; }
};


// Relational operators for comparing vectors lexicographically.
// Do not need to be members.
template <typename Type>
bool operator== (const xvector<Type>& lhs, const xvector<Type>& rhs);

template <typename Type>
bool operator< (const xvector<Type>& lhs, const xvector<Type>& rhs);

template <typename Type>
bool operator!= (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   return not (lhs == rhs);
}

template <typename Type>
bool operator> (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   return rhs < lhs;
}

template <typename Type>
bool operator<= (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   return not (rhs < lhs);
}

template <typename Type>
bool operator>= (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   return not (lhs < rhs);
}


// xvector<Type>::iterator
template <typename Type>
class xvector_iterator {
   friend class xvector<Type>;
   template<typename> friend class xvector_iterator;

public:
   using iterator_category = random_access_iterator_tag;
   using value_type = Type;
   using reference = value_type&;
   using pointer = value_type*;
   using const_reference = const value_type&;
   using const_pointer = const value_type*;
   using difference_type = ptrdiff_t;

private:
   pointer base {};
   xvector_iterator (pointer base): base(base) {}

public:
   xvector_iterator(): base(nullptr) {}
   // Other implicit members by default OK.

   xvector_iterator& operator++()      { ++base; return *this; }
   xvector_iterator& operator--()      { --base; return *this; }
   xvector_iterator operator++ (int);
   xvector_iterator operator-- (int);

   reference operator*()                         { return *base; }
   const_reference operator*() const             { return *base; }
   pointer operator->()                          { return base; }
   const_pointer operator->() const              { return base; }
   reference operator[] (size_t pos)             { return base[pos]; }
   const_reference operator[] (size_t pos) const { return base[pos]; }

   // Comparison and arithmetic operators.
   bool operator== (const xvector_iterator& that) const
                                 { return base == that.base; }
   bool operator<  (const xvector_iterator& that) const
                                 { return base < that.base; }
   xvector_iterator& operator+= (difference_type offset)
                                 { base += offset; return *this; }
   xvector_iterator& operator-= (difference_type offset)
                                 { base -= offset; return *this; }
   difference_type operator- (const xvector_iterator& that)
                                 { return base - that.base; }
   // Implicit conversion of iterator to const_iterator.
   operator xvector_iterator<const value_type>() const
   { return xvector_iterator<const value_type> (base); }
   operator bool() { return base != nullptr; }

};


//
// XVECTOR-ITERATOR NON-MEMBER OPERATORS
//

template <typename Type>
xvector_iterator<Type>
operator+ (typename xvector_iterator<Type>::difference_type offset,
           const xvector_iterator<Type>& itor) {
   xvector_iterator<Type> result {itor};
   return result += offset;
}

template <typename Type>
xvector_iterator<Type>
operator+ (const xvector_iterator<Type>& itor,
           typename xvector_iterator<Type>::difference_type offset) {
   xvector_iterator<Type> result {itor};
   return result += offset;
}

template <typename Type>
xvector_iterator<Type>
operator- (const xvector_iterator<Type>& itor,
           typename xvector_iterator<Type>::difference_type offset) {
   xvector_iterator<Type> result {itor};
   return result -= offset;
}

template <typename Type>
bool operator!= (const xvector_iterator<Type>& one,
                 const xvector_iterator<Type>& two) {
   return not (one == two);
}

template <typename Type>
bool operator> (const xvector_iterator<Type>& one,
                const xvector_iterator<Type>& two) {
   return two < one;
}

template <typename Type>
bool operator<= (const xvector_iterator<Type>& one,
                 const xvector_iterator<Type>& two) {
   return not (two < one);
}

template <typename Type>
bool operator>= (const xvector_iterator<Type>& one,
                 const xvector_iterator<Type>& two) {
   return not (one < two);
}

#include "xvector.tcc"

#endif

