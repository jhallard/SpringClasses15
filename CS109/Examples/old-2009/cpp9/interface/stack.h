// $Id: stack.h,v 1.1 2009-03-06 20:04:35-08 - - $

#ifndef __STACK_H__
#define __STACK_H__

//
// C++ example of a Java interface.
//
// An interface in java is an abstract class with no methods and
// no fields.  Java allows single inheritance of classes and
// multiple inheritance of interfaces.  C++ allows multiple
// inheritance of classes.
//

#include <stdexcept>

using namespace std;

template <class item_t>
class stack {
   public:
      virtual stack &operator= (const stack &) = 0;
      virtual ~stack () = 0;
      virtual bool empty () = 0;
      virtual void push (const item_t &) = 0;
      virtual item_t pop () = 0;
      struct empty_error: public runtime_error {
         empty_error ();
      };
};

#endif

