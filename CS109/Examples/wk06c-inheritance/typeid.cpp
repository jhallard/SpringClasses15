// $Id: typeid.cpp,v 1.17 2015-02-10 17:53:15-08 - - $

//
// Show a few classes with inheritance.
// All are inline for simplicity.
// Suppress copy ctor and operator= because of inheritance.
// Always make dtor virtual if any functions are virtual.
//

#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;
#define TRACE(STMT) cout << "TRACE (" << #STMT << ")" << endl; STMT
#define SHOW cout << this << "->" << __func__ << endl;

class base {
   private:
      string baseid;
      base (const base&) = delete;
      base& operator= (const base&) = delete;
   public:
      base(): baseid ("(base)") { SHOW }
      virtual ~base() { SHOW }
      virtual void print() { cout << baseid; }
};

class extend: public base {
   private:
      string extendid;
   public:
      extend(): extendid ("(extend)") { SHOW }
      virtual ~extend() { SHOW }
      virtual void print() { base::print(); cout << "::" << extendid; }
};

class other: public base {
   private:
      string otherid;
   public:
      other(): otherid ("(other)") { SHOW }
      virtual ~other() { SHOW }
      virtual void print() { base::print(); cout << "::" << otherid; }
};


int main() {
   TRACE (cout << sizeof (base) << endl;)
   TRACE (cout << sizeof (extend) << endl;)
   TRACE (cout << sizeof (other) << endl;)
   TRACE (base *bptr = new base();)
   TRACE (cout << "typeid *bptr = " << typeid (*bptr).name() << endl;)
   TRACE (bptr->print(); cout << endl;)
   TRACE (base *dptr = new extend();)
   TRACE (cout << "typeid *dptr = " << typeid (*dptr).name() << endl;)
   TRACE (dptr->print(); cout << endl;)
   TRACE (base *optr = new other();)
   TRACE (cout << "typeid *optr = " << typeid (*optr).name() << endl;)
   TRACE (optr->print(); cout << endl;)
   TRACE (delete optr;)
   TRACE (delete bptr;)
   TRACE (bptr = dptr;)
   TRACE (cout << "typeid *bptr = " << typeid (*bptr).name() << endl;)
   TRACE (bptr->print(); cout << endl;)
   TRACE (dptr = dynamic_cast<extend *> (bptr);)
   TRACE (cout << "typeid *dptr = " << typeid (*dptr).name() << endl;)
   TRACE (dptr->print(); cout << endl;)
   TRACE (extend dloc;)
   TRACE (cout << "typeid dloc = " << typeid (dloc).name() << endl;)
   TRACE (dloc.print(); cout << endl;)
   TRACE (delete dptr;)
   //error: 'base::base(const base&)' is private
   //Otherwise we would get slicing.
   TRACE (return 0;)
}

//TEST// grind="valgrind --leak-check=full --show-reachable=yes"
//TEST// $grind typeid >typeid.out 2>&1
//TEST// mkpspdf typeid.ps typeid.cpp* typeid.out*

