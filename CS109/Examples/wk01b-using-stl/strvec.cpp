// $Id: strvec.cpp,v 1.24 2014-06-20 21:56:35-07 - - $

//
// NAME
//    strvec - a few random operations on a vector of strings
//

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

void print (const string& s) { cout << "for_each: " << s << endl; }

int main () {
   // Load array into vector.
   vector<string> vecstr {"this", "is", "an", "array", "of", "words"};

   // Print using indices.
   for (size_t index = 0; index < vecstr.size(); ++index) {
      cout << "indexing: " << vecstr[index] << endl;
   }

   // Print using explicit types for iterators.
   for (vector<string>::const_iterator itor = vecstr.cbegin();
        itor != vecstr.cend(); ++itor) {
      cout << "iterator: " << *itor << endl;
   }

   // Print using auto feature.
   for (auto itor = vecstr.cbegin(); itor != vecstr.cend(); ++itor) {
      cout << "auto itor: " << *itor << endl;
   }

   // Print using for-each loop.
   for (const auto& str: vecstr) cout << "for colon: " << str << endl;

   // Print using <algorithm>for_each and a lambda.
   for_each (vecstr.cbegin(), vecstr.cend(),
             [](const string& s) {cout << "lambda: " << s << endl;});

   // Print using <algorithm>for_each and a function.
   for_each (vecstr.cbegin(), vecstr.cend(), print);

   return EXIT_SUCCESS;
}

//TEST// valgrind ./strvec foo bar baz qux quux >strvec.lis 2>&1
//TEST// mkpspdf strvec.ps strvec.cpp* strvec.lis

