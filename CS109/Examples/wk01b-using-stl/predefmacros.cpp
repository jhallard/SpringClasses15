// $Id: predefmacros.cpp,v 1.35 2014-03-27 19:17:41-07 - - $

//
// Print out the valuas of various macros and test whether some
// compiler and operating system flags are present.
//
// References:
// http://sourceforge.net/apps/mediawiki/predef/
// See links to Compilers and Operating Systems
//

#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

#ifdef __unix__

#include <cerrno>
#include <cstdio>
#include <cstring>

const string uname_args[] = {
   "kernel-name", 
   "nodename", 
   "kernel-release", 
   "kernel-version", 
   "machine", 
   "processor", 
   "hardware-platform", 
   "operating-system", 
};
const unsigned uname_size = sizeof uname_args / sizeof *uname_args;

void print_unames () {
   const string *const end = uname_args + uname_size;
   string command = "date\n";
   for (const string *itor = uname_args; itor < end; ++itor) {
      command += "echo uname --" + *itor
               + " = `uname --" + *itor + "`\n";
   }
   system (command.c_str());
}

#else

void print_unames () {
   throw "Praeterea, censeo Microflaccidem esse delendam.";
}

#endif


int main () {
   print_unames ();

   cout << "__FILE__ = \"" << __FILE__ << "\"" << endl;
   cout << "__LINE__ = \"" << __LINE__ << "\"" << endl;
   cout << "__func__ = \"" << __func__ << "\"" << endl;
   cout << "__DATE__ = \"" << __DATE__ << "\"" << endl;
   cout << "__TIME__ = \"" << __TIME__ << "\"" << endl;
   cout << "__STDC__ = \"" << __STDC__ << "\"" << endl;
   cout << "__cplusplus = \"" << __cplusplus << "\"" << endl;

   #ifdef __unix__
   cout << "__unix__ = \"" << __unix__ << "\"" << endl;
   #endif

   #ifdef __linux__
   cout << "__linux__ = \"" << __linux__ << "\"" << endl;
   #endif

   #ifdef __x86_64__
   cout << "__x86_64__ = \"" << __x86_64__ << "\"" << endl;
   #endif

   #ifdef __GNUC__
   cout << "__GNUC__ = \"" << __GNUC__ << "\"" << endl;
   cout << "__GNUC_MINOR__ = \"" << __GNUC_MINOR__ << "\"" << endl;
   cout << "__GNUC_PATCHLEVEL__ = \"" << __GNUC_PATCHLEVEL__ << "\""
        << endl;
   #endif

   return 0;
}

//TEST// ./predefmacros >predefmacros.lis 2>&1
//TEST// mkpspdf predefmacros.ps predefmacros.cpp* predefmacros.lis

