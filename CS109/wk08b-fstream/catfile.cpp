// $Id: catfile.cpp,v 1.23 2014-05-29 15:32:51-07 - - $

// NAME
//    catfile - concatenate files and print
//
// SYNOPSIS
//    cat [-aemntv] [filename...]
//
// DESCRIPTION
//    Display files to stdout.  If no filenames are specified,
//    read from stdin.  
//
// OPTIONS
//    -a  same as -mntv
//    -e  display $ at end of each line
//    -m  display headings before files as in more(1)
//    -n  display line numbers before each line
//    -v  display all non-isgraph characters visibly

#include <algorithm>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <locale>
#include <stdexcept>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>
#include <unistd.h>


struct {
   string name {};
   int status {EXIT_SUCCESS};
} program;

void error (const string& message) {
   cerr << program.name << ": " << message << endl;
   program.status = EXIT_FAILURE;
}

struct options {
   bool e_endline {};
   bool m_more {};
   bool n_numbers {};
   bool v_visible {};
   vector<string> filenames;
   locale olocale {"en_US.iso88591"};
   options (int argc, char**argv) {
      opterr = false;
      for (;;) {
         int opt = getopt (argc, argv, "aemntv");
         if (opt == EOF) break;
         switch (opt) {
            case 'a': m_more = n_numbers = v_visible = true; break;
            case 'e': e_endline = true; break;
            case 'm': m_more = true; break;
            case 'n': n_numbers = true; break;
            case 'v': v_visible = true; break;
            default:  error (string ("-") + static_cast<char> (optopt)
                             + ": invalid option");
                      break;
         }
      }
      for_each (&argv[optind], &argv[argc],
                [this] (const string& arg) {
                   filenames.push_back (arg);
                });
      if (filenames.size() == 0) filenames.push_back ("-");
   }
};


void copyfile (const string& filename, istream& input,
               const options& opts) {
   if (opts.m_more) {
      string colons {"::::::::::::::::"};
      cout << colons << endl << filename << endl << colons << endl;
   }
   for (int lcount = 1;; ++lcount) {
      string line;
      getline (input, line);
      if (input.eof()) break;
      if (opts.n_numbers) cout << setw(6) << lcount << "\t";
      if (not opts.v_visible) cout << line;
      else {
         for (char byte: line) {
            if (isprint (byte, opts.olocale)) cout << byte;
            else if ((byte & 0x80) == 0) {
               cout << "^" << static_cast<char> (byte ^ 0x40);
            }else {
               cout << "\\x" << setw(2) << hex << uppercase
                    << static_cast<int> (byte & 0xFF);
            }
         }
      }
      if (opts.e_endline) cout << "$";
      cout << endl;
   }
}

int main (int argc, char** argv) {
   program.name = basename (argv[0]);
   options opts (argc, argv);
   for (const auto& filename: opts.filenames) {
      if (filename == "-") copyfile (filename, cin, opts);
      else {
         ifstream infile (filename);
         if (not infile.fail()) copyfile (filename, infile, opts);
         else error (filename + ": " + strerror (errno));
      }
   }
   return program.status;
}

//TEST// ./catfile -a /error in.data 256 >catfile.out 2>&1
//TEST// mkpspdf catfile.ps catfile.cpp* catfile.out

