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

bool get_file_contents(string fn, listmap<string,string> * map) {
  string line;
  ifstream myfile (fn);
  if(myfile.is_open()) {
    while(getline(myfile,line)) {
      std::cout << line << endl;
      str_str_pair my_pair(line, line);
      map->insert(my_pair);
    }
    myfile.close();
    return true;
  }

  return false;

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

      for(int i = 0; i < curr; i++) {
         get_file_contents(filenames[i], &main_map);
      }

      delete [] filenames;
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

