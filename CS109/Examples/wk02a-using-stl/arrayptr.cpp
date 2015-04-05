// $Id: arrayptr.cpp,v 1.4 2015-01-07 15:50:18-08 - - $

//
// Print out addresses of array elements.  Show how to use a 
// pointer to iterate over an array instead of an index.  Show
// how to get the index by subtracting pointers.
//
// Note:  + and - have higher precedences than << and >>.
//

#include <cstdlib>
#include <iomanip>
#include <iostream>

using namespace std;

int main (int argc, char **argv) {
   cout << "argv = " << static_cast<void*> (argv) << endl;
   for (char** itor = argv; itor != &argv[argc]; ++itor) {
      cout << "argv[" << itor - argv << "] = "
           << static_cast<void*> (*itor)
           << " -> \"" << *itor << "\"" << endl;
   }
   cout << "main = " << reinterpret_cast<void*> (main) << endl;
   return EXIT_SUCCESS;
}

//TEST// ./arrayptr foo bar baz qux quux >arrayptr.lis 2>&1
//TEST// mkpspdf arrayptr.ps arrayptr.cpp* arrayptr.lis

