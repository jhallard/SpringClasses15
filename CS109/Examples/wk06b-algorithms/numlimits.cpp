// $Id: numlimits.cpp,v 1.10 2013-08-20 20:03:02-07 - - $

#include <iomanip>
#include <iostream>
#include <limits>
#include <typeinfo>

#include <cxxabi.h>

using namespace std;

template <typename T>
void show (const string &label) {
   const char *const mangled = typeid (T).name();
   int status;
   char *unmangled = abi::__cxa_demangle (mangled, 0, 0, &status);
   cout << label << ":" << endl
        << unmangled << "(" << mangled << ") [" << sizeof (T) << "] "
        << setprecision (numeric_limits<T>::digits10)
        << numeric_limits<T>::min() << " .. "
        << numeric_limits<T>::max() << endl;
   free (unmangled); // C code allocated by malloc.

}

#define SHOW(T) show<T>(#T)

int main() {
   SHOW (bool);
   SHOW (char);
   SHOW (signed char);
   SHOW (unsigned char);
   SHOW (short);
   SHOW (signed short);
   SHOW (unsigned short);
   SHOW (int);
   SHOW (signed int);
   SHOW (unsigned int);
   SHOW (long);
   SHOW (signed long);
   SHOW (unsigned long);
   SHOW (long long);
   SHOW (signed long long);
   SHOW (unsigned long long);
   SHOW (float);
   SHOW (double);
   SHOW (long double);
   return 0;
}

//TEST// ./numlimits >numlimits.out 2>&1
//TEST// mkpspdf numlimits.ps numlimits.cpp* numlimits.out*

