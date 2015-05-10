// $Id: main.cpp,v 1.8 2015-04-28 19:23:13-07 - - $

#include <cstdlib>
#include <exception>
#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>

using namespace std;

#include "listmap.h"
#include "xpair.h"
#include "util.h"

using str_str_map = listmap<string,string>;
using str_str_pair = str_str_map::value_type;

// function pre-declarations
bool process_contents(string, listmap<string, string> *);
bool get_file_contents(string, listmap<string,string> *);
string read_from_cin();
void scan_options (int, char**);
string trim_ws(const string &);


// get the options from the argv array
void scan_options (int argc, char** argv) {
   opterr = 0;
   for (;;) {
      int option = getopt (argc, argv, "@:");
      if (option == EOF) break;
      switch (option) {
         case '@':
            traceflags::setflags (optarg);
            break;
         default:
            complain() << "-" << (char) optopt << ": invalid option"
                       << endl;
            break;
      }
   }
}

// takes a filename, inserts the contents of that filename into a
// listmap class to keep track of all of the key/value pairs.
bool get_file_contents(string fn, listmap<string,string> * map) {
  string line;
  ifstream myfile (fn);
  int count = 1;
  if(myfile.is_open()) {
    while(getline(myfile,line)) {
      std::cout << fn << endl << line <<  " " << count++ << endl;
      if(!process_contents(line, map)) {
         // throw error;
      }
    }
    myfile.close();
    return true;
  }

  return false;

}

// used to read from standard input when requested by the user.
string read_from_cin() {

   return "helpme";
}

// process a single input given as a string, either a line from a file
// or from standard input. Edits (inserts and removes) from the given 
// listmap appropriately.
bool process_contents(string content, listmap<string, string> * map) {

   content = trim_ws(content);
   if(content.length() == 0) return true;

   if(content[0] == '#') return true;

   std::size_t found = content.find_first_of("=");

   // if it isn't a comment and has no equals sign it's invalid.
   if(found == string::npos) return false;

   // get the left and right halves around the equals sign
   string left = content.substr(0, found);
   string right = content.substr(found, content.length());

   left = trim_ws(left);
   right = trim_ws(right);

   // key=value case
   if(right.length() && left.length()) {

      // TODO - Lookup to see if left is already a key in the map before
      // we insert like this
      str_str_pair my_pair(left, right);
      map->insert(my_pair);
      return true;
   }
   // key= case 
   else if(left.length() && !right.length()) {
      cout << "key= case, delete key from map" << endl;
   }
   // = value case
   else if(!left.length() && right.length()) {
      cout << "=value case, delete key from map" << endl;
   }

   return true;
}


// @TODO this function is broken, it removes all whitespace not
// just trailing which is not what we wants
string trim_ws(const string & str) {

   string ret = "";
   for(auto c : str) {
      if(c != ' ') {ret.push_back(c);}
   }

   return ret;
}


int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);

   str_str_map main_map; // main listmap for the program

   // there are filenames to be read in
   if(argc-optind+1 > 0) {

      string * filenames = new string[argc-optind+1];
      int curr = 0;

      for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
         filenames[curr++] = *argp; 
      }

      // go through all input and either read from a file or from cin
      // depending on the input value
      for(int i = 0; i < curr; i++) {
         if(filenames[i] == "-") {
            read_from_cin();
         }
         else {
            get_file_contents(filenames[i], &main_map);
         }
      }

      delete [] filenames;
   }
   else {
      while(true) {
         string input = read_from_cin();
         // process input
      }
   }

   // str_str_map test;
   // for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
   //    str_str_pair pair (*argp, to_string<int> (argp - argv));
   //    cout << "Before insert: " << pair << endl;
   //    test.insert (pair);
   // }

   // for (str_str_map::iterator itor = test.begin();
   //      itor != test.end(); ++itor) {
   //    cout << "During iteration: " << *itor << endl;
   // }

   // str_str_map::iterator itor = test.begin();
   // test.erase (itor);

   // cout << "EXIT_SUCCESS" << endl;

   return EXIT_SUCCESS;
}

