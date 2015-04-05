// $Id: stl-template-list.cpp,v 1.7 2014-07-08 22:33:25-07 - - $

#include <iostream>
#include <list>
using namespace std;

int main() {
   list<int> li = {1, 2, 3, 4, 5};
   int maxcount = 20;
   cout << &li << "[" << sizeof li << "]" << endl;
   cout << "li.cbegin() = " << &*li.cbegin() << endl;
   cout << "li.cend() = " << &*li.cend() << endl;
   for (auto i = li.cbegin(); maxcount-- > 0; ++i) {
      cout << &*i << " -> " << *i << endl;
   }
}

//TEST// stl-template-list >stl-template-list.out 2>&1
//TEST// more stl-template-list.cpp stl-template-list.out \
//TEST//      >stl-template-list.lis 2>&1 </dev/null
//TEST// mkpspdf stl-template-list.ps stl-template-list.lis

