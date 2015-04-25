// $Id: bigint.cpp,v 1.61 2014-06-26 17:06:06-07 - - $

#include <cstdlib>
#include <exception>
#include <limits>
#include <stack>
#include <stdexcept>
using namespace std;

#include "bigint.h"
#include "debug.h"

bigint::bigint (long that) {
   
   // DEBUGF ('~', this << " -> " << that);
}

// bigint::bigint (const string& that) {
//    auto itor = that.cbegin();
//    bool isnegative = false;
//    if (itor != that.cend() and *itor == '_') {
//       isnegative = true;
//       ++itor;
//    }
//    int newval = 0;
//    while (itor != that.end()) newval = newval * 10 + *itor++ - '0';
//    big_value = isnegative ? - newval : + newval;
//    DEBUGF ('~', this << " -> " << big_value)
// }

bigint::bigint (const string& that) {
   auto itor = that.cbegin();
   bool isnegative = false;
   if (itor != that.cend() and *itor == '_') {
      isnegative = true;
      ++itor;
   }
   int newval = 0;
   for(auto iter = that.rbegin(); iter != that.rend()-1; ++iter) {
      big_value.push_back(*iter);
   }

   if(isnegative) big_value.push_back('_');
 
   // while (itor != that.end()) newval = newval * 10 + *itor++ - '0';
   // big_value = isnegative ? - newval : + newval;
 
   // DEBUGF ('~', this << " -> " << big_value)
}

bigint::bigvalue_t do_bigadd (const bigint::bigvalue_t&,
 const bigint::bigvalue_t&) {

   // replace line below.s
   bigint::bigvalue_t ret({'1','2','3'});

   return ret;
}

bigint::bigvalue_t do_bigsub (const bigint::bigvalue_t&,
 const bigint::bigvalue_t&) {

   // replace line below.s
   bigint::bigvalue_t ret({'1','2','3'});

   return ret;
}


bigint operator+ (const bigint& left, const bigint& right) {
   bigint ret_val('0');
   return ret_val;
   // return left.big_value + right.big_value;
}

bigint operator- (const bigint& left, const bigint& right) {
   bigint ret_val('0');
   return ret_val;
   // return left.big_value - right.big_value;
}

bigint operator+ (const bigint& right) {
   bigint ret_val('0');
   return ret_val;
   // return +right.big_value;
}

bigint operator- (const bigint& right) {
   bigint ret_val('0');
   return ret_val;
   // return -right.big_value;
}

long bigint::to_long() const {
   if (*this <= bigint (numeric_limits<long>::min())
    or *this > bigint (numeric_limits<long>::max()))
               throw range_error ("bigint__to_long: out of range");

   // do_bigadd(bigint('0'), this);
   long ret = 0, i = 1;
   for(auto & x : big_value) {
      ret += i*(x-'0');
   }
   return big_value;
}

bool abs_less (const long& left, const long& right) {
   return left < right;
}

//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   bigint ret_val('0');
   return ret_val;
   // return left.big_value * right.big_value;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint & value) {
   value *= 2;
}

void divide_by_2 (bigint & value) {
   value /= 2;
}


bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   using unumber = unsigned long;
   static unumber zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   unumber divisor = right.big_value;
   unumber quotient = 0;
   unumber remainder = left.big_value;
   unumber power_of_2 = 1;
   while (abs_less (divisor, remainder)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (abs_less (zero, power_of_2)) {
      if (not abs_less (remainder, divisor)) {
         remainder = remainder - divisor;
         quotient = quotient + power_of_2;
      }
      divide_by_2 (divisor);
      divide_by_2 (power_of_2);
   }
   return {quotient, remainder};
}

bigint operator/ (const bigint& left, const bigint& right) {
   return divide (left, right).first;
}

bigint operator% (const bigint& left, const bigint& right) {
   return divide (left, right).second;
}

bool operator== (const bigint& left, const bigint& right) {
   return false;
   // return left.big_value == right.big_value;
}

bool operator< (const bigint& left, const bigint& right) {
   return false;
   // return left.big_value < right.big_value;
}

ostream& operator<< (ostream& out, const bigint& that) {
   // out << that.big_value;
   for(auto & x : that.big_value) {
      out << x;
   }
   return out;
}


bigint pow (const bigint& base, const bigint& exponent) {
   DEBUGF ('^', "base = " << base << ", exponent = " << exponent);
   if (base == 0) return 0;
   bigint base_copy = base;
   long expt = exponent.to_long();
   bigint result = 1;
   if (expt < 0) {
      base_copy = 1 / base_copy;
      expt = - expt;
   }
   while (expt > 0) {
      if (expt & 1) { //odd
         result = result * base_copy;
         --expt;
      }else { //even
         base_copy = base_copy * base_copy;
         expt /= 2;
      }
   }
   DEBUGF ('^', "result = " << result);
   return result;
}


