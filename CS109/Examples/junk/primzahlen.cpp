// $Id$

// http://www.erwin-unruh.de/primorig.html

// Das folgende Programm ist das Original (neu abgetippt). Ich habe
// auch gleich die Ausgabe des Metaware Compilers mit angefügt. Es
// ist ist nicht mehr gültiges C++. Eine neuere Variante ist hier.

// Prime number computation by Erwin Unruh

template <int i>
struct D { D(void*); operator int(); };

template <int p, int i>
struct is_prime {
    enum { prim = (p%i) && is_prime<(i > 2 ? p : 0), i -1> :: prim };
};

template <int i>
struct Prime_print {
    Prime_print<i-1> a;
    enum { prim = is_prime<i, i-1>::prim };
    void f() { D<i> d = prim; }
    };

template <>
struct is_prime<0,0> { enum {prim=1}; };

template <>
struct is_prime<0,1> { enum {prim=1}; };

template <>
struct Prime_print<2> { enum {prim = 1}; void f() { D<2> d = prim; } };

#ifndef LAST
#define LAST 10
#endif

main () {
    Prime_print<LAST> a;
} 

