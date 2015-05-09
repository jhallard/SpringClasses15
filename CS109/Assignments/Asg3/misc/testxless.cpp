// $Id: testxless.cpp,v 1.22 2015-02-06 16:22:06-08 - - $

// Example of how to use xless object on a pair of strings.

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

template <typename Type>
struct xless {
   bool operator() (const Type &left, const Type &right) const {
      return left < right;
   }
};

template <typename Type, class Less=xless<Type>>
void compare (const Type &left, const Type &right) {
   Less less;
   cout << boolalpha;
   bool is_less = less (left, right);
   bool is_equal = not less (left, right) and not less (right, left);
   bool is_greater = not is_less and not is_equal;
   cout << left << " <  " << right << " = " << is_less << endl;
   cout << left << " == " << right << " = " << is_equal << endl;
   cout << left << " >  " << right << " = " << is_greater << endl;
   cout << endl;
}

int main () {
   compare (string ("hello"), string ("world"));
   compare (string ("qwert"), string ("qwert"));
   compare (string ("zxcvb"), string ("asdfg"));
   return 0;
}

//TEST// testxless >testxless.out 2>&1
//TEST// mkpspdf testxless.ps testxless.cpp* testxless.out

