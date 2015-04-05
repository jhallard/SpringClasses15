// $Id: teststack.cc,v 1.5 2009-03-06 20:04:35-08 - - $

#include <cstdlib>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>

using namespace std;

#include "arraystack.h"
#include "linkedstack.h"
#include "stack.h"

template <class item_t>
void teststack (stack <item_t> &astack, const vector<item_t> &args) {
   vector<item_t>::const_iterator itor = args.begin ();
   const vector<item_t>::const_iterator end = args.end ();
   cout << endl;
   cout << "stack type: " << endl << typeid (astack).name () << endl;
   cout << "vector type: " << endl << typeid (args).name () << endl;
   for (; itor != end; ++itor) {
      cout << "Pushing: " << *itor << endl;
      astack.push (*itor);
   }
   while (! astack.empty ()) {
      cout << "Popping: " << astack.pop () << endl;
   }
   
}

int main (int argc, char **argv) {
   vector<string> args;
   for (int argi = 1; argi < argc; ++argi) args.push_back (argv[argi]);
   cout << "\f" << endl;
   teststack (arraystack<string> (), args);
   cout << "\f" << endl;
   teststack (linkedstack<string> (), args);
   cout << "\f" << endl;
   return EXIT_SUCCESS;
}

