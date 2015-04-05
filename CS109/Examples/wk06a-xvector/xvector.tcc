// $Id: xvector.tcc,v 1.37 2015-02-03 13:07:18-08 - - $

#include <memory>
#include <utility>

//
// XVECTOR-BASE MEMBERS AND FUNCTIONS.
//

template <typename Type>
xvector_base<Type>::xvector_base (xvector_base&& that):
   begin (that.begin),
   end (that.end),
   limit (that.limit) {
   that.begin = that.end = that.limit = nullptr;
}

template <typename Type>
xvector_base<Type>&
xvector_base<Type>::operator= (xvector_base&& that) {
   if (this != &that) {
      if (begin) alloc.deallocate (begin, limit - begin);
      begin = that.begin;
      end = that.end;
      limit = that.limit;
      that.begin = that.end = that.limit = nullptr;
   }
   return *this;
}

template <typename Type>
xvector_base<Type>::xvector_base (size_t capacity):
   begin (alloc.allocate (capacity)),
   end (begin),
   limit (&begin[capacity]) {
}


//
// XVECTOR CONSTRUCTORS, OPERATOR=, DESTRUCTOR.
//

// Copy constructor.
template <typename Type>
xvector<Type>::xvector (const xvector& that): base (that.capacity()) {
   uninitialized_copy (that.cbegin(), that.cend(), base.begin);
   base.end = base.begin + that.size();
}

// Copy operator=.
template <typename Type>
xvector<Type>& xvector<Type>::operator= (const xvector& that) {
   if (*this != that) {
      resize (0);
      reserve (that.size());
      uninitialized_copy (that.cbegin(), that.cend(), base.begin);
      base.end = base.begin + that.size();
   }
   return *this;
}

// Move constructor.
template <typename Type>
xvector<Type>::xvector (xvector&& that):
   base (std::move (that.base)) {
}

// Move operator=.
template <typename Type>
xvector<Type>& xvector<Type>::operator= (xvector&& that) {
   if (*this != that) base = std::move (that);
   return *this;
}

// Fill constructor.
template <typename Type>
xvector<Type>::xvector (size_type fill_size, const value_type& val):
   base (fill_size) {
   base.end = &base.begin[fill_size];
   uninitialized_fill (base.begin, base.end, val);
}

// Initializer list constructor.
template <typename Type>
xvector<Type>::xvector (initializer_list<value_type> list):
   base (list.size()) {
   uninitialized_copy (list.begin(), list.end(), base.begin);
   base.end = base.begin + list.size();
}


//
// XVECTOR OTHER FUNCTION MEMBERS.
//

// Reserve minimum uninitialized space.
template <typename Type>
void xvector<Type>::reserve (size_type capacity_) {
   if (capacity_ <= capacity()) return;
   if (capacity_ < MIN_RESERVE) capacity_ = MIN_RESERVE;
   if (capacity_ < 2 * capacity()) capacity_ = 2 * capacity();
   xvector_base<value_type> new_base (capacity_);
   new_base.end = &new_base.begin[size()];
   if (base.begin and size() > 0) {
      uninitialized_copy (begin(), end(), new_base.begin);
      resize (0);
   }
   base = std::move (new_base);
}

// Increase or decrease size of vector.
template <typename Type>
void xvector<Type>::resize (size_type size_, const value_type &val) {
   while (size_ < size()) pop_back();
   while (size_ > size()) push_back (val);
}

template <typename Type>
void xvector<Type>::push_back (const value_type& that) {
   reserve (size() + 1);
   base.alloc.construct (base.end++, that);
}

template <typename Type>
void xvector<Type>::push_back (value_type&& that) {
   reserve (size() + 1);
   *base.end++ = std::move (that);
}

template <typename Type>
void xvector<Type>::pop_back() {
   base.alloc.destroy (--base.end);
}


//
// XVECTOR RELATIONAL OPERATORS == and <
//
template <typename Type>
bool operator== (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   if (lhs.size() != rhs.size()) return false;
   auto lhs_itor = lhs.cbegin();
   auto rhs_itor = rhs.cbegin();
   for (; lhs_itor != lhs.cend(); ++lhs_itor, ++rhs_itor) {
      if (*lhs_itor != *rhs_itor) return false;
   }
   return true;
}
    
template <typename Type>
bool operator< (const xvector<Type>& lhs, const xvector<Type>& rhs) {
   auto lhs_itor = lhs.cbegin();
   auto rhs_itor = rhs.cbegin();
   for (; lhs_itor != lhs.cend(); ++lhs_itor, ++rhs_itor) {
      if (rhs_itor == rhs.cend()) return false;
      if (*lhs_itor < *rhs_itor) return true;
      if (*rhs_itor < *lhs_itor) return false;
   }
   return rhs_itor != rhs.cend();
}
    

//
// XVECTOR::ITERATOR FUNCTIONS.
//

template <typename Type>
xvector_iterator<Type> xvector_iterator<Type>::operator++ (int) {
   xvector_iterator<Type> result {*this};
   ++base;
   return result;
}

template <typename Type>
xvector_iterator<Type> xvector_iterator<Type>::operator-- (int) {
   xvector_iterator<Type> result {*this};
   --base;
   return result;
}

