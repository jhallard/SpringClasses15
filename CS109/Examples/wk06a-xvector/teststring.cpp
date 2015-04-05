// $Id: teststring.cpp,v 1.7 2013-08-13 14:53:57-07 - - $

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "xvector.h"

template <typename Iter>
void print (Iter itor, Iter end) {
   for (; itor != end; ++itor) cout << " " << *itor;
}

int main() {
   xvector<string> vs {"hello", "world", "foo", "bar", "baz"};
   xvector<string> vt = vs;
   vs.resize (9, "six");

   while (not vs.empty()) {
      cout << "vs.size = " << vs.size() << ", vs.back() = \""
           << vs.back() << "\"" << endl; 
      vs.pop_back();
   }

   cout << "second string vt:";
   for (auto i = vt.cbegin(); i != vt.cend(); ++i) {
      cout << " " << *i;
   }
   cout << endl;

   cout << "template print:";
   print (vt.begin(), vt.end());
   xvector<string>::iterator j {vt.begin()};
   xvector<string>::const_iterator cj {j};
   ++cj;
   cout << " " << *cj << endl;
   cout << "END" << endl;

   return 0;
}

