// $Id: predobjsort.cpp,v 1.5 2015-02-05 19:09:40-08 - - $

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class item_t>
struct incrcmp {
   bool operator () (const item_t &left, const item_t &right) {
      return left < right;
   }
};

template <class item_t>
struct decrcmp {
   bool operator () (const item_t &left, const item_t &right) {
      return left > right;
   }
};

template <class item_t>
struct lengthcmp {
   bool operator () (const item_t &left, const item_t &right) {
      return left.size() < right.size()
          or (not (right.size() < left.size()) and left < right);
   }
};

template <class itor_t>
void print (string label, const itor_t &begin, const itor_t &end) {
   cout << endl << label << " order:" << endl;
   for (itor_t itor = begin; itor != end; ++itor) {
      cout << " " << *itor;
   }
   cout << endl;
}

int main (int argc, char **argv) {
   char **end = argv + argc;
   vector<string> vec;
   for (char **itor = argv; itor < end; ++itor) vec.push_back (*itor);
   print ("initial", vec.begin(), vec.end());

   sort (vec.begin(), vec.end());
   print ("default sort", vec.begin(), vec.end());

   sort (vec.begin(), vec.end(), incrcmp<string>());
   print ("incrcmp<string>", vec.begin(), vec.end());

   sort (vec.begin(), vec.end(), decrcmp<string>());
   print ("decrcmp<string>", vec.begin(), vec.end());

   sort (vec.begin(), vec.end(), lengthcmp<string>());
   print ("lengthcmp<string>", vec.begin(), vec.end());

   return 0;
}

//TEST// predobjsort hello world foo bar baz quux >predobjsort.out 2>&1
//TEST// mkpspdf predobjsort.ps predobjsort.cpp* predobjsort.out

