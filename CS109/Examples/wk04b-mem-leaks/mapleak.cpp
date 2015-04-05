// $Id: mapleak.cpp,v 1.14 2015-01-26 14:35:42-08 - - $

//
// Illustrate how leaks may happen for a map.
// Use argv to create a series of objects, each of which has a
// string field and which is put in a map.
// If the first argument is "-", erase all map entries.
//

#include <iostream>
#include <map>

using namespace std;

int seqct = 0;
struct object {
   int seqnr;
   string value;
   explicit object (const string& val): seqnr(++seqct), value(val) {}
};

int main (int argc, char** argv) {
   using strobjmap = map<string,object*>;
   strobjmap somap;

   // Push each element of argv into map as object.
   for (int index = 1; index < argc; ++index) {
      string arg = argv[index];
      somap.emplace (strobjmap::value_type (arg, new object (arg)));
   }

   // Iterate over the map, printing out the keys and values.
   for (auto itor = somap.cbegin(); itor != somap.cend(); ++itor) {
      cout << itor->first << " => (" << itor->second->seqnr << ", "
           << itor->second->value << ")" << endl;
   }

   // If the first argument is "-", erase all map entries.
   if (argc > 1 && argv[1][0] == '-') {
      while (somap.size() > 0) {
         auto itor = somap.begin();
         object *second = itor->second;
         somap.erase (itor);
         delete second;
      }
   }

   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind mapleak arguments to check on leak >mapleak.out1 2>&1
//TEST// grind mapleak - arguments to check on leak >mapleak.out2 2>&1
//TEST// mkpspdf mapleak.ps mapleak.cpp* mapleak.out*

