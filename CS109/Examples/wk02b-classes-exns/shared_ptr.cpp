// $Id: shared_ptr.cpp,v 1.5 2014-04-10 14:44:24-07 - - $

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

using namespace std;

int main (int argc, char** argv) {
   auto vecstr = make_shared<vector<shared_ptr<string>>>();
   cout << "vector<string*> = " << vecstr << endl;
   for (auto argp = &argv[1]; argp != &argv[argc]; ++argp) {
      vecstr->push_back (make_shared<string> (*argp));
   }
   for (auto itor = vecstr->cbegin(); itor != vecstr->cend(); ++itor) {
      cout << "string* = " << *itor << " -> " << **itor << endl;
   }
   cerr << "We are done." << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=shared_ptr.out.grind \
//TEST//       shared_ptr foo bar baz qux >shared_ptr.out 2>&1
//TEST// mkpspdf shared_ptr.ps shared_ptr.cpp* shared_ptr.out*
*/

