// $Id: template-primes.cpp,v 1.1 2014-07-17 14:09:11-07 - - $

#include <iostream>
using namespace std;

template <int i>
struct D {
   D (void*);
   operator int();
};

template <int p, int i>
struct is_prime {
   enum { prime = (p%i) and is_prime<(i>2?p:0),i>::prime };
};

template <>
struct is_prime<0,0> { enum { prime = 1 }; };

template <>
struct is_prime<0,1> { enum { prime = 1 }; };

template <int i>
struct Prime_print {
   Prime_print<i-1> a;
   enum { prime = is_prime<i,i-1>::prime };
   void f() { D<i> d = prime; }
};

template <>
struct Prime_print<2> {
   enum { prime = 1 };
   void f() { D<2> d = prime; }
};

void foo() {
   Prime_print<10> a;
}

