// $Id: hash.cpp,v 1.5 2013-03-11 21:38:15-07 - - $

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;
 
int main (int argc, char **argv) {
   hash<string> hash_fn;
   for (char **argi = argv + 1; argi != argv + argc; ++argi) {
      string arg = *argi;
      size_t hash = hash_fn(arg);
      cout << setw (20) << hash << " " << arg << endl;
   }
   return 0;
}
