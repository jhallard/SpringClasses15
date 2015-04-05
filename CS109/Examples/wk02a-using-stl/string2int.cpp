// $Id: string2int.cpp,v 1.15 2014-06-20 22:46:10-07 - - $

//
// NAME
//    str2int-stream - print out argv elements that are ints
//
// SYNOPSIS
//    str2int-stream [string...]
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

int from_string (const string &arg) {
   stringstream stream (arg);
   int result;
   if (not (stream >> result and stream.eof())) {
      throw domain_error ("int from_string (" + arg + ")");
   }
   return result;
}

int main (int argc, char **argv) {
   cout << boolalpha;
   vector<string> args (&argv[0], &argv[argc]);
   for (const auto& arg: args) {
      cout << "\"" << arg << "\"" << endl;
      try {
         int number = from_string (arg);
         cout << "        success: number = " << number << endl;
      }catch (const domain_error &error) {
         cout << "        failure: " << error.what() << endl;
      }
   }
   return 0;
}

/*
//TEST// ./string2int 1024 56foobar -45 68.9 testing 007777 0x48 \
//TEST//          2147483648 2>&1 >string2int.output
//TEST// mkpspdf string2int.ps string2int.cpp* string2int.output
*/

