// $Id: leaks.cpp,v 1.4 2014-04-10 14:17:42-07 - - $

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main (int argc, char** argv) {
   vector<string*> *vecstr = new vector<string*>();
   cout << "vector<string*> = " << vecstr << endl;
   for (int itor = 0; itor < argc; ++itor) {
      string str = argv[itor];
      vecstr->push_back (new string(str));
   }
   for (auto itor = vecstr->cbegin(); itor != vecstr->cend(); ++itor) {
      cout << "string* = " << *itor << " -> " << **itor << endl;
   }
   cerr << "We are done." << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=leaks.out.grind \
//TEST//       leaks foo bar baz qux >leaks.out 2>&1
//TEST// mkpspdf leaks.ps leaks.cpp* leaks.out*
*/

