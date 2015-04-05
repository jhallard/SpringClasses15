// $Id: linkedstack.cc,v 1.2 2009-03-06 14:54:04-08 - - $

#include "linkedstack.h"

template <class item_t>
linkedstack<item_t>::linkedstack (): top (NULL) {
}

template <class item_t>
linkedstack<item_t>::linkedstack (const linkedstack<item_t> &that) {
   *this = that;
}

template <class item_t>
linkedstack<item_t> &linkedstack<item_t>::operator= (
            const linkedstack<item_t> &that) {
   if (this == &that) return *this;
   while (! empty ()) pop ();
   node **end = &top;
   for (node *itor = that.top; itor != NULL; itor = itor->link) {
      *end = new node (itor->item, NULL);
      end = &(*end)->link;
   }
}

template <class item_t>
linkedstack<item_t>::~linkedstack () {
   while (! empty ()) pop ();
}

template <class item_t>
bool linkedstack<item_t>::empty () {
   return top == NULL;
}

template <class item_t>
void linkedstack<item_t>::push (const item_t &item) {
   top = new node (item, top);
}

template <class item_t>
item_t linkedstack<item_t>::pop () {
   if (empty ()) throw new empty_error ();
   item_t result = top->item;
   node *oldtop = top;
   top = top->link;
   delete oldtop;
   return result;
}

template <class item_t>
linkedstack<item_t>::node::node (const item_t &item, node *link):
            item (item), link (link) {
}

