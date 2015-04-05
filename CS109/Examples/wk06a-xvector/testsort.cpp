// $Id: testsort.cpp,v 1.1 2013-08-16 14:57:39-07 - - $

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#include "xvector.h"

xvector<string> vecvalues {
   "Hello", "World",
   "foo", "bar", "baz", "qux",
   "3.14159265358979",
   "1.61803398874989",
   "2.71828182845905",
   "!@#$%^&*()_+|",
};

template <typename Iterator>
void print (const string& label, Iterator itor, const Iterator &end) {
   cout << label << ":" << endl;
   for (; itor != end; ++itor) {
      cout << "   " << *itor << endl;
   }
}

int main () {
   xvector<string> v1 (vecvalues);
   sort (v1.begin(), v1.end());
   print ("Default sort", v1.cbegin(), v1.cend());

   xvector<string> v2 (vecvalues);
//   sort (v2.begin(), v2.end(), greater<string>());
   print ("Greater sort", v2.cbegin(), v2.cend());

   return 0;
}

