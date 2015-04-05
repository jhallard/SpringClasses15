// $Id: stoi.cpp,v 1.15 2014-04-09 15:28:50-07 - - $

//
// NAME
//    stoi - print out argv elements that are ints
//
// SYNOPSIS
//    stoi [string...]
//
// DESCRIPTION
//    Prints out its arguments that are ints, and which are not.
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

int main (int argc, char **argv) {
   cout << boolalpha;
   for (const auto& arg: vector<string> (&argv[1], &argv[argc])) {
      cout << "\"" << arg << "\": ";
      try {
         size_t endpos;
         int number = stoi (arg, &endpos);
         if (endpos == arg.size()) {
            cout << "good number = " << number << endl;
         }else {
            cout << "bad number = " << number << ", trailing junk = \""
                 << arg.substr (endpos) << "\"" << endl;
         }
      }catch (invalid_argument &error) {
         cout << "invalid_argument (" << error.what() << ")" << endl;
      }catch (out_of_range &error) {
         cout << "out_of_range (" << error.what() << ")" << endl;
      }
   }
}

/*
//TEST// ./stoi 1024 56foobar -45 68.9 testing 007777 0x48 \
//TEST//        2147483648 >stoi.lis
//TEST// mkpspdf stoi.ps stoi.cpp* stoi.lis
*/

