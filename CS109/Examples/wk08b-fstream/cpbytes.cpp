// $Id: cpbytes.cpp,v 1.18 2014-05-29 15:28:06-07 - - $

//
// NAME
//    cpbytes - copy binary file
//
// SYNOPSIS
//    cpbytes infile outfile
//
// DESCRIPTION
//    Uses ifstream and ofstream to copy bytes from the infile
//    to the outfile.
//

#include <cerrno>
#include <cstring>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

string execname;
struct cpbytes_exit: public exception {};

struct sys_errno: public runtime_error {
   sys_errno (const string& obj):
              runtime_error (obj + ": " + strerror (errno)){}
};

void usage (const string& execname) {
   cerr << "Usage: " << execname << " infile outfile" << endl;
   throw cpbytes_exit();
}


int main (int argc, char** argv) {
   execname = argv[0];
   int exit_status {EXIT_SUCCESS};
   try {
      if (argc != 3) usage (execname);
      string infilename {argv[1]};
      string outfilename {argv[2]};
      ifstream infile {infilename};
      if (infile.fail()) throw sys_errno (infilename);
      ofstream outfile {outfilename};
      if (outfile.fail()) throw sys_errno (outfilename);
      while (not infile.eof()) {
         char buffer[0x100];
         infile.read (buffer, sizeof buffer);
         outfile.write (buffer, infile.gcount());
      }
   }catch (sys_errno& error) {
      cerr << execname << ": " << error.what() << endl;
      exit_status = EXIT_FAILURE;
   }catch (cpbytes_exit&) {
      exit_status = EXIT_FAILURE;
   }
   return exit_status;
}

