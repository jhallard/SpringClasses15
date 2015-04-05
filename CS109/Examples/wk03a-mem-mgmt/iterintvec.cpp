// $Id: iterintvec.cpp,v 1.22 2014-07-02 18:15:47-07 - - $

//
// iterintvec - implementation of an int vector with iterator.
//

#include <iostream>
#include <stdexcept>

using namespace std;

/////////////////////////////////////////////////////////////////
// iterintvec.h
/////////////////////////////////////////////////////////////////

class iterintvec {
   private:
      size_t _size;
      int *_data;
      void copy_data (int *data);
      void range_check (size_t index) const;
   public:
      using value_type = int;
      using reference = int&;
      using const_reference = const int&;
      using pointer = int*;
      using const_pointer = const int*;
      using difference_type = ptrdiff_t;
      using size_type = size_t;
      class iterator;
      friend class iterintvec::iterator;
      iterintvec ();                             // default ctor
      iterintvec (const iterintvec&);            // copy ctor
      iterintvec (iterintvec&&);                 // move ctor
      iterintvec& operator= (const iterintvec&); // copy operator=
      iterintvec& operator= (iterintvec&&);      // move operator=
      ~iterintvec();                             // dtor
      explicit iterintvec (size_t size);
      size_t size() const;
      int get (size_t index) const;
      void put (size_t index, int value);
      iterator begin();
      iterator end();
};


class iterintvec::iterator {
   private:
      pointer curr;
      friend class iterintvec;
      iterator (pointer init): curr (init) {};
   public:
      iterator(): curr (nullptr) {};
      reference operator* () { return *curr; }
      const_reference operator* () const { return *curr; }
      iterator& operator++ () { ++curr; return *this; }
      iterator operator++ (int) {
         iterator tmp {*this}; ++curr; return tmp;
      }
      bool operator== (const iterator& that) {
         return curr == that.curr;
      }
      bool operator!= (const iterator& that) {
         return not (*this == that);
      }
};


/////////////////////////////////////////////////////////////////
// iterintvec.cpp
/////////////////////////////////////////////////////////////////

// Private.
void iterintvec::copy_data (int *data) {
   for (size_t index = 0; index < _size; ++index) {
      _data[index] = data[index];
   }
}

// Private.
void iterintvec::range_check (size_t index) const {
   if (index >= _size) throw out_of_range ("iterintvec::range_check");
}

// Default ctor.
iterintvec::iterintvec(): _size(0), _data(nullptr){}

// Copy constructor.
iterintvec::iterintvec (const iterintvec& that):
            _size(that._size), _data (new int[that._size]) {
   copy_data (that._data);
}

// Move constructor.
iterintvec::iterintvec (iterintvec&& that):
            _size(that._size), _data (that._data) {
   that._size = 0;
   that._data = nullptr;
}

// Copy operator=
iterintvec& iterintvec::operator= (const iterintvec& that){
   if (this != &that) {
      if (_data != nullptr) delete[] _data;
      _size = that._size;
      _data = new int[that._size];
      copy_data (that._data);
   }
   return *this;
}

// Move operator=
iterintvec& iterintvec::operator= (iterintvec&& that){
   if (this != &that) {
      if (_data != nullptr) delete[] _data;
      _size = that._size;
      _data = that._data;
      that._size = 0;
      that._data = nullptr;
   }
   return *this;
}


// Destructor.
iterintvec::~iterintvec() {
   if (_data != nullptr) delete[] _data;
}

// Fixed-size allocator.
iterintvec::iterintvec (size_t size):
               _size(size), _data (new int[_size]) {
   for (size_t index = 0; index < _size; ++index) {
      _data[index] = 0;
   }
}

size_t iterintvec::size() const {
   return _size;
}

int iterintvec::get (size_t index) const {
   range_check (index);
   return _data[index];
}

void iterintvec::put (size_t index, int value) {
   range_check (index);
   _data[index] = value;
}

iterintvec::iterator iterintvec::begin() {
   return iterator (&_data[0]);
}

iterintvec::iterator iterintvec::end() {
   return iterator (&_data[_size]);
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main () {
   iterintvec v1(10);
   v1.put (3, 99);
   int x = v1.get (3);
   cout << x << endl;
   try {
      v1.get (999);
   }catch (out_of_range error) {
      cerr << error.what() << endl;
   }
   iterintvec v2 = v1;
   v2.put (3, 1234);
   cout << v1.get (3) << " " << v2.get (3) << endl;
   v2 = v1;
   cout << v1.get (3) << " " << v2.get (3) << endl;
   for (iterintvec::iterator i = v1.begin();
        i != v1.end(); ++i) {
      cout << *i << endl;
   }
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind iterintvec >iterintvec.out 2>&1
//TEST// mkpspdf iterintvec.ps iterintvec.cpp* iterintvec.out*

