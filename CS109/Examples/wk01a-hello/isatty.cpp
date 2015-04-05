// $Id: isatty.cpp,v 1.14 2015-01-07 15:06:54-08 - - $

//
// NAME
//    isatty - check if cin, cout, and cerr are ttys
//
// SYNOPSIS
//    isatty
//
// DESCRIPTION
//    Examines the file descriptors associated with cin, cout,
//    and cerr and says whether or not they are ttys.  Redirection
//    to/from a pipe or file will make them not.
//

#include <cerrno>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include <libgen.h>
#include <unistd.h>

// Declare standard file descriptors.
enum class FD {CIN = 0, COUT = 1, CERR = 2};

int exit_status = EXIT_SUCCESS;
string exec_name = "";

void report (string filename, FD filedes) {
   errno = 0;
   bool istty = isatty (int (filedes)) != 0;
   if (errno != 0) {
      cerr << exec_name << ": " << filename << ": fd " << int (filedes)
           << ": " << strerror (errno) << endl;
      exit_status = EXIT_FAILURE;
   }else {
      char* name = ttyname (int (filedes));
      cout << filename << (istty ? " is" : " is not") << " a tty";
      if (name != nullptr) cout << " named " << name;
      cout << endl;
   }
        
}

int main (int argc, char **argv) {
   (void) argc; // SUPPRESS: warning: unused parameter 'argc'
   exec_name = basename (argv[0]);
   report ("cin", FD::CIN);
   report ("cout", FD::COUT);
   report ("cerr", FD::CERR);
   return exit_status;
}

//TEST// ./isatty 1>isatty.out 2>isatty.err
//TEST// catnv isatty.cpp.log isatty.out isatty.err >isatty.lis
//TEST// rm -v isatty.cpp.log isatty.out isatty.err
//TEST// mkpspdf isatty.ps isatty.cpp* isatty.lis

