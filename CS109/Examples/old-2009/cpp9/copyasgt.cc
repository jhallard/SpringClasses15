// $Id: copyasgt.cc,v 1.4 2009-01-16 17:16:30-08 - - $

#include <iostream>
#include <string>

using namespace std;

class foo {
   private:
      int x;
   public:
      foo(): x(0) {};
      foo (const foo &y) {
         x = y.x;
         cout << "copy ctor" << x << endl;
      }
      foo &operator= (const foo &y) {
         x = y.x;
         cout << "op =" << x << endl;
         return *this;
      }
};

int main () {
   foo x;
   foo y (x);
   foo z = x;
   y = z;
}
