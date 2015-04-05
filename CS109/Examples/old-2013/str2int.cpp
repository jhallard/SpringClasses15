// $Id: str2int.cpp,v 1.1 2013-07-26 20:10:49-07 - - $

//
// NAME
//    str2int - print out argv elements that are ints
//
// SYNOPSIS
//    str2int [string...]
//
// DESCRIPTION
//    Prints out its arguments that are ints, and errors if not.
//    Implement str2int function via iterator.
//

#include <cstdlib>
#include <iostream>
#include <locale>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

int str2int (const string &number) {
   invalid_argument invalid_int ("invalid int: " + number);
   int value = 0;
   bool negative = false;
   string::const_iterator itor = number.begin();
   const string::const_iterator end = number.end();
   if (itor == end) throw invalid_int;
   if (*itor == '-') negative = true, ++itor;
   if (itor == end) throw invalid_int;
   for (; itor != end; ++itor) {
      if (! isdigit (*itor)) throw invalid_int;
      value = value * 10 + *itor - '0';
   }
   if (negative) value = -value;
   return value;
}

//
// For each element of argv, convert to integer and print,
// else catch an exception and print an error message.
//
int main (int argc, char **argv) {
   for (int argi = 1; argi < argc; ++argi) {
      string arg = argv[argi];
      cout << "\"" << arg << "\"";
      try {
         int value = str2int (arg);
         cout << " = " << value << endl;
      }catch (invalid_argument &exn) {
         cout << ": " << exn.what() << endl;
      }
   }
   return EXIT_SUCCESS;
}

/*
//TEST// runprogram.perl -x str2int.lis ./str2int \
//TEST//       1024 56foobar -45 68.9 testing 007777 0x48 2147483648
//TEST// mkpspdf str2int.ps str2int.cpp* str2int.lis
*/

