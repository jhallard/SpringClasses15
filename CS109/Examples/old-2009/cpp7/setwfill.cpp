// $Id: setwfill.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

// Use of set width.

#include <iomanip>
#include <iostream>

using namespace std;

int main (int argc, char **argv) {
   cout << setw(4) << setfill('0') << 20 << endl;
   cout << setw(8) << setfill('x') << 1 << endl;
   cout << 6 << endl;
   return 0;
}

