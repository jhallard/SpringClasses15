// $Id: prtenv.cc,v 1.1 2009-01-16 17:22:29-08 - - $

//
// NAME
//    printenv - print all or part of an environment
//
// SYNOPSIS
//    printenv [variable...]
//
// DESCRIPTION
//    Prints to stdout all of the environment variables specified
//    on the command line.  If none, prints out the entire
//    environment.
//

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>

using namespace std;

//
// base_execname
//    Get the name of the executable binary being run, and trim
//    the directory portion of the name, if it was given.
//
const string base_execname () {
   string execname = getexecname ();
   return execname.substr (execname.rfind ('/') + 1);
}

//
// Global variables showing program status:
//    program_exit_status - Unix exit status
//    program_name - basename of the program being run
//
static int program_exit_status = EXIT_SUCCESS;
static const string program_name = base_execname ();

//
// warn
//    Print a warning to stderr and set the exit status to failure.
//
void warn (const string object, const string reason) {
   program_exit_status = EXIT_FAILURE;
   cerr << program_name << ": " << object << ": " << reason << endl;
}


//
// print_env_vars
//    Iterate over the vector of environment variables given as
//    an argument, printing out each key and value pair.  Error
//    if one can not be found.
//
void print_env_vars (const char *const *const varnames) {
   for (int vari = 0; varnames[vari] != NULL; ++vari) {
      char *value = getenv (varnames[vari]);
      if (value != NULL) {
         cout << varnames[vari] << " = " << value << endl;
      }else {
         warn (varnames[vari], "variable not in environment");
      }
   }
}

//
// print_env
//    Print all of the environment variables in sorted order.
//    Done by splitting each string in the environment into a
//    key and value pair and then inserting them into a binary
//    search tree (map).  An iterator is then used to print out
//    the tree.
//
void print_env () {
   extern char **environ;
   typedef map <string, string> strstr_map_t;
   typedef strstr_map_t::const_iterator strstr_map_itor_t;
   strstr_map_t env;
   for (int envi = 0; environ[envi] != NULL; ++envi) {
      string keyvalue = environ[envi];
      int eqpos = keyvalue.find ('=');
      assert (eqpos != string::npos);
      string key = keyvalue.substr (0, eqpos);
      string value = keyvalue.substr (eqpos + 1);
      env[key] = value;
   }
   strstr_map_itor_t map_itor = env.begin ();
   const strstr_map_itor_t mapend = env.end ();
   for (; map_itor != mapend; ++map_itor) {
      cout << map_itor->first << " = " << map_itor->second << endl;
   }
}

//
// main
//    Choose one option or the other.
//
int main (int argc, char **argv) {
   if (argc > 1) print_env_vars (argv + 1);
            else print_env ();
   return program_exit_status;
}

