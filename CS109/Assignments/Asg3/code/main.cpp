// $Id: main.cpp,v 1.8 2015-04-28 19:23:13-07 - - $

// @author John Allard
// @file main.cpp
// @date May 9th 2015
// @project Asg3 UCSC CMPS-109 

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
      cout << fn << ": " << count++ << ": " << line << endl;
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
   string ret = "";
   getline(cin, ret);
   // cin.get(); // get return here
   return ret;
}

void print_pair(str_str_pair pair) {
   cout << pair.first << " = " << pair.second << endl;
}

// process a single input given as a string, either a line from a file
// or from standard input. Edits (inserts and removes) from the given 
// listmap appropriately.
bool process_contents(string content, listmap<string, string> * map) {

   content = trim_ws(content);

   if(content.length() == 0) return true;

   if(content[0] == '#') return true;
   
   // @TODO - Sort the items in lexographic order before displaying
   // to the user
   if(content[0] == '=' && content.length() == 1) {
      for(auto it = map->begin(); it != map->end(); ++it) {
          print_pair(*it);
      }
      return true;
   }

   std::size_t found = content.find_first_of("=");

   // if it isn't a comment and has no equals sign it must be a key
   // value which means we output the pair if found in the map.
   if(found == string::npos) {
      auto it = map->find(content); 
      // see if key exists in map, if so show pair
      if(it != map->end()) {
         print_pair(*it);
      }
      else {
         cout << content  << ": key not found" << endl;
      }

      return true;
   }


   // get the left and right halves around the equals sign
   string left = content.substr(0, found);
   string right = content.substr(found+1, content.length());

   left = trim_ws(left);
   right = trim_ws(right);

   // key=value case
   if(right.length() && left.length()) {

      str_str_pair my_pair(left, right);

      // see if key already exists in map, if so delete pair
      if(map->find(my_pair.first) != map->end()) {
         map->erase(map->find(my_pair.first));
      }

      map->insert(my_pair);

      print_pair(my_pair);
      return true;
   }
   // key= case 
   else if(left.length() && !right.length()) {
 
      // see if key already exists in map, if so delete pair
      if(map->find(left) != map->end()) {
         map->erase(map->find(left));
      }

   }
   // = value case
   else if(!left.length() && right.length()) {
      for(auto it = map->begin(); it != map->end(); ++it) {
        if(it->second == right) {
           print_pair(*it);
        }
      }
   }

   return true;
}


string trim_ws(const string & str) {
    const auto begin = str.find_first_not_of(" ");
    if (begin == std::string::npos)
        return ""; // no content

    const auto end = str.find_last_not_of(" ");
    const auto diff = end - begin + 1;

    return str.substr(begin, diff);
}


int main (int argc, char** argv) {
   sys_info::set_execname (argv[0]);
   scan_options (argc, argv);

   str_str_map main_map; // main listmap for the program
   int cin_count = 1;

   // there are filenames to be read in
   if(argc-optind > 0) {

      string * filenames = new string[argc-optind+1];
      int curr = 0;

      // put the filenames into their own array
      for (char** argp = &argv[optind]; argp != &argv[argc]; ++argp) {
         filenames[curr++] = *argp; 
      }

      // go through all input and either read from a file or from cin
      // depending on the input value
      for(int i = 0; i < curr; i++) {
         if(filenames[i] == "-") {
            string in = read_from_cin();
            if(cin.eof()) {
              return EXIT_SUCCESS;
            }
            cout << "-: " << cin_count++ << ": " << in << endl;
            process_contents(in, &main_map);
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
         if(cin.eof()) {
          return EXIT_SUCCESS;
         }
         cout << "-: " << cin_count++ << ": " << input << endl;
         process_contents(input, &main_map);
      }
   }
   
   for(auto i = main_map.begin(); i != main_map.end(); ++i) {
   // cout << i->first << " " << i->second << endl;
   }

   return EXIT_SUCCESS;
}

