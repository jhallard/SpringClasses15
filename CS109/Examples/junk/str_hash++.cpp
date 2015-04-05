// $Id: str_hash++.cpp,v 1.12 2013-08-07 12:52:21-07 - - $

//
// This program is not part of your project.  It exists just to 
// illustrate how to obtain and print hash values.  Each element
// of argv is hashed and printed along with its hashcode.
//

#include <functional>
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

int main (int argc, char **argv) {
   size_t const width = 20;
   hash<string> str_hash;
   for (int argi = 0; argi < argc; ++argi) {
      string const str = argv[argi];
      size_t const hash_value = str_hash (str);
      cout << setw (width) << hash_value << " = hash(\"" << str
           << "\")" << endl;
   }
   size_t const max = numeric_limits<size_t>::max();
   cout << setw (width) << max
        << " = 0x" << hex << uppercase << max
        << " = " << nouppercase << (long double) (max) << endl;
   return EXIT_SUCCESS;
}

