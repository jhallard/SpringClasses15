// $Id: linkedstack.h,v 1.1 2009-03-06 20:04:35-08 - - $

#ifndef __LINKEDSTACK_H__
#define __LINKEDSTACK_H__

#include "stack.h"

template <class item_t>
class linkedstack: public stack<item_t> {
   public:
      linkedstack ();
      linkedstack (const linkedstack &);
      virtual linkedstack<item_t> &operator= (
                  const linkedstack<item_t> &);
      virtual ~linkedstack ();
      virtual bool empty ();
      virtual void push (const item_t &);
      virtual item_t pop ();
   private:
      struct node {
         node (const item_t &, node *);
         item_t item;
         node *link;
      };
      node *top;
};

#endif

