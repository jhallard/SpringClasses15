// $Id: uninit.cpp,v 1.1 2012-04-10 19:08:04-07 - - $

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void foo (int an_int) {
   cout << "foo: " << an_int << endl;
   an_int = 12345;
   int before = 6666;
   int array[5];
   int after = 8888;
   cout << "before = " << before << endl;
   cout << "array[-1] = " << array[-1] << endl;
   cout << "array[6] = " << array[6] << endl;
   cout << "after = " << after << endl;
}

int main (int argc, char **argv) {
   int an_int;
   cout << an_int << endl;
   foo (an_int);
   foo (an_int);
   if (an_int > 0) cout << "greater" << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=uninit.out.grind \
//TEST//       uninit foo bar baz qux >uninit.out 2>&1
//TEST// mkpspdf uninit.ps uninit.cpp* uninit.out*
*/

