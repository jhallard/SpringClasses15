// $Id: throw.cpp,v 1.1 2014-06-05 19:27:16-07 - - $

#include <iostream>
#include <stdexcept>
#include <string>
using namespace std;

struct foo_error: public runtime_error {
   explicit foo_error (const string& w):
            runtime_error("foo_error: [" + w + "]") {}
};

struct subfoo_error: public foo_error {
   explicit subfoo_error (const string& w):
            foo_error("subfoo_error: [" + w + "]") {}
};

void foo() {
   throw subfoo_error (__func__);
}

int main() {
   try {
      foo();
   }catch (foo_error& e) {
      cout << e.what() << endl;
   }
}

