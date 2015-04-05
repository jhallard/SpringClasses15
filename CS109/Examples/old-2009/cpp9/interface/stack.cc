// $Id: stack.cc,v 1.2 2009-03-06 14:54:04-08 - - $

#include "stack.h"

template <class item_t>
stack<item_t>::~stack () {
}

template <class item_t>
stack<item_t>::empty_error::empty_error ():
       runtime_error ("stack::empty_error") {
}

