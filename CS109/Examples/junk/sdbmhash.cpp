// $Id: sdbmhash.cpp,v 1.2 2013-08-08 20:10:46-07 - - $

#include <functional>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

size_t sdbmhash (const string &str) {
   size_t hash = 0;
   for (auto i = str.begin(); i != str.end(); ++i) {
      hash = *i + (hash << 6) + (hash << 16) - hash;
   }
   return hash;
}
 
int main (int argc, char **argv) {
   for (char **argi = argv + 1; argi != argv + argc; ++argi) {
      string arg = *argi;
      size_t hash = sdbmhash(arg);
      cout << setw (20) << hash << " " << arg << endl;
   }
   return 0;
}
