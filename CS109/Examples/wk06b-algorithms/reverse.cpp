// $Id: reverse.cpp,v 1.31 2015-02-05 19:10:01-08 - - $

//
// Show how to reverse a collection using a pair of iterators.
// Reverse requires a bidirectionaly iterator, with ++ and --.
// Also show that pointers can be used as iterators.
//

#include <iostream>
#include <list>
#include <typeinfo>
#include <vector>

#include <cxxabi.h>

using namespace std;

template <typename itor_t>
void xswap (const itor_t &itor1, const itor_t &itor2) {
   typeof (*itor1) tmp = std::move (*itor1);
   *itor1 = std::move (*itor2);
   *itor2 = std::move (tmp);
}

// Reverse a collection from each end.
// Uses a bidirectional iterator.
// Xreverse avoids clash with <algorithm>reverse
// Pass itors by value so we don't need an extra local copy.
template <typename biitor_t>
void xreverse (biitor_t begin, biitor_t end) {
   while (begin != end && begin != --end) {
      xswap (begin, end);
      ++begin;
   }
}


// Print a range using an iterator.
template <typename itor_t>
void print (const itor_t &begin, const itor_t &end) {
   cout << "  ";
   for (itor_t itor = begin; itor != end; ++itor) cout << " " << *itor;
   cout << endl;
}

// Demangle typeinfo names
void print_type (const char *const label, const type_info &info) {
   const char *const name = info.name();
   cout << "   typeid(" << label << ") = " << name << endl;
   int status;
   char *unmangled = abi::__cxa_demangle (name, 0, 0, &status);
   cout << "      unmangled = " << unmangled << endl;
   free (unmangled); // C code allocated by malloc.
}

// Print, reverse, print, reverse.
template <typename itor_t>
void print_reverse_twice (const itor_t &begin, const itor_t &end) {
   print_type ("itor", typeid (typeof (end)));
   print_type ("*itor", typeid (typeof (*end)));
   for (int count = 0; count < 2; ++count) {
      print (begin, end);
      xreverse (begin, end);
   }
}

// Load container with data.
// itor_t must be convertable to container_t::const_iterator.
template <typename container_t, typename itor_t>
void load_container (container_t &cont, itor_t begin, itor_t end) {
   for (itor_t itor = begin; itor != end; ++itor) {
      cont.push_back (*itor);
   }
}


// Put argv into a vector, xreverse, then print.
// Use iterator-style to process argv.
void testvector (char **argv, char **argend) {
   cout << endl << __func__ << ":" << endl;
   vector<string> vec;
   load_container (vec, argv, argend);
   print_reverse_twice (vec.begin(), vec.end());
}

// Put argv into a vector, xreverse, then print.
// Use iterator-style to process argv.
// NOTE: Same code, just a different data structure.
void testlist (char **argv, char **argend) {
   cout << endl << __func__ << ":" << endl;
   list<string> lis;
   load_container (lis, argv, argend);
   print_reverse_twice (lis.begin(), lis.end());
}

// Now actually just use real pointers as iterators.
// NOTE: Same code, just an array instead of iterators.
void testcharstar (char **argv, char **argend) {
   cout << endl << __func__ << ":" << endl;
   print_reverse_twice (argv, argend);
}

// Now actually just use an array of ints.
// NOTE: Same code, just an array instead of iterators.
void testintarray () {
   cout << endl << __func__ << ":" << endl;
   int array[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
   int *end = array + sizeof array / sizeof *array;
   print_reverse_twice (&*array, end);
}

// Main program to call each one in turn.
int main (int argc, char **argv) {
   testvector (argv + 1, argv + argc);
   testlist (argv + 1, argv + argc);
   testcharstar (argv + 1, argv + argc);
   testintarray ();
   return 0;
}

//TEST// ./reverse foo bar baz qux hello world >reverse.out 2>&1
//TEST// mkpspdf reverse.ps reverse.cpp* reverse.out

