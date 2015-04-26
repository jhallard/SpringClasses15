// $Id: main.cpp,v 1.4 2014-06-10 20:08:02-07 - - $

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>

#include "hello.h"

int main (int argc, char** argv) {
   string execname {basename (argv[0])};
   vector<string> args (&argv[1], &argv[argc]);
   cout << execname << endl;
   auto hello_ptr = make_shared<hello>();
   hello_ptr->say (cout);
   hello goodbye {"Goodbye, world!"};
   goodbye.say (cout);
   hello second {*hello_ptr};
   second.say (cout);
   for (const auto& arg: args) cout << "for: " << arg << endl;
   for_each (&argv[0], &argv[argc],
             [=] (const char* arg) {
                cout << "for_each: " << arg << endl;
             });
   return EXIT_SUCCESS;
}

