// $Id: arraystack.cc,v 1.3 2009-03-06 20:04:35-08 - - $

#include "arraystack.h"

const int EMPTY = -1;
const int INITSIZE = 8;

template <class item_t>
arraystack<item_t>::arraystack ():
            top (EMPTY), size(INITSIZE), data (new item_t[INITSIZE]) {
}

template <class item_t>
arraystack<item_t>::arraystack (const arraystack<item_t> &that) {
   *this = that;
}

template <class item_t>
arraystack<item_t> &arraystack<item_t>::operator= (
            const arraystack<item_t> &that) {
   if (this == &that) return *this;
   delete data;
   top = that.top;
   size = that.size;
   for (int itor = 0; itor < top; ++itor) data[itor] = that.data[itor];
   return *this;
}

template <class item_t>
arraystack<item_t>::~arraystack () {
   delete[] data;
}

template <class item_t>
bool arraystack<item_t>::empty () {
   return top == EMPTY;
}

template <class item_t>
void arraystack<item_t>::push (const item_t &item) {
   if (top == size - 1) {
      item_t *newdata = new item_t[size *= 2];
      for (int itor = 0; itor < top; ++itor) newdata[itor] = data[itor];
      delete[] data;
      data = newdata;
   }
   data[++top] = item;
}

template <class item_t>
item_t arraystack<item_t>::pop () {
   if (empty ()) throw new empty_error ();
   return data[top--];
}


