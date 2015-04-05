// $Id: arraystack.h,v 1.1 2009-03-06 20:04:35-08 - - $

#ifndef __ARRAYSTACK_H__
#define __ARRAYSTACK_H__

#include "stack.h"

template <class item_t>
class arraystack: public stack<item_t> {
   public:
      arraystack ();
      arraystack (const arraystack<item_t> &);
      virtual arraystack<item_t> &operator= (
                  const arraystack<item_t> &);
      virtual ~arraystack ();
      virtual bool empty ();
      virtual void push (const item_t &);
      virtual item_t pop ();
   private:
      int top;
      int size;
      item_t *data;
};

#endif

