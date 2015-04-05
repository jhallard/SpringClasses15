// $Id: ristring.cpp,v 1.16 2013-07-12 19:51:58-07 - - $

//
// NAME
//    ristring - reference counted immutable string
//
// DESCRIPTION
//    Shows how to use reference counting on immutable objects.
//    If this were changed to mutable, then we should probably
//    implement them as copy-on-write (COW).
//

#include <cstdlib>
#include <cstring>
#include <iostream>

using namespace std;

/////////////////////////////////////////////////////////////////
// ristring.h
/////////////////////////////////////////////////////////////////

class ristring {
   private:
      class repr_t;
      repr_t *repr;
      ristring () = delete;
      void decrement ();
   public:
      // override implicit members
      ristring (const ristring &);             // copy ctor
      ristring &operator= (const ristring &);  // operator=
      ~ristring ();                            // dtor
      // other members
      ristring (const char *const);            // "" ctor
      ristring &operator= (const char *const); // "" operator=
      char operator[] (int index) const;       // charat
      int size () const;                       // strlen
      friend ostream &operator<< (ostream &, const ristring &);
      ostream &show (ostream &, const string &label);
};

class ristring::repr_t {
   friend class ristring;
   private:
      int ref_count;
      const ssize_t isize;
      const char *const buffer;
      // Default members.
      repr_t () = delete;
      repr_t (const repr_t &) = delete;
      repr_t &operator= (const repr_t &) = delete;
      ~repr_t ();
      // Ctor and fields.
      repr_t (const char *const string);
      friend ostream &operator<< (ostream &, const ristring &);
};

/////////////////////////////////////////////////////////////////
// ristring.cpp
/////////////////////////////////////////////////////////////////

// strdup(3) calls malloc(3), which is to be freed with free(3),
// not with delete[].  Do not mix malloc/new with free/delete.
const char *strnew (const char *const str) {
   char *tmp = new char[strlen (str) + 1];
   strcpy (tmp, str);
   return tmp;
}

ristring::ristring (const ristring &that) {
   repr = that.repr;
   ++repr->ref_count;
}

ristring &ristring::operator= (const ristring &that) {
   if (this != &that) {
      decrement ();
      repr = that.repr;
      ++repr->ref_count;
   }
   return *this;
}

ristring::ristring (const char *const that) {
   repr = new repr_t (that);
}

ristring::~ristring () {
   decrement ();
}

char ristring::operator[] (int index) const {
   return repr->buffer[index];
}

int ristring::size () const {
   return repr->isize;
}

void ristring::decrement () {
   --repr->ref_count;
   if (repr->ref_count == 0) delete repr;
}

ostream &ristring::show (ostream &out, const string &label) {
   out << label << ": " << static_cast <const void*> (this)
       << "->irstring {repr=" << repr
       << "-> {" << endl
       << "   ref_count=" << repr->ref_count
       << ", isize=" << repr->isize
       << ", buffer=" << static_cast <const void*> (repr->buffer)
       << "->\"" << repr->buffer << "\"" << endl
       << "}}" << endl;
   return out;
}


ristring::repr_t::repr_t (const char *const string):
      ref_count (1), isize (strlen (string)), buffer (strnew (string)) {
}

ristring::repr_t::~repr_t () {
   delete[] buffer;
}

ostream &operator<< (ostream &out, const ristring &that) {
   out << that.repr->buffer;
   return out;
}

/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main (int argc, char **argv) {
   cout << argv[0] << " " << argc << endl;
   ristring first = "Hello, world!";
   first.show (cout, "first") << endl;
   cout << first << endl;
   for (int index = 0; index < first.size (); ++index) {
      cout << "|" << first[index];
   }
   cout << "|" << endl;
   ristring second = "foobar";
   second.show (cout, "second") << endl;
   second = first;
   ristring third = first;
   ristring fourth (first);
   cout << second << endl;
   cout << third << endl;
   cout << fourth << endl;
   second.show (cout, "fourth") << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=ristring.out.grind \
//TEST//       ristring >ristring.out 2>&1
//TEST// mkpspdf ristring.ps ristring.cpp* ristring.out*
*/

