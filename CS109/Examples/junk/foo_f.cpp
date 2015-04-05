// $Id: foo_f.cpp,v 1.1 2013-08-08 17:42:42-07 - - $

#include <iostream>
using namespace std;

#define T(X) cout << __func__ << "[" << __LINE__ << "]: " << X

#define U(X) T(#X) << endl; X

#define D(X,Y) X { T(#X) << " " << this << endl; Y; }

struct foo {
   D(foo(),)
   D(~foo(),)
   D(foo (const foo &),)
   D(foo (foo &&),)
   D(foo &operator= (const foo &),return *this)
   D(foo &operator= (foo &&),return *this)
};

foo f() {
   U()
   U(foo g;)
   U(return g;)
}

int main() {
   U(foo h;)
   U(h = f();)
   U(return 0;)
}
