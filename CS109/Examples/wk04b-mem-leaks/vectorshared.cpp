// $Id: vectorshared.cpp,v 1.4 2014-04-22 19:02:44-07 - - $

//
// Exact copy of vectorleak.cpp, except use shared_ptr instead of
// actual pointers so that memory is released.
//

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

int main (int argc, char **argv) {
   vector<shared_ptr<string>> vs;
   for (int index = 1; index < argc; ++index) {
      vs.push_back (make_shared<string> (argv[index]));
   }
   auto begin = vs.begin();
   for (auto itor = begin; itor != vs.end(); ++itor) {
      cout << itor - begin << ": " << *itor << "->" << **itor << endl;
   }
   return 0;
}

/*
//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind vectorshared these are some arguments to check on leak \
//TEST//       >vectorshared.out 2>&1
//TEST// mkpspdf vectorshared.ps vectorshared.cpp* vectorshared.out
*/

