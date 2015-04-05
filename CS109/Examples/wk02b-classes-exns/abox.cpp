// $Id: abox.cpp,v 1.12 2014-04-10 14:12:07-07 - - $

// Class abox showing default ctor, copy ctor, operator=, dtor.

#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

#define LINE "[" << __LINE__ << "] "
#define IDENT(name) \
        cout << LINE << reinterpret_cast<const void*> (this) \
             << "->" << name << ": value=" << value << endl; 
#define SHOW(STMT) \
        cout << LINE << "SHOW(" << #STMT << "):" << endl; \
        STMT; \
        cout << endl;

/////////////////////////////////////////////////////////////////
// abox.h
/////////////////////////////////////////////////////////////////

class abox {
   private:
      int value;
   public:
      abox();                          // default ctor
      abox (const abox&);              // copy ctor
      abox& operator= (const abox&);   // copy operator=
      ~abox();                         // dtor
      abox (abox&&);                   // C++11 move ctor
      abox& operator= (abox&&);        // C++11 move operator=
      abox (int);                      // implicit int->abox conv
      operator int() const;            // implicit abox->int conv
      abox& operator++();              // prefix ++
      abox operator++ (int);           // postfix ++
};

/////////////////////////////////////////////////////////////////
// abox.cpp
/////////////////////////////////////////////////////////////////

abox::abox(): value(0) { // default ctor
   IDENT ("abox::abox()");
}

abox::abox (const abox& init): value(init.value) { // copy ctor
   IDENT ("abox::abox(const abox&)");
}

abox& abox::operator= (const abox& that) { // copy operator=
   if (this != &that) {
      this->value = that.value;
   }
   IDENT ("abox::operator= (const abox&)");
   return *this;
}

abox::~abox() { // dtor
   IDENT ("abox::~abox()");
}

abox::abox (abox&& init): value(init.value) { // C++11 move ctor
   IDENT ("abox::abox(abox&&)");
}

abox& abox::operator= (abox&& that) { // C++11 move operator=
   if (this != &that) {
      this->value = that.value;
   }
   IDENT ("abox::operator= (abox&&)");
   return *this;
}

abox::abox (int init): value(init) { // implicit int->abox conv
   IDENT ("abox::abox(int)");
}

abox::operator int() const { // implicit abox->int conv
   IDENT ("abox::operator int()");
   return value;
}

abox& abox::operator++() { // prefix ++
   ++value;
   return *this;
}

abox abox::operator++ (int) { // postfix ++
   abox result = value;
   value++;
   return result;
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

void ref_fn (const abox& that) {
   SHOW (cout << "ref_fn, that=" << that << endl);
}

void value_fn (const abox that) {
   SHOW (cout << "value_fn, that=" << that << endl);
}

int main() {
   SHOW (abox a);
   SHOW (abox b = a);
   SHOW (abox c (a));
   SHOW (abox d = 6);
   SHOW (b = 3);
   SHOW (ref_fn (6));
   SHOW (ref_fn (a));
   SHOW (value_fn (a));
   SHOW (abox ii = 255);
   SHOW (int i = ii);
   SHOW (cout << i << endl);
   cout << '\f' << endl;
   SHOW (abox *p = new abox (6));
   SHOW (delete p);
   SHOW (abox *bb = new abox[3]);
   SHOW (delete[] bb);
   SHOW (vector<abox> vb);
   SHOW (vb.push_back (6));
   SHOW (vb.push_back (8));
   SHOW (cout << (a = d++) << endl;);
   SHOW (cout << (a = ++d) << endl;);
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=abox.lis.grind abox >abox.lis 2>&1
//TEST// mkpspdf abox.ps abox.cpp* abox.lis*
*/

