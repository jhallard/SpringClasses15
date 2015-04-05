// $Id: searching.cpp,v 1.5 2012-06-04 14:35:45-07 - - $

//
// Generic algorithms.
// Searching.
//

#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

// Linear search.
// Uses an input iterator.
// Assumes operator== on the element type.

template <typename input_itor, typename element>
input_itor linear_find (const input_itor &begin, const input_itor &end,
                        const element &key) {
   input_itor itor = begin;
   for (; itor != end; ++itor) if (*itor == key) break;
   return itor;
}

// Binary search.
// Uses a random iterator.
// Assumes operator== and operator< on the element type.
// Inefficient in that it uses both == and < instead of just a cmp.

template <typename random_itor, typename element>
random_itor binary_find (const random_itor &begin,
                         const random_itor &end,
                         const element &key) {
   random_itor low = begin;
   random_itor high = end - 1;
   while (low <= high) {
      random_itor mid = low + (high - low) / 2;
      if (*mid == key) return mid;
      if (*mid < key) low = mid + 1;
                 else high = mid - 1;
   }
   return end;
}


// Print function.
// Prints the value or message not found.

template <typename itor>
void print (itor value, itor end) {
   if (value == end ) cout << "not found" << endl;
                 else cout << *value << " found" << endl;
}

// Main.
// Test harness.

int main () {
   int array[] = {1, 3, 5, 11, 16, 24, 32, 88};
   int *arrayend = array + sizeof array / sizeof *array;
   vector <int> vi;
   for (int *aip = array; aip < arrayend; ++aip) vi.push_back (*aip);
   print (linear_find (vi.begin (), vi.end(), 16), vi.end ());
   print (linear_find (vi.begin (), vi.end(), 26), vi.end ());
   print (binary_find (vi.begin (), vi.end(), 16), vi.end ());
   print (binary_find (vi.begin (), vi.end(), 26), vi.end ());
}

//TEST// ./searching >searching.out 2>&1
//TEST// mkpspdf searching.ps searching.cpp* searching.out

