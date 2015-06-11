// $Id: ch256.cpp,v 1.1 2014-05-29 14:49:54-07 - - $

#include <iostream>
using namespace std;

int main() {
   for (int c = 0; c < 255; ++c) {
      cout << static_cast<char> (c);
      if ((c & 0x1F) == 0x1F) cout << endl;
   }
}
