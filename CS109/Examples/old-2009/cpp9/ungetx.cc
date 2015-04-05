// $Id: ungetx.cc,v 1.1 2009-01-16 17:22:30-08 - - $

//
// NAME
//    unget - use unget to push a char back into a stream
//
// SYNOPSIS
//    unget
//
// DESCRIPTION
//    Reads characters into a string.  Prints the string whenever
//    a number is read, or when a non-numeric character is read.
//

#include <cstdlib>
#include <iostream>
#include <locale>
#include <string>

using namespace std;

int main (int argc, char **argv) {
   for (;;) {
      char achar;
      cin.get (achar);
      if (cin.eof()) break;
      string token = "";
      if (isspace (achar)) continue;
      if (achar == '_' || isdigit (achar)) {
         token = achar;
         for (;;) {
            cin.get (achar);
            if (cin.eof()) break;
            if (isdigit (achar)) {
               token += achar;
            }else {
               cin.unget();
               break;
            }
         }
      }else {
         token = achar;
      }
      cout << '[' << token << ']' << endl;
   }
   return EXIT_SUCCESS;
}
