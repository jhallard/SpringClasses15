// $Id: const.cpp,v 1.1 2013-08-15 18:45:22-07 - - $

#include <iostream>
using namespace std;

template <typename T>
class foo {
   T x;
public:
   foo (const T& y = T()): x(y) {}
   void bar() {
      cout << is_const<T>::value << endl;
   }
};

int main() {
   foo<int> a;
   foo<const int> b;
   a.bar();
   b.bar();
}
