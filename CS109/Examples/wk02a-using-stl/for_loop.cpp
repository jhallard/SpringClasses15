// $Id: for_loop.cpp,v 1.24 2014-06-27 13:08:31-07 - - $

//
// Simple class range which allows a range of integral values
// to be used in a foreach loop in the same way as iterators
// may be used.
//

#include <iostream>
using namespace std;

template <typename Discrete> class range;
template <typename Discrete>
ostream& operator<< (ostream& out, const range<Discrete>& range_) {
   return out << "range(" << range_.begin_ << "," << range_.end_ << ")";
}

template <typename Discrete>
class range {
   private:
      Discrete begin_ {};
      Discrete end_ {};
   public:
      range() {}
      range (Discrete begin, Discrete end): begin_(begin), end_(end) {}
      class iterator;
      iterator begin() { return {begin_}; }
      iterator end() { return {end_}; }
      friend ostream& operator<< <> (ostream&, const range<Discrete>&);
};

template <typename Discrete>
class range<Discrete>::iterator {
   private:
      friend class range<Discrete>;
      Discrete value {};
      iterator (Discrete value): value(value) {}
   public:
      iterator() {}
      Discrete operator*() { return value; }
      iterator operator++() { ++value; return *this; }
      Discrete operator!= (range::iterator other) {
         return value != other.value;
      }
};


int main (int, char**) {
   range<int> integers (1, 11);
   cout << "integers range is " << integers << endl;
   for (int val: integers) {
      cout << (val != *integers.begin() ? " " : "") << val;
   }
   cout << endl;
   for (range<int>::iterator itor = integers.begin();
        itor != integers.end(); ++itor) {
      cout << (itor != integers.begin() ? " " : "") << *itor;
   }
   cout << endl;
   range<char> chars (' ', '~' + 1);
   cout << "chars range is " << chars << endl;
   for (char chr: chars) {
      cout << chr;
      if ((chr & 0x1F) == 0x1F) cout << endl;
   }
   cout << endl;
   return 0;
}

//TEST// ./for_loop >for_loop.out 2>&1
//TEST// mkpspdf for_loop.ps for_loop.cpp* for_loop.out

