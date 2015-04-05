// $Id: testint.cpp,v 1.11 2014-07-09 13:00:06-07 - - $

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "xvector.h"

void printvec (const string& label, const xvector<int>& vec) {
   cout << label << ":";
   for (size_t i {0}; i < vec.size(); ++i) {
      cout << " [" << i << "]" << vec[i];
   }
   cout << endl;
}

int main() {
   xvector<int> aa {10, 20, 30, 40, 50, 60, 70, 80, 90};
   xvector<int> va;
   cout << "sizeof aa = " << sizeof aa << endl;
   cout << "sizeof va = " << sizeof va << endl;

   printvec ("loop1(aa)", aa);
   for (auto& i: aa) va.push_back (i);

   for (auto i = va.cbegin(); i != va.cend(); ++i) {
      cout << "loop2: " << &*i << "->" << *i << endl;
   }

   printvec ("loop3(va)", va);

   xvector<int> vb (va);
   xvector<int>::iterator j {vb.begin()};
   xvector<int>::const_iterator cj {j};

   ++cj;
   cout << &*cj << ": " << *j << " " << *cj << endl;

   //xvector<int>::iterator k = cj;
   //error: conversion from 'xvector_iterator<const int>'
   //to non-scalar type 'xvector_iterator<int>' requested

   xvector<int> bb {10, 20, 30, 45};
   printvec ("compare(aa)", aa);
   printvec ("compare(bb)", bb);
   cout << "aa < bb = " << boolalpha << (aa < bb) << endl;

   return 0;
}

