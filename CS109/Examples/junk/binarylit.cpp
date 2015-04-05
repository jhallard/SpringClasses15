// $Id: binarylit.cpp,v 1.16 2013-07-25 19:42:18-07 - - $

#include <bitset>
#include <climits>
#include <iomanip>
#include <iostream>

using namespace std;

const size_t shortbits = CHAR_BIT * sizeof (short);

int main() {
   short a = 0b10001111;
   bitset<shortbits> b {a};
   cout << b << endl;
   cout << setw(shortbits) << oct << a << endl;
   cout << setw(shortbits) << dec << a << endl;
   cout << setw(shortbits) << uppercase << hex << a << endl;
   return 0;
}
