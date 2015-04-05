// $Id: cinread.cc,v 1.1 2009-01-16 15:13:39-08 - - $

//
// NAME
//    cinread - read input from cin in various ways
//
// SYNOPSIS
//    cinread
//
// DESCRIPTION
//    Read input from cin and print the data.
//
// OPTIONS
//    argv contains a single letter specifying the option
//    c  read using cin >> char
//    s  read using cin >> string
//    g  read using cin.get (char)
//    l  read using getline (istream&, string&)
//

#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

string execname () {
   string execname = getexecname();
   return execname.substr (execname.rfind ('/') + 1);
}

void cin_char() {
   char achar;
   while (cin >> achar) {
      if (achar == '\n') cout << "\\n\n";
                    else cout << "[" << achar << "]";
   }
}

void cin_string() {
   string astring;
   while (cin >> astring) {
      cout << "[" << astring << "]\n";
   }
}

void cin_get() {
   char achar;
   for (;;) {
      cin.get (achar);
      if (cin.eof()) break;
      if (achar == '\n') cout << "\\n\n";
                    else cout << "[" << achar << "]";
   }
}

void cin_getline() {
   string astring;
   for (;;) {
      getline (cin, astring);
      if (cin.eof()) break;
      cout << "[" << astring << "]\n";
   }
}

int main (int argc, char **argv) {
   if (argc <= 1) {
      cerr << "Usage: " << execname() << " c|s|g|l" << endl;
      return EXIT_FAILURE;
   }
   switch (*argv[1]) {
      case 'c': cin_char();    break;
      case 's': cin_string();  break;
      case 'g': cin_get();     break;
      case 'l': cin_getline(); break;
   }
   return EXIT_SUCCESS;
}
