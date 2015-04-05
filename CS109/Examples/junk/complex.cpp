// $Id: complex.cpp,v 1.12 2013-08-09 15:51:26-07 - - $

#include <complex>
#include <iomanip>
#include <iostream>
using namespace std;

using dcomplex = complex<double>;

#define D(X,V) cout << "const dcomplex " #X " = " #V ";" << endl; \
               const dcomplex X = V; \
               cout << #X << " = " << X << endl;

int main() {
   cout << setprecision(15);
   D(C_N1,-1);
   D(C_I,sqrt(C_N1));
   D(C_PI,M_PI);
   D(C_I_PI,C_I * M_PI);
   D(C_EXP,exp (C_I_PI));
   D(E_I_PI_P1,C_EXP + 1.0);
   return 0;
}
