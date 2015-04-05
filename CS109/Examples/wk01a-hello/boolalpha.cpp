// $Id: boolalpha.cpp,v 1.4 2014-03-27 19:03:31-07 - - $

// Printing booleans as alpha.

#include <cstdlib>
#include <iostream>

using namespace std;

void true_false () {
   cout << "true = " << true << ", false = " << false << endl;
}

int main (int argc, char **argv) {
   (void) argc; // SUPPRESS: warning: unused parameter 'argc'
   (void) argv; // SUPPRESS: warning: unused parameter 'argv'

   true_false ();
   cout << boolalpha;
   true_false ();
   return EXIT_SUCCESS;
}

//TEST// ./boolalpha 1>boolalpha.out 2>&1
//TEST// catnv boolalpha.cpp.log boolalpha.out >boolalpha.lis
//TEST// rm -v boolalpha.cpp.log boolalpha.out
//TEST// mkpspdf boolalpha.ps boolalpha.cpp* boolalpha.lis

