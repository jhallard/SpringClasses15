// $Id: argv.cpp,v 1.5 2014-03-31 13:02:14-07 - - $

//
// NAME
//    argv - print out the argument vector
//
// SYNOPSIS
//    argv [string...]
//
// DESCRIPTION
//    Prints out its arguments to stdout, one per line.
//

#include <cstdlib>
#include <iostream>

using namespace std;

int main (int argc, char** argv) {
   cout << "argc = " << argc << endl;
   for (int argi = 0; argi < argc; ++argi) {
      cout << "argv[" << argi << "] = \"" << argv[argi] << "\""
           << endl;
   }
   return EXIT_SUCCESS;
}

//TEST// ./argv foo bar baz qux quux >argv.lis 2>&1
//TEST// mkpspdf argv.ps argv.cpp* argv.lis

