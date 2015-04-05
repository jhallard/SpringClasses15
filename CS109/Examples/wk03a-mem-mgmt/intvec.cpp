// $Id: intvec.cpp,v 1.24 2014-04-14 13:16:36-07 - - $

//
// intvec - implementation of an int vector, similar to 
// Stroustrup, ch.17 example.
//

#include <iostream>
#include <stdexcept>

using namespace std;

/////////////////////////////////////////////////////////////////
// intvec.h
/////////////////////////////////////////////////////////////////

class intvec {
   private:
      size_t _size;
      int *_data;
      void copy_data (int *data);
      void range_check (size_t index) const;
   public:
      intvec ();                         // default ctor
      intvec (const intvec&);            // copy ctor
      intvec (intvec&&);                 // move ctor
      intvec& operator= (const intvec&); // copy operator=
      intvec& operator= (intvec&&);      // move operator=
      ~intvec();                         // dtor
      // Other members.
      explicit intvec (size_t size);
      size_t size() const;
      int get (size_t index) const;
      void put (size_t index, int value);
};


/////////////////////////////////////////////////////////////////
// intvec.cpp
/////////////////////////////////////////////////////////////////

// Private.
void intvec::copy_data (int *data) {
   for (size_t index = 0; index < _size; ++index) {
      _data[index] = data[index];
   }
}

// Private.
void intvec::range_check (size_t index) const {
   if (index >= _size) throw out_of_range ("intvec::range_check");
}

// Default ctor.
intvec::intvec(): _size(0), _data(nullptr) {
}

// Copy constructor.
intvec::intvec (const intvec& that):
            _size(that._size), _data (new int[that._size]) {
   copy_data (that._data);
}

// Move constructor.
intvec::intvec (intvec&& that):
            _size(that._size), _data (that._data) {
   that._size = 0;
   that._data = nullptr;
}

// Copy operator=
intvec& intvec::operator= (const intvec& that){
   if (this != &that) {
      if (_data != nullptr) delete[] _data;
      _size = that._size;
      _data = new int[that._size];
      copy_data (that._data);
   }
   return *this;
}

// Move operator=
intvec& intvec::operator= (intvec&& that){
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
intvec::~intvec() {
   if (_data != nullptr) delete[] _data;
}

// Fixed-size allocator.
intvec::intvec (size_t size): _size(size), _data (new int[_size]) {
   for (size_t index = 0; index < _size; ++index) {
      _data[index] = 0;
   }
}

size_t intvec::size() const {
   return _size;
}

int intvec::get (size_t index) const {
   range_check (index);
   return _data[index];
}

void intvec::put (size_t index, int value) {
   range_check (index);
   _data[index] = value;
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main () {
   intvec v1(10);
   v1.put (3, 99);
   int x = v1.get (3);
   cout << x << endl;
   try {
      v1.get (999);
   }catch (out_of_range error) {
      cerr << error.what() << endl;
   }
   intvec v2 = v1;
   v2.put (3, 1234);
   cout << v1.get (3) << " " << v2.get (3) << endl;
   v2 = v1;
   cout << v1.get (3) << " " << v2.get (3) << endl;
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind intvec >intvec.out 2>&1
//TEST// mkpspdf intvec.ps intvec.cpp* intvec.out*

