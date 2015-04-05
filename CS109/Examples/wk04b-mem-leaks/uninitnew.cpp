// $Id: uninitnew.cpp,v 1.2 2014-04-22 18:55:00-07 - - $o

//
// Illustrates the uninitialized behavior of areas returned by
// new when there is no default ctor, as for primitives and pointers.
// Allocate an array, print non-zero entries, then free the array.
// check for memory leak.
//

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void f(int n) {
   cout << n << ":";
   int *p = new int[n];
   for (int i = 0; i < n; ++i) {
      if (p[i]!=0) cout << " " << dec << i << "=" << hex << p[i] << ";";
      p[i] = 0xDEADBEEF;
   }
   cout << endl;
   delete[] p;
}

void g() {
   vector<int*> vi(5);
   cout << "g:";
   for (size_t i = 0; i < vi.size(); ++i) cout << " " << vi[i];
   cout << endl;
}

int main() {
   f(10);
   f(5);
   f(6);
   f(100);
   f(8);
   g();
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind uninitnew >uninitnew.out 2>&1
//TEST// mkpspdf uninitnew.ps uninitnew.cpp* uninitnew.out

