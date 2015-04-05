// $Id: regex.cpp,v 1.36 2014-05-02 15:54:53-07 - - $

#include <iostream>
#include <regex>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>

//
// NAME
//    regex - test regular expressions
//
// SYNOPSIS
//    regex pattern args...
//
// DESCRIPTION
//    The first argument to the function is a regex pattern which
//    is compiled into a regex.  The rest of the arguments are
//    matched agains the regex to see if they match.
//

int main (int argc, char **argv) {
   cout << "__GLIBCXX__ = " << __GLIBCXX__ << endl;
   string progname {basename (argv[0])};
   if (argc < 3) {
      cerr << "Usage: " << progname << " regex args..." << endl;
      exit (1);
   }
   string pattern {argv[1]};
   vector<string> args {&argv[2], &argv[argc]};
   try {
      regex reg (pattern, regex::egrep | regex::icase);
      cout << "Compiled \"" << pattern << "\"" << endl;
      for (const string& arg: args) {
         cout << "\"" << arg << "\":";
         smatch result;
         if (regex_match (arg, result, reg)) {
            cout << endl;
            cout << "  prefix=" << result.prefix() << endl;
            cout << "  suffix=" << result.suffix() << endl;
            cout << "  str=" << result.str() << endl;
            for (const auto& res: result) {
               cout << "  [" << res << "]" << endl;
            }
         }else {
            cout << " no match" << endl;
         }
      }
   }catch (regex_error& error) {
      cerr << pattern << ": " << error.what() << ": code "
           << error.code() << endl;
      exit (1);
   }
   return 0;
}
