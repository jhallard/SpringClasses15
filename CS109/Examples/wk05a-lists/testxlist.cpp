// $Id: testxlist.cpp,v 1.3 2013-08-21 12:37:12-07 - - $

#include <cxxabi.h>
#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;

#include "xlist.h"

template <typename T>
ostream& show_node (typename xlist<T>::node* np) {
   cout << np << "->{next=" << np->next << ", prev=" << np->prev;
   return cout;
}

template <typename T>
void show_list (const string &str, xlist<T>& thelist) {
   cout << str << ":" << endl;
   show_node<T> (&thelist.base) << "}" << endl;
   for (typename xlist<T>::iterator it = thelist.begin();
        it != thelist.end();
        ++it) {
      show_node<T> (it.curr) << ", item=" << *it << "}" << endl;
   }
}

void test_int() {
   xlist<int> xli;
   cout << "sizeof (xlist) = " << sizeof (xli) << endl;
   cout << "sizeof (int) = " << sizeof (int) << endl;
   show_list ("After decl", xli);
   xli.push_back(3);
   xli.push_back(4);
   xli.push_back(5);
   xli.push_back(6);
   show_list ("After push_back", xli);
   cout << xli.back() << endl;
   xli.pop_back();
   cout << xli.back() << endl;
   xli.pop_back();
   show_list ("At end of test_int", xli);
}


void test_string() {
   xlist<string> xli;
   cout << "sizeof (xlist) = " << sizeof (xli) << endl;
   cout << "sizeof (string) = " << sizeof (string) << endl;
   show_list ("After decl", xli);
   xli.push_back("Hello");
   xli.push_back("World");
   xli.push_back("foo");
   xli.push_back("bar");
   show_list ("After push_back", xli);
   cout << xli.back() << endl;
   xli.pop_back();
   cout << xli.back() << endl;
   xli.pop_back();
   show_list ("At end of test_string", xli);
}

int main() {
   string line = "--------------------------------------------------";
   cout << line << endl;
   test_int();
   cout << line << endl;
   test_string();
   cout << line << endl;
   return 0;
}

