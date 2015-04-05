// $Id: delegate.cpp,v 1.3 2013-08-15 12:43:13-07 - - $

#include <iostream>
using namespace std;

struct del {
   int a;
   del(): del(4) {cout<<__LINE__<<endl;}
   del(int a): a(a) {cout<<__LINE__<<endl;}
   ~del() {cout <<__LINE__<<endl;}
};

#define T(X) cout << #X << endl; X

int main() {
   T(del x;)
   T(cout << x.a << endl;)
   T(del y{9};)
   T(cout << y.a << endl;)
   T(return 0;)
}
