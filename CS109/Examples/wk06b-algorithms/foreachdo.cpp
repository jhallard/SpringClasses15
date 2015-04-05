// $Id: foreachdo.cpp,v 1.14 2013-08-20 19:49:22-07 - - $

#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

// Accumulators.

struct adder: unary_function <double, void> {
   double &sum;
   adder (double &sum): sum (sum) {}
   void operator() (double num) { sum += num; }
};

struct multiplier: unary_function <double, void> {
   double &prod;
   multiplier (double &prod): prod (prod) {}
   void operator() (double num) { prod *= num; }
};

struct sqrt_vec: unary_function <double, void> {
   void operator() (double &num) { num = sqrt (num); }
};

void printd (double num) {
   cout << "vec: " << num << endl;
}

int main () {
   vector<double> vec {1.6, 3.9, 3.14, 11.44, 16.28, 24, 32.3, 98.6};
   for_each (vec.begin(), vec.end(), printd);

   double sum {0};
   for_each (vec.begin(), vec.end(), adder (sum));
   cout << "sum = " << sum << endl;

   double product {1};
   for_each (vec.begin(), vec.end(), multiplier (product));
   cout << "product = " << product << endl;

   for_each (vec.begin(), vec.end(), sqrt_vec());
   for_each (vec.begin(), vec.end(), printd);

   return EXIT_SUCCESS;
}

//TEST// ./foreachdo >foreachdo.out 2>&1
//TEST// mkpspdf foreachdo.ps foreachdo.cpp* foreachdo.out

