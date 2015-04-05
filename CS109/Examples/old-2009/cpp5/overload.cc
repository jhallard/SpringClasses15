// $Id: overload.cc,v 1.1 2012-04-12 20:36:51-07 - - $

//
// Example of the difference between member and non-member
// overloading.  We create a class number with member functions
// unary and binary + and non-member friend functions unary
// and binary -.
//
// Member operators are declared with one fewer parameter than
// their arity.  Non-member operators are declared with the same
// number of parameters as their arity.  Non-members must be
// friends if they are to access the internals.
//

#include <iostream>
using namespace std;

class number {
   public:
      number (int);
      number operator+ ();
      number operator+ (const number &);
      friend number operator- (const number &);
      friend number operator- (const number &, const number &);
      friend ostream &operator<< (ostream &, const number &);
   private:
      int value;
};

number::number (int init): value(init) {
   cout << "number (int);" << endl;
}

// Member unary +
number number::operator+ () {
   cout << "number operator+ ();" << endl;
   return +this->value;
}

// Member binary +
number number::operator+ (const number &that) {
   cout << "number operator+ (const number &);" << endl;
   return this->value + that.value;
}

// Non-member unary -
number operator- (const number &right) {
   cout << "friend number operator- (const number &);" << endl;
   return -right.value;
}

// Non-member binary -
number operator- (const number &left, const number &right) {
   cout << "friend number operator- (const number &, const number &);"
        << endl;
   return left.value - right.value;
}

// Allow us to print a number
ostream &operator<< (ostream &out, const number &num) {
   out << "[" << num.value << "]";
   return out;
}

int main () {
   number a = 6;
   number b = 8;
   cout << +a << endl;
   cout << a + b << endl;
   cout << -a << endl;
   cout << a - b << endl;
   return 0;
}

