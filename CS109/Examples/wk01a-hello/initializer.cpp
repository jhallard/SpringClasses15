// $Id: initializer.cpp,v 1.5 2014-03-26 17:51:31-07 - - $

//
// Illustrate initializer lists and for loops.
//

#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

int main (int argc, char **argv) {
   vector<string> args (&argv[0], &argv[argc]);
   for (const auto& i: args) cout << i << endl;;
   map<string,double> msd = {{"foo",26}, {"bar",99}, {"baz",-3}};
   for (const auto& i: msd) cout << i.first << " " << i.second << endl;
   return EXIT_SUCCESS;
}

//TEST// ./initializer hello world >initializer.lis 2>&1
//TEST// mkpspdf initializer.ps initializer.cpp* initializer.lis

