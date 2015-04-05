// $Id: testvector.cpp,v 1.7 2014-05-29 19:02:56-07 - - $

#include <iomanip>
#include <iostream>

using namespace std;

#include "xvector.h"

using dvector = xvector<double>;
using matrix = xvector<dvector>;

matrix outer_product (const dvector &v1, const dvector &v2) {
   matrix m (v1.size(), dvector (v2.size()));
   for (size_t i {0}; i < v1.size(); ++i) {
      for (size_t j {0}; j < v2.size(); ++j) {
         m[i][j] = v1[i] * v2[j];
      }
   }
   return m;
}

void print (const matrix &m) {
   cout << fixed << setprecision(0);
   for (size_t i {0}; i < m.size(); ++i) {
      for (size_t j {0}; j < m[i].size(); ++j) {
         cout << setw(4) << m[i][j];
      }
      cout << endl;
   }
}

int main() {
   dvector v1 {1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29};
   dvector v2 {2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30};
   matrix m = outer_product (v1, v2);
   print (m);
   cout << "sizeof (dvector) = " << sizeof (dvector) << endl;
   cout << "sizeof (matrix)  = " << sizeof (matrix) << endl;
   return 0;
}

