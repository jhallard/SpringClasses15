// $Id: mixin-minh.cc,v 1.15 2009-03-06 20:25:28-08 - - $

//
// Mixin (interface) multiple inheritance.
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
      virtual void print () = 0;
      virtual ~base () {}
};

class base2 {
   public:
      virtual void print () = 0;
      virtual ~base2 () {}
};

class derived: public base, public base2 {
   public:
      derived (int valuei): value (valuei) {
         info (*this); cout << ", ctor value = " << value << endl;
      }
      virtual void print () {
         info (*this); cout << ", value = " << value << endl;
      }
      virtual ~derived () {}
   private:
      int value;
};

struct intbox {
   int value;
};

int main () {
   base *bptr = new derived (6);
   bptr->print ();
   PRTSIZE (int);
   PRTSIZE (intbox);
   PRTSIZE (base);
   PRTSIZE (derived);
   return 0;
}

