// $Id: fixarray.cpp,v 1.8 2014-05-30 16:43:27-07 - - $

//
// fixarray - implementation of an int vector, using templates,
// with the array inline in the struct, so size can not be changed.
// also shows checked operator[] instead of get/put.
//

#include <iostream>
#include <stdexcept>

using namespace std;

/////////////////////////////////////////////////////////////////
// fixarray.h
/////////////////////////////////////////////////////////////////

template <typename item_t, size_t size_>
class fixarray {
   private:
      item_t data_[size_];
      void range_check (size_t index) const;
   public:
      fixarray();
      fixarray (const fixarray &) = default;            // copy ctor
      fixarray &operator= (const fixarray &) = default; // copy op=
      ~fixarray() = default;
      size_t size() const;
      item_t operator[] (size_t index) const; // get: x = a[i];
      item_t& operator[] (size_t index); // put: a[i] = x;
};


/////////////////////////////////////////////////////////////////
// fixarray.cpp
/////////////////////////////////////////////////////////////////

template <typename item_t, size_t size_>
fixarray<item_t,size_>::fixarray() {
   for (size_t index = 0; index < size_; ++index) data_[index] = int();
}

template <typename item_t, size_t size_>
void fixarray<item_t,size_>::range_check (size_t index) const {
   if (index >= size_) throw out_of_range ("fixarray::range_check");
}

template <typename item_t, size_t size_>
size_t fixarray<item_t,size_>::size() const {
   return size_;
}

template <typename item_t, size_t size_>
item_t fixarray<item_t,size_>::operator[] (size_t index) const {
   range_check (index);
   return data_[index];
}

template <typename item_t, size_t size_>
item_t& fixarray<item_t,size_>::operator[] (size_t index) {
   range_check (index);
   return data_[index];
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

using tenvec = fixarray<int,10>;
int main () {
   tenvec v1;
   v1[3] = 99;
   int x = v1[3];
   cout << x << endl;
   try {
      cout << "v1[999] = " << v1[999] << endl;
   }catch (out_of_range error) {
      cout << error.what() << endl;
   }
   tenvec v2 = v1;
   v2[3] = 1234;
   cout << v1[3] << " " << v2[3] << endl;
   v2 = v1;
   cout << v1[3] << " " << v2[3] << endl;
   for (size_t i = 0; i < v1.size(); ++i) cout << v1[i];
   cout << endl;
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind fixarray >fixarray.out 2>&1
//TEST// mkpspdf fixarray.ps fixarray.cpp* fixarray.out*

