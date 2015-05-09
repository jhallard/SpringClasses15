// $Id: catfile.cpp,v 1.7 2015-04-23 16:34:44-07 - - $

//
// NAME
//    catfile - display files to stdout
//
// SYNOPSIS
//    catfile [filename...]
//
// DESCRIPTION
//    Display contents of files given on the command line.  If no
//    files are specified, display stdin.  Interpret "-" as the 
//    name of stdin.
//

#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>

const string cin_name = "-";

void catfile (istream& infile, const string& filename) {
   static string colons (32, ':');
   cout << colons << endl << filename << endl << colons << endl;
   for(;;) {
      string line;
      getline (infile, line);
      if (infile.eof()) break;
      cout << line << endl;
   }
}


int main (int argc, char** argv) {
   int status = 0;
   string progname (basename (argv[0]));
   vector<string> filenames (&argv[1], &argv[argc]);
   if (filenames.size() == 0) filenames.push_back (cin_name);
   for (const auto& filename: filenames) {
      if (filename == cin_name) catfile (cin, filename);
      else {
         ifstream infile (filename);
         if (infile.fail()) {
            status = 1;
            cerr << progname << ": " << filename << ": "
                 << strerror (errno) << endl;
         }else {
            catfile (infile, filename);
            infile.close();
         }
      }
   }
   return status;
}

//TEST// date >date.out
//TEST// ls -bgoa date* catfile* | catfile - date.out >catfile.out
//TEST// rm date.out
//TEST// mkpspdf catfile.ps catfile.cpp* catfile.out

