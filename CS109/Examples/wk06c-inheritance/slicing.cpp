// $Id: slicing.cpp,v 1.9 2015-02-10 17:51:17-08 - - $

//
// Slicing occurs when an object of a a derived class is copied
// into an object of a base class, which loses information.
// Thus, the copy ctor and operator= should be supporessed.
// We use struct here to avoid protection questions.
//

#include <iostream>
#include <typeinfo>

using namespace std;

struct base {
   int base_;
   void print() { // non-virtual
      cout << typeid(*this).name() << ": " << base_ << endl;
   }
};

struct second: public base {
   int second_;
   void print() { // non-virtual
      cout << typeid(*this).name() << ": " << base_
           << ", " << second_ << endl;
   }
};

struct other: public base {
   int other_;
   void print() { // non-virtual
      cout << typeid(*this).name() << ": " << base_
           << ", " << other_ << endl;
   }
};

int main () {
   cout << "sizeof (base) = " << sizeof (base) << endl;
   cout << "sizeof (second) = " << sizeof (second) << endl;
   cout << "sizeof (other) = " << sizeof (other) << endl;
   base b; b.base_ = 6; b.print();
   second s; s.base_ = 8; s.second_ = 10; s.print();
   other o; o.base_ = 15; o.other_ = 20; o.print();

   b = s; b.print();

   s.base_ = 42; s.second_ = 99; s.print();
   // s = b; s.print(); // error: no match for 'operator=' in 's = b'
   static_cast<base>(s) = b; s.print();

   return 0;
}

//TEST// grind="valgrind --leak-check=full --show-reachable=yes"
//TEST// $grind slicing >slicing.out 2>&1
//TEST// mkpspdf slicing.ps slicing.cpp* slicing.out*
