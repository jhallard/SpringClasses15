// $Id: vectorleak.cpp,v 1.4 2014-04-22 18:58:28-07 - - $

//
// Illustrate how leaks may happen when a vector of pointers is
// created.  If the vector is not explicitly cleared, when it is
// deleted, the objects it access are not deleted.
//

#include <iostream>
#include <vector>

using namespace std;

int main (int argc, char **argv) {
   vector<string*> vs;
   for (int index = 1; index < argc; ++index) {
      vs.push_back (new string (argv[index]));
   }
   auto begin = vs.begin();
   for (auto itor = begin; itor != vs.end(); ++itor) {
      cout << itor - begin << ": " << *itor << "->" << **itor << endl;
   }
   return 0;
}

/*
//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind vectorleak these are some arguments to check on leak \
//TEST//       >vectorleak.out 2>&1
//TEST// mkpspdf vectorleak.ps vectorleak.cpp* vectorleak.out
*/

