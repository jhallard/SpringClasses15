// $Id: hstring.cc,v 1.1 2012-04-12 20:36:51-07 - - $

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdint.h>
#include <string>

using namespace std;

//
// Show how to extend class string to allow for a hashing function.
//

/////////////////////////////////////////////////////////////////
// hashable.h
/////////////////////////////////////////////////////////////////

// Interface hashable.
// This is a Java-like interface, not a class.

class hashable {
   public:
      uint32_t hash () = 0;
   private:
      hashable (); // Disable.
      hashable (const hashable &); // Disable.
      hashable &operator= (const hashable &); // Disable.
      ~hashable (); // Disable.
}

/////////////////////////////////////////////////////////////////
// hstring.h
/////////////////////////////////////////////////////////////////

// Hashable string interface.

class hstring: public string {
   public:
      hstring (char *cstring): string (cstring) {};
      uint32_t hash ();
};

/////////////////////////////////////////////////////////////////
// hstring.cc
/////////////////////////////////////////////////////////////////

// Hashable string implementation.

// Source:
// http://java.sun.com/j2se/1.5.0/docs/api/java/lang/
// String.html#hashCode()
uint32_t hstring::hash () {
   uint32_t hashcode = 0;
   for (const_iterator itor = begin (); itor < end (); ++itor) {
      hashcode = (hashcode << 5) - hashcode + *itor;
   }
   return hashcode;
}

/////////////////////////////////////////////////////////////////
// main.cc
/////////////////////////////////////////////////////////////////

int main (int argc, char **argv) {
   for (int argi = 0; argi < argc; ++argi) {
      hstring word = argv[argi];
      uint32_t hashcode = word.hash ();
      cout << setw (12) << hashcode << " = hash (\""
           << word << "\")" << endl;
   }
}

