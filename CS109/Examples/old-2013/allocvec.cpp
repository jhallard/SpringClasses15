// $Id: allocvec.cpp,v 1.1 2013-03-14 14:11:50-07 - - $

//
// allocvec
// example shows how an allocator is used to manage a vector.
//
// Container elements must be default-constructable, copyable,
// assignable, and destructible.
//
// Simple functions are inlined for efficiency.
//

#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

using namespace std;

template <typename value_t, class alloc_t = allocator<value_t>>
class allocvec {
   public:
      typedef value_t *iterator;
      typedef const value_t *const_iterator;
   private:
      static const size_t MIN_RESERVE = 8;
      alloc_t alloc;
      size_t size_;
      size_t capacity_;
      iterator begin_;
   public:
      // Inline members
      inline iterator begin() {return begin_;}
      inline iterator end() {return &begin_[size_];}
      inline const_iterator begin() const {return begin_;}
      inline const_iterator end() const {return &begin_[size_];}
      inline size_t size() const {return size_;}
      inline size_t capacity() const {return capacity_;}
      inline bool empty() const {return size_ == 0;}
      inline value_t &operator[] (size_t pos) {return begin_[pos];}
      inline const value_t &operator[] (size_t pos) const
                                              {return begin_[pos];}
      inline value_t &back() {return begin_[size_ - 1];}
      inline const value_t &back() const {return begin_[size_ - 1];}

      // Other members
      void push_back (const value_t &value);
      void pop_back();
      explicit allocvec (size_t size = 0,
                         const value_t &init = value_t(),
                         alloc_t alloc = allocator<value_t>());
      allocvec (const allocvec &);
      allocvec &operator= (const allocvec &);
      ~allocvec();
      void reserve (size_t size);
};


template <typename value_t, class alloc_t>
allocvec<value_t,alloc_t>::allocvec (size_t size,
               const value_t &init, alloc_t alloc):
               alloc(alloc), size_(size), capacity_(size),
               begin_(NULL) {
   if (size > 0) {
      begin_ = alloc.allocate (capacity_);
      for (iterator itor = begin(); itor != end(); ++itor) {
         alloc.construct (itor, init);
      }
   }
}

template <typename value_t, class alloc_t>
allocvec<value_t,alloc_t>::allocvec (const allocvec &that):
               alloc(that.alloc), size_(that.size_),
               capacity_(that.size_), begin_(NULL) {
   if (size_ > 0) {
      begin_ = alloc.allocate (capacity_);
      iterator thisitor = begin_;
      iterator thatitor = that.begin();
      while (that.itor != that.end()) {
         alloc.construct (*thisitor++, *thatitor++);
      }
   }
}

template <typename value_t, class alloc_t>
allocvec<value_t,alloc_t> &
allocvec<value_t,alloc_t>::operator= (const allocvec &that) {
   if (this == &that) return *this;
   for (iterator itor = begin(); itor != end(); ++itor) {
      alloc.destroy (itor);
   }
   if (capacity_ < that.size()) {
      alloc.deallocate (begin_, capacity_);
      size_ = capacity_ = that.size();
      begin_ = alloc.allocate (capacity_);
   }
   iterator thisitor = begin_;
   iterator thatitor = that.begin();
   while (that.itor != that.end()) {
      alloc.construct (*thisitor++, *thatitor++);
   }
}

template <typename value_t, class alloc_t>
allocvec<value_t,alloc_t>::~allocvec() {
   for (iterator itor = begin(); itor != end(); ++itor) {
      alloc.destroy (itor);
   }
   alloc.deallocate (begin_, capacity_);
}


template <typename value_t, class alloc_t>
void allocvec<value_t,alloc_t>::reserve (size_t capacity) {
   if (capacity < MIN_RESERVE) capacity = MIN_RESERVE;
   if (capacity <= capacity_) return;
   iterator newarray = alloc.allocate (capacity);
   iterator newitor = newarray;
   for (iterator itor = begin(); itor != end(); ++itor) {
      alloc.construct (newitor++, *itor);
      alloc.destroy (itor);
   }
   alloc.deallocate (begin_, capacity_);
   capacity_ = capacity;
   begin_ = newarray;
}

template <typename value_t, class alloc_t>
void allocvec<value_t,alloc_t>::push_back (const value_t &value) {
   if (size_ == capacity_) reserve (size_ * 2);
   alloc.construct (&begin_[size_++], value);
}

template <typename value_t, class alloc_t>
void allocvec<value_t,alloc_t>::pop_back() {
   alloc.destroy (&begin_[--size_]);
}


int main (int argc, char **argv) {
   allocvec<string> vec;
   cout << "sizeof(allocvec) = " << sizeof vec << endl;
   for (char **arg = &argv[1]; arg < &argv[argc]; ++arg) {
      vec.push_back (*arg);
   }
   for (auto itor = vec.begin(); itor != vec.end(); ++itor) {
      cout << "vector: " << " " << *itor << endl;
   }
   cout << "vec.size() = " << vec.size() << endl;
   for (size_t count = 0; count <= vec.size() / 2; ++count) {
      cout << "half: " << vec.back() << endl ;
      vec.pop_back();
   }
   cout << "vec.size() = " << vec.size() << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes allocvec \
//TEST//          This is a simple test of allocvec. \
//TEST//          >allocvec.out 2>&1
//TEST// mkpspdf allocvec.ps allocvec.cpp* allocvec.out
*/


