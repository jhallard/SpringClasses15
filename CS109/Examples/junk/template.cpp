#include <iostream>
using namespace std;

template <int N>
constexpr int fac() {
   return N * fac<N-1>();
}

template<>
constexpr int fac<0>() {
   return 1;
}

void print() {
   cout << endl;
}

template <typename Type, typename... Args>
void print (Type head, Args... tail) {
   cout << head;
   print (tail...);
}

int main() {
   cout << fac<0>() << endl;
   cout << fac<1>() << endl;
   cout << fac<2>() << endl;
   cout << fac<3>() << endl;
   cout << fac<4>() << endl;
   cout << fac<5>() << endl;
   cout << fac<6>() << endl;
   print ("Testing: ", 6, " ", 4.8, " end");
   return 0;
}

