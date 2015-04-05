// $Id: operstring.cpp,v 1.1 2013-08-06 15:19:32-07 - - $

#include <iostream>

using namespace std;

struct bigint {
   char *data;
   bigint (const char *p): data(p) {}
}

bigint operator""big (const char *p) {
   return bigint (p);
}

struct degrees {
   double value;
   degrees (long double d): value(d) {}
}

constexpr operator""deg (long double d) {
   return degrees (d);
}

int main() {
   bigint b = 12345big;
   degrees d = 90deg;
   cout << b.data << endl;
   cout << d.value << endl;
   return 0;
}
