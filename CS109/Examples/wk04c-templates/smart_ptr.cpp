// $Id: smart_ptr.cpp,v 1.3 2015-01-27 17:50:27-08 - - $

//
// Smart pointer class encapsulating a pointer, like shared_ptr.
//

#include <iostream>
using namespace std;

/////////////////////////////////////////////////////////////////
// pointer.h
/////////////////////////////////////////////////////////////////

template <typename Type>
class pointer {
      template <typename U>
      friend ostream& operator<< (ostream& , const pointer<U>& );

   private:

      // Invariant: ref_count == obj_ptr == nullptr
      //            ref_count->count on heap, obj_ptr->object itself

      size_t* ref_count;
      Type* obj_ptr;

      // Auxiliary functions.

      inline void increment_count() {
         if (ref_count) ++*ref_count;
      }

      inline void copy_that (size_t* ref, Type* obj) {
         if (ref_count and --*ref_count == 0) {
            delete ref_count;
            delete obj_ptr;
         }
         ref_count = ref;
         obj_ptr = obj;
      }

      inline void clear_that (pointer& that) const {
         that.ref_count = nullptr;
         that.obj_ptr = nullptr;
      }


   public:
      // Replace implicitly generated functions.

      pointer(): ref_count (nullptr), obj_ptr (nullptr) {
      }

      pointer (const pointer& that): ref_count (that.ref_count),
                                     obj_ptr (that.obj_ptr) {
         increment_count();
      }

      pointer (pointer&& that): ref_count (that.ref_count),
                                obj_ptr (that.obj_ptr) {
         clear_that (that);
      }

      pointer& operator= (const pointer& that) {
         if (this == &that) return *this;
         copy_that (that.ref_count, that.obj_ptr);
         increment_count();
         return *this;
      }

      pointer& operator= (pointer&& that) {
         if (this == &that) return *this;
         copy_that (that.ref_count, that.obj_ptr);
         clear_that (that);
         return *this;
      }

      ~pointer() {
         copy_that (nullptr, nullptr);
      }

      // Other constructors.

      pointer (Type* p_obj_ptr): ref_count (new size_t (1)),
                                 obj_ptr (p_obj_ptr) {
      }

      // Mutators (non-const functions).

      inline Type& operator*() { return *obj_ptr; }

      inline Type* operator->() { return obj_ptr; }


      // Accessors (const functions).

      inline const Type& operator*() const { return *obj_ptr; }

      inline const Type* operator->() const { return obj_ptr; }

      inline operator bool() const { return obj_ptr; }

      inline bool operator== (const pointer& that) const {
         return obj_ptr == that.obj_ptr;
      }

      inline bool operator!= (const pointer& that) const {
         return not (*this == that);
      }

      size_t users() const { return ref_count ? *ref_count : 0; }

      size_t unique() const { return users() == 1; }

      size_t empty() const { return users() == 0; }
};

template <typename Type>
ostream& operator<< (ostream& out, const pointer<Type>& that) {
   out << that.obj_ptr << "[" << *that.ref_count << "]";
   return out;
}


/////////////////////////////////////////////////////////////////
// Main program.
/////////////////////////////////////////////////////////////////

struct node {
   string str;
   pointer<node> link;
   node (const char* s, pointer<node> p = nullptr): str (s), link (p) {
   }
};

int main (int argc, char** argv) {
   pointer<node> head, tail;
   for (int i = 0; i < argc; ++i) {
      pointer<node> tmp = pointer<node> (new node (argv[i]));
      if (head == nullptr) head = tmp;
                      else tail->link = tmp;
      tail = tmp;
   }
   for (pointer<node> p = head; p != nullptr; p = p->link) {
      cout << p << "->\"" << p->str << "\"" << endl;
   }
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind smart_ptr hello world foo bar baz >smart_ptr.out 2>&1
//TEST// mkpspdf smart_ptr.ps smart_ptr.cpp* smart_ptr.out

