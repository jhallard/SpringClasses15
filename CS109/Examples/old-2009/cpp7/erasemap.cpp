// $Id: erasemap.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

//
// Show how to erase a map when a map contains strings.
//

#include <cstdlib>
#include <iostream>
#include <map>

using namespace std;

typedef map <int, string *> map_t;;
typedef map_t::iterator map_itor;
typedef map_t::const_iterator map_citor;

void printmap (const string &label, const map_t &argmap) {
   cout << label << ":" << endl;
   for (map_citor itor = argmap.begin(); itor != argmap.end(); ++itor) {
      cout << itor->first << " = " << itor->second << endl;
   }
}

int main (int argc, char **argv) {
   map <int, string *> argmap;
 
   // Copy argv into heap strings and put in argmap.
   for (int argi = 0; argi < argc; ++argi) {
      argmap[argi] = new string (argv[argi]);
   }
   printmap ("First", argmap);

   // Erase the map.
   map_itor itor = argmap.begin();
   map_itor end = argmap.end();
   for (; itor != end; ++itor) {
      delete itor->second;
      argmap.erase (itor);
   }
   printmap ("Seconde", argmap);

   return EXIT_SUCCESS;
}

