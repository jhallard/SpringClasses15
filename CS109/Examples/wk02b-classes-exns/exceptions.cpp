// $Id: exceptions.cpp,v 1.32 2013-06-28 19:51:19-07 - - $

// Illustrate some exceptions.

#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

#define SHOW(STMT) \
        cout << __func__ << "[" << __LINE__ << "]: SHOW (" \
             << #STMT << ")" << endl; \
        STMT

void fn_bad_alloc() {
   SHOW (vector<int> v0(-5);)
}

void fn_out_of_range() {
   SHOW (vector<int> v1(10);)
   SHOW (v1.at(-5) = 8;)
}

void fn_pop_empty_vector() {
   SHOW (vector<int> v2(10);)
   SHOW (v2.pop_back();)
}

void fn_back_empty_vector() {
   SHOW (vector<int> v3(10);)
   SHOW (cout << ".... " << v3.back() << endl;)
}

int main (int argc, char **argv) {
   for (int argi = 1; argi < argc; ++argi) {
      for (char *chari = argv[argi]; *chari != '\0'; ++chari) {
         try {
            switch (*chari) {
               case 'b': fn_bad_alloc(); break;
               case 'o': fn_out_of_range(); break;
               case 'p': fn_pop_empty_vector(); break;
               case 'e': fn_back_empty_vector(); break;
            }
         }catch (exception &err) {
            cout << ".... exception " << typeid (err).name() 
                 << ", what = \"" << err.what() << "\"" << endl;
         }
      }
   }
   fn_bad_alloc(); // Throw an uncaught exception.
   return 0;
}

//TEST// ./exceptions b o p e 2>&1 >exceptions.lis
//TEST// mkpspdf exceptions.ps exceptions.cpp* exceptions.lis

