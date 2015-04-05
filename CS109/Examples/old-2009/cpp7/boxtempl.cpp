// $Id: boxtempl.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////
// box.h
/////////////////////////////////////////////////////////////////

template <class item_t>
class box {
   public:
      box ();
      box (const box<item_t> &);
      box &operator= (const box<item_t> &);
      ~box ();
      box (const item_t &);
      box &operator= (const item_t &);
      item_t get ();
   private:
      item_t item;
};

/////////////////////////////////////////////////////////////////
// box.cc
/////////////////////////////////////////////////////////////////

template <class item_t>
box<item_t>::box () {
}

template <class item_t>
box<item_t>::box (const box<item_t> &that): item(that.item) {
}

template <class item_t>
box<item_t> &box<item_t>::operator= (const box<item_t> &that) {
   if (this == &that) return *this;
   item = that.item;
   return *this;
}

template <class item_t>
box<item_t>::~box () {
}

template <class item_t>
box<item_t>::box (const item_t &that): item(that) {
}

template <class item_t>
box<item_t> &box<item_t>::operator= (const item_t &that) {
   item = that;
   return *this;
}

template <class item_t>
item_t box<item_t>::get () {
   return item;
}

/////////////////////////////////////////////////////////////////
// main.cc
/////////////////////////////////////////////////////////////////

int main () {
   //box<string> bxstr = "hello";
   box<string> bxstr ("hello");
   cout << bxstr.get() << endl;
   bxstr = "world";
   cout << bxstr.get() << endl;
   box<int> bxint = 99;
   cout << bxint.get() << endl;
   bxint = 9;
   cout << bxint.get() << endl;
   return 0;
}

