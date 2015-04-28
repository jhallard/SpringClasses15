// $Id: bigint.cpp,v 1.61 2014-06-26 17:06:06-07 - - $

#include <cstdlib>
#include <exception>
#include <limits>
#include <algorithm>
#include <stack>
#include <stdexcept>
#include <sstream>
using namespace std;

#include "bigint.h"
#include "debug.h"


bigint::bigint (long that) : negative(false){
   if(that < 0) negative = true;
   big_value.clear();
   string val;
   stringstream s_val;
   s_val << that;
   val = s_val.str();
   for(int i = 0; i < s_val.str().length(); i++) {
      big_value.push_back(val.back());
      val.pop_back();
   }
   DEBUGF ('~', this << " -> " << that);
}

bigint::bigint (const string& that) : negative(false) {
   auto itor = that.cbegin();
   if (itor != that.cend() and *itor == '_') {
      negative = true;
      ++itor;
   }

   while (itor != that.end()) {
      big_value.push_back(*itor);
      itor++;
   }

   reverse(big_value.begin(), big_value.end());
   // int newval = 0;
   // while (itor != that.end()) newval = newval * 10 + *itor++ - '0';
   // big_value = isnegative ? - newval : + newval;
   // cout << that << "--" << *this << "\n";
   DEBUGF ('~', this << " -> " << that)
}

bigint::bigvalue_t do_bigadd (const bigint::bigvalue_t& left,
 const bigint::bigvalue_t& right) {

   int carry = 0;
   bool left_bigger = left.size() > right.size();
   bool right_bigger = left.size() < right.size();
   bigint::bigvalue_t big_ret;
   auto lt = left.begin();
   auto rt = right.begin();
   for(; lt != left.end() && rt != right.end();) {

      int ldig = *lt - '0';
      int rdig = *rt - '0';

      ldig += carry;
      carry = 0;

      int res = ldig+rdig;
      while(res >= 10) {
         carry++;
         res = res-10;
      }
      big_ret.push_back(res+'0');
      ++lt; ++rt;
   }

// edit still need to account for if a carry still exists
// at this points

   if(left_bigger) {
      while(lt != left.end()) {
         int dig = *lt - '0';
         dig += carry;
         carry = 0;
         if(dig >= 10) {
            carry++;
            dig -= 10;
         }
         big_ret.push_back(dig+'0');
         ++lt;
      }
   }
   else if(right_bigger) {
      while(rt != right.end()) {
         int dig = *rt - '0';
         dig += carry;
         carry = 0;
         if(dig >= 10) {
            carry++;
            dig -= 10;
         }
         big_ret.push_back(dig+'0');
         ++rt;
      }
   }
   if(carry) {
      big_ret.push_back(carry+'0');
   }
   return big_ret;
}

bigint::bigvalue_t do_bigsub (const bigint::bigvalue_t& left,
 const bigint::bigvalue_t& right) {

   if(right.size() > left.size()) {
      throw ydc_exn("do_bigsub : right val > left val\n");
   }

   if(!right.size() || !left.size())
      throw ydc_exn("zero size in do_bigsub\n");
   cout << "Here #1" << endl;
   bool carry = false;
   bigint::bigvalue_t big_ret;
   auto lt = left.cbegin();
   auto rt = right.cbegin();
   for(; lt != left.end() && rt != right.end();) {

      int ldig = *lt - '0';
      int rdig = *rt - '0';

      if(carry==true) {
         ldig-=1;
         carry = false;
      }

      if(ldig<rdig) {
         ldig +=10;
         carry = true;
      }
      cout << "Here #2" << endl;

      int res = ldig-rdig;
      big_ret.push_back(res+'0');
      ++lt; ++rt;
   }

cout << "Here #3" << endl;
   while(lt != left.cend()) {
      int dig = *lt - '0';
      if(carry==true) {
         dig-=1;
         carry = false;
      }
      cout << "Here #4" << endl;

      if(dig<0) {
         dig +=10;
         carry = true;
      }

      big_ret.push_back(dig+'0');
      ++lt;
   }

   // clear meaningless zeros
   if(big_ret.size()) {
      while(big_ret.back() == '0') big_ret.pop_back();
   }
   return big_ret;
}

// returns true if left is less than right
bool do_bigless (const bigint::bigvalue_t& left, 
   const bigint::bigvalue_t& right) {

   if(left.size() != right.size()) {
      return left.size() < right.size();
   }

   // go through all digits and find which is smaller first
   for(int it = left.size()-1; it >=0; --it) {
      // if the left digit is smaller return true (or false
      // if both are negative)
      if(left.at(it) < right.at(it)) return true;
      else if(left.at(it) > right.at(it)) return false;
   }

   return false;

}


bigint operator+ (const bigint& left, const bigint& right) {
   // if they're both negative this flag is hot, meaning we just 
   // flip the output we would get if they were both positive
   bool flip = left.negative && right.negative;
   bigint ret(0);
   if(left.negative && !right.negative) {
      cout << "Here #16" << endl;

      if(do_bigless(left.big_value, right.big_value)) {
         cout << "Here #17" << endl;
         ret.big_value = do_bigsub(right.big_value, left.big_value);
      }
      else {
         ret.big_value = do_bigsub(left.big_value, right.big_value);
         ret.negative = true;
      }
      return ret;
   }
   if(!left.negative && right.negative) {
      if(do_bigless(left.big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, left.big_value);
         ret.negative = true;
      }
      else {
         ret.big_value = do_bigsub(left.big_value, right.big_value);
      }
      return ret;
   }

   ret.big_value = do_bigadd(left.big_value, right.big_value);

   if(flip) ret.negative = true;

   return ret;
}

// left minus right!
bigint operator- (const bigint& left, const bigint& right) {
   // if they're both negative this flag is hot, meaning we just 
   // flip the output we would get if they were both positive
   bool flip = left.negative && !right.negative;
   bigint ret(0);
   if(!left.negative && !right.negative) {
      if(do_bigless(left.big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, left.big_value);
         ret.negative = true;
      }
      else {
         ret.big_value = do_bigsub(left.big_value, right.big_value);
      }
      return ret;
   }
   if(left.negative && right.negative) {
      if(do_bigless(left.big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, left.big_value);
      }
      else {
         ret.big_value = do_bigsub(left.big_value, right.big_value);
         ret.negative = true;
      }
      return ret;
   }

   ret.big_value = do_bigadd(left.big_value, right.big_value);

   if(flip) ret.negative = true;

   return ret;
}

bigint bigint::operator+ (const bigint& right) {
   // if they're both negative this flag is hot, meaning we just 
   // flip the output we would get if they were both positive
   bool flip = this->negative && right.negative;
   bigint ret(0);
   if(this->negative && !right.negative) {
      if(do_bigless(this->big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, this->big_value);
      }
      else {
         ret.big_value = do_bigsub(this->big_value, right.big_value);
         ret.negative = true;
      }
      return ret;
   }
   if(!this->negative && right.negative) {
      if(do_bigless(this->big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, this->big_value);
         ret.negative = true;
      }
      else {
         ret.big_value = do_bigsub(this->big_value, right.big_value);
      }
      return ret;
   }

   ret.big_value = do_bigadd(this->big_value, right.big_value);

   if(flip) ret.negative = true;

   return ret;
}

bigint bigint::operator- (const bigint& right) {
   // if they're both negative this flag is hot, meaning we just 
   // flip the output we would get if they were both positive
   bool flip = negative && !right.negative;
   bigint ret(0);
   if(!negative && !right.negative) {
      if(do_bigless(big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, big_value);
         ret.negative = true;
      }
      else {
         ret.big_value = do_bigsub(big_value, right.big_value);
      }
      return ret;
   }
   if(negative && right.negative) {
      if(do_bigless(big_value, right.big_value)) {
         ret.big_value = do_bigsub(right.big_value, big_value);
      }
      else {
         ret.big_value = do_bigsub(big_value, right.big_value);
         ret.negative = true;
      }
      return ret;
   }

   ret.big_value = do_bigadd(big_value, right.big_value);

   if(flip) ret.negative = true;

   return ret;
}

long bigint::to_long() const {
   // if (*this <= bigint (numeric_limits<long>::min())
    // or *this > bigint (numeric_limits<long>::max()))
               // throw range_error ("bigint__to_long: out of range");

   // do_bigadd(bigint('0'), this);
   long ret = 0, i = 1;
   for(auto & x : big_value) {
      ret += i*(x-'0');
      i*=10;
   }

   return this->negative ? -1*ret : ret; 
}

bool abs_less (const bigint & left, const bigint & right) {
   return do_bigless(left.big_value, right.big_value);
}

//
// Multiplication algorithm.
//
bigint operator* (const bigint& left, const bigint& right) {
   bigint ret(0);
   bigint::bigvalue_t num = {'0'};
   num.reserve(right.big_value.size()*left.big_value.size());
   int neg_count = 0;
   if(left.negative) neg_count++;
   if(right.negative) neg_count++;

   if(neg_count % 2) ret.negative = true;

   std::cout << left.to_long() << endl << endl;
   for(int i = 0; i < left.to_long(); i++) {
      for(auto x : vector<char>(num.rbegin(), num.rend())) cout << x;
      num = do_bigadd(num, right.big_value);
      cout << endl;
   }

   ret.big_value = num;
   return ret;
}

//
// Division algorithm.
//

void multiply_by_2 (bigint & value) {
   value.big_value = do_bigadd(value.big_value, value.big_value);
}

void divide_by_2 (bigint & value) {
   value.big_value = do_bigadd(value.big_value, value.big_value);
}


bigint::quot_rem divide (const bigint& left, const bigint& right) {
   if (right == 0) throw domain_error ("divide by 0");
   using unumber = unsigned long;
   static unumber zero = 0;
   if (right == 0) throw domain_error ("bigint::divide");
   bigint divisor = right;
   bigint quotient = bigint('0');
   bigint rem = left;
   bigint power_of_2 = bigint('1');
   while (abs_less (divisor, rem)) {
      multiply_by_2 (divisor);
      multiply_by_2 (power_of_2);
   }
   while (abs_less (zero, power_of_2)) {
      if (not abs_less (rem, divisor)) {
         rem = rem - divisor;
         quotient = quotient + power_of_2;
      }
      divide_by_2 (divisor);
      divide_by_2 (power_of_2);
   }
   return {quotient, rem};
}

bigint operator/ (const bigint& left, const bigint& right) {
   return divide (left, right).first;
}

bigint operator% (const bigint& left, const bigint& right) {
   return divide (left, right).second;
}

bool operator== (const bigint& left, const bigint& right) {
   if(left.negative != right.negative)
      return false;
   if(left.big_value.size() != right.big_value.size()) 
      return false;

   return (left-right).to_long() == 0; 
}

bool operator< (const bigint& left, const bigint& right) {
   // if they're both negative this flag is hot, meaning we just 
   // flip the output we would get if they were both positive
   bool flip = !left.negative && !right.negative;
   if(left.negative && !right.negative) {
      return true;
   }
   if(!left.negative && right.negative) {
      return false;
   }

   if(left.big_value.size() != right.big_value.size()) {
      bool ret = left.big_value.size() < right.big_value.size();
      if(flip) ret = !ret;
      return ret;
   }


   bool ret = do_bigless(left.big_value, right.big_value);

   return flip? !ret : ret;

}

ostream& operator<< (ostream& out, const bigint& that) {
   // out << that.big_value;
   // cout << that.big_value.size();
   if(that.negative) out << '-';
   for(auto x = that.big_value.rbegin();
    x != that.big_value.rend(); x++) {
      out << *x;
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


