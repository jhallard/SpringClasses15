// $Id: repeated-minh.cc,v 1.18 2009-03-10 19:13:10-07 - - $

//
// Repeated multiple inheritance.
// We use inline functions for brevity, not necessarily because it
// is a good idea.
//

#include <iostream>
#include <typeinfo>

using namespace std;

template <class any_t>
void info (const any_t &any) {
   cout << "type (" << typeid (any).name ()
        << ", " << sizeof any << ")";
}

#define PRTSIZE(X) { \
        cout << "sizeof " #X " = " << sizeof (X) << endl; }

class base {
   public:
      base (int valuei): value (valuei) {
         info (*this); cout << ", ctor value = " << value << endl;
      }
      virtual void print () {
         info (*this); cout << ", value = " << value << endl;
      }
      virtual ~base () {}
   protected:
      int value;
};

class derived: public base {
   public:
      derived (int valuei, int valuedi):
                  base (valuei), valued(valuedi) {
         info (*this); cout << ", ctor valued = " << valued << endl;
      }
      virtual void print () {
         base::print ();
         info (*this); cout << ", valued = " << valued << endl;
      }
      virtual ~derived () {}
   protected:
      int valued;
};

class derived2: public base {
   public:
      derived2 (int valuei, int valued2i):
                  base (valuei), valued2 (valued2i) {
         info (*this); cout << ", ctor valued2 = " << valued2 << endl;
      }
      virtual void print () {
         base::print ();
         info (*this); cout << ", valued2 = " << valued2 << endl;
      }
      virtual ~derived2 () {}
   protected:
      int valued2;
};

class diamond: public derived, public derived2 {
   public:
      diamond (int i1, int i2, int i3, int i4, int i5):
                  derived (i1, i2), derived2 (i3, i4), bottom (i5) {
         info (*this); cout << ", ctor bottom = " << bottom << endl;
      }
      virtual void print () {
         derived::print ();
         derived2::print ();
         info (*this); cout << ", bottom = " << bottom << endl;
      }
      virtual ~diamond () {}
   protected:
      int bottom;
};

int main () {

   base *bptr = new derived (6, 8);
   cout << endl;
   bptr->print ();
   cout << endl;

   base *bptr2 = new derived2 (3, 5);
   cout << endl;
   bptr2->print ();
   cout << endl;

   derived *dptr = new diamond (10, 11, 12, 13, 14);
   cout << endl;
   dptr->print ();
   cout << endl;

   derived2 *dptr2 = new diamond (10, 11, 12, 13, 14);
   cout << endl;
   dptr->print ();
   cout << endl;

   PRTSIZE (base);
   PRTSIZE (derived);
   PRTSIZE (derived2);
   PRTSIZE (diamond);
   return 0;
}

