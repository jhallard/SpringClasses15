// $Id: ststring.cpp,v 1.9 2013-02-22 19:27:07-08 - - $

// Simple traced string.
// Print out message from constructor and destructor.

#include <cstring>
#include <iostream>

using namespace std;

class ststring {
   private:
      size_t length;
      char *buffer;
      void trace (const char *const label);
   public:
      ststring();
      ststring (const ststring &that);
      ststring &operator= (const ststring &that);
      ~ststring();
      ststring (const char *const str);
      friend ostream &operator<< (ostream &out, const ststring &str);
};

void ststring::trace (const char *const label) {
   cout << label << ": " << static_cast<void*> (this)
        << "->ststring {" << length << "," << buffer << "}" << endl;
}

ststring::ststring(): length(0), buffer(new char[1]) {
   buffer[0] = '\0';
   trace ("ststring()");
}

ststring::ststring (const ststring &that):
          length(that.length), buffer(new char[that.length]) {
   strcpy (buffer, that.buffer);
   trace ("ststring(const ststring &)");
}

ststring &ststring::operator= (const ststring &that) {
   if (this == &that) return *this;
   delete[] buffer;
   length = that.length;
   buffer = new char[length];
   strcpy (buffer, that.buffer);
   trace ("ststring::operator=");
   return *this;
}

ststring::~ststring() {
   trace ("~ststring");
   delete[] buffer;
}

ststring::ststring (const char *const str):
          length(strlen(str)), buffer(new char[length + 1]) {
   strcpy (buffer, str);
   trace ("ststring(const char *const)");
}

ostream &operator<< (ostream &out, const ststring &str) {
   out << str.buffer;
   return out;
}

int main (int argc, char **argv) {
   ststring s1;
   ststring s2 ("hello");
   ststring s3 (s2);
   s1 = s3;
   return 0;
}
