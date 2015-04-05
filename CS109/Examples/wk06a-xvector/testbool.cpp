// $Id: testbool.cpp,v 1.6 2013-08-12 18:55:17-07 - - $

//
// Sieve of Eratosthenes.
// To Kóskinon 'Eratosthénous.
//

#include <iomanip>
#include <iostream>

using namespace std;

#include "xvector.h"

int main () {
   const size_t rows {32};
   const size_t columns {16};
   const size_t num_width {4};
   xvector<bool> sieve (rows * columns, true);
   sieve[0] = sieve[1] = false;

   for (size_t prime {2}; prime * prime < sieve.size(); ++prime) {
      if (sieve[prime]) {
         for (size_t itor {prime * prime};
              itor < sieve.size(); itor += prime) {
            sieve[itor] = false;
         }
      }
   }

   size_t prime_count {0};
   size_t col_count {0};
   cout << "Sieve of Eratosthenes." << endl;
   cout << "To Kóskinon 'Eratosthénous." << endl;
   for (size_t itor {0}; itor < rows * columns; ++itor) {
      cout << setw (num_width);
      if (sieve[itor]) { cout << itor; ++prime_count; }
                  else { cout << "."; }
      if (++col_count % columns == 0) cout << endl;
   }
   cout << "Sieve size: " << sieve.size() << ".  ";
   cout << "Primes found: " << prime_count << "." << endl;

   return 0;
}

