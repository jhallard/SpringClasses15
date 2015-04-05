// $Id: testpointer.cpp,v 1.3 2015-02-03 13:06:33-08 - - $

#include <iomanip>
#include <iostream>

using namespace std;

#include "xvector.h"

struct node {
   int a;
   int b;
   node (int ai = 0, int bi = 0): a(ai), b(bi) {}
};

int main() {
   xvector<int*> vecpi;
   for (int i = 0; i < 10; ++i) vecpi.push_back (new int (i));
   for (auto it = vecpi.begin(); it != vecpi.end(); ++it) **it *= **it;
   cout << "vecpi:";
   for (auto it = vecpi.begin(); it != vecpi.end(); ++it)
        cout << " " << **it;
   cout << endl;
   while (not vecpi.empty()) {
      int *ip = vecpi.back();
      vecpi.pop_back();
      delete ip;
   }

   xvector<node> vecn;
   for (int i = 0; i < 10; ++i) vecn.push_back (node (i, i * i));
   cout << "vecn:";
   for (auto i = vecn.cbegin(); i != vecn.cend(); ++i) {
      cout << " (" << (*i).a << "," << i->b << ")";
   }
   cout << endl;

   xvector<node*> vecpn;
   for (int i = 0; i < 10; ++i) vecpn.push_back (new node (i, i * i));
   for (auto i = vecpn.cbegin(); i != vecpn.cend(); ++i) {
      cout << "vecpn: " << *i << "->(" << (**i).a << "," << (*i)->b
           << ")" << endl;
   }
   while (not vecpn.empty()) {
      delete vecpn.back();
      vecpn.pop_back();
   }

   return 0;
}
