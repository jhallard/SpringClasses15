// $Id: args.cpp,v 1.5 2015-03-31 17:55:46-07 - - $

//
// NAME
//    args - print out the argument vector
//
// SYNOPSIS
//    args [string...]
//
// DESCRIPTION
//    Prints out its arguments to stdout, one per line.
//

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main (int argc, char** argv) {
   string execname {argv[0]};
   vector<string> args (&argv[1], &argv[argc]);
   cout << "execname = " << execname << endl;
   for (const auto& arg: args) cout << arg << endl;
   return EXIT_SUCCESS;
}

//TEST// ./args foo bar baz qux quux >args.lis 2>&1
//TEST// mkpspdf args.ps args.cpp* args.lis

