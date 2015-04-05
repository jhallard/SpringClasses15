// $Id: hashmap.cpp,v 1.4 2013-08-30 18:28:53-07 - - $

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

int main (int argc, char **argv) {
   unordered_map<string,int> h;
   for (int i = 0; i < argc; ++i) {
      h.insert ({argv[i], i});
   }
   for (auto i = h.cbegin(); i != h.cend(); ++i) {
      cout << &*i << ": {" << i->first << "," << i->second << "}"
           << endl;
   }
}
