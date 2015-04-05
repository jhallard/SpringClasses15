// $Id: sizeof.cpp,v 1.20 2014-03-31 13:02:39-07 - - $

#include <cstdlib>
#include <cwchar>
#include <iostream>
#include <map>
#include <stack>
#include <vector>

using namespace std;

#define SHOW(Type) \
   cout << "sizeof (" << #Type << ") = " << sizeof (Type) << endl;

class empty {
};

class one {
   int x;
};

class virt_one {
   int x;
   virtual void fn1 ();
   virtual ~virt_one ();
};

class virt_two {
   int y;
   virtual void fn2 ();
   virtual ~virt_two ();
};

class single: public virt_one {
   int z;
   virtual void fn3 ();
   virtual ~single ();
};

class multiple: public virt_one, virt_two {
   int z;
   virtual void fn3 ();
   virtual ~multiple ();
};

vector<int> vector_of_int_64 (64);


int main (int argc, char **argv) {
   (void) argc; // SUPPRESS: warning: unused parameter 'argc'
   (void) argv; // SUPPRESS: warning: unused parameter 'argv'

   SHOW (bool);
   SHOW (char);
   SHOW (short);
   SHOW (int);
   SHOW (long);
   SHOW (long long);
   SHOW (float);
   SHOW (double);
   SHOW (long double);
   SHOW (wchar_t);
   SHOW (char16_t);
   SHOW (char32_t);
   SHOW (char*);
   SHOW (void*);
   SHOW (int*);
   SHOW (empty);
   SHOW (one);
   SHOW (virt_one);
   SHOW (virt_two);
   SHOW (single);
   SHOW (multiple);
   SHOW (vector<int>);
   SHOW (vector_of_int_64);
   SHOW (vector<string>);
   SHOW (string);
   SHOW (stack<string>);
   using map_string_int = map<string,int>;
   SHOW (map_string_int);
   return EXIT_SUCCESS;
}

//TEST// ./sizeof >sizeof.lis 2>&1
//TEST// mkpspdf sizeof.ps sizeof.cpp* sizeof.lis

