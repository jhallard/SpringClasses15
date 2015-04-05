// $Id: astring.cpp,v 1.30 2015-01-26 14:28:34-08 - - $

//
// NAME
//    astring - trivial implementation of a string using an array
//
// DESCRIPTION
//    We show how to implement a simple string class.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////
// astring.h
/////////////////////////////////////////////////////////////////

class astring {
   private:
      static constexpr size_t DEFAULT_CAPACITY = 16;
      size_t capacity_;
      size_t size_;
      char* buffer_;
      void range_check (size_t pos, const char* id) const;
      void copy_from (const astring&);
      void clear_that (astring&);
   public:

      // override implicit members
      astring();                                // default ctor
      astring (const astring&);                 // copy ctor
      astring& operator= (const astring&);      // operator=
      ~astring();                               // dtor
      astring (astring&&);                      // move ctor
      astring& operator= (astring&&);           // move operator=

      // other members
      astring (const char* );                 // "" ctor
      explicit astring (size_t);              // length reservation
      astring& operator= (const char*);       // operator=
      astring& operator+= (const char);       // += char
      astring& operator+= (const char*);      // += char* 
      char operator[] (size_t pos) const;     // const subscript =[]
      char& operator[] (size_t pos);          // ref subscript []=
      void reserve (size_t);                  // ensure buffer size;
      size_t size() const;                    // strlen
      size_t capacity() const;
      const char* c_str() const;              // borrow string in C fmt
      friend ostream& operator<< (ostream&, const astring&);
};

/////////////////////////////////////////////////////////////////
// astring.cpp
/////////////////////////////////////////////////////////////////

void astring::range_check (size_t pos, const char* id) const {
   if (pos < size_) return;
   throw out_of_range (id);
}

void astring::copy_from (const astring& that) {
   reserve (that.size_ + 1);
   size_ = that.size_;
   strcpy (buffer_, that.buffer_);
}

void astring::clear_that (astring& that) {
   that.size_ = that.capacity_ = 0;
   that.buffer_ = NULL;
}

astring::astring(): capacity_ (DEFAULT_CAPACITY), size_ (0),
                    buffer_ (new char[DEFAULT_CAPACITY]) {
   buffer_[size_] = '\0';
}

astring::astring (const astring& that): capacity_ (that.capacity_),
                    buffer_ (new char[that.capacity_]) {
   copy_from (that);
}

astring& astring::operator= (const astring& that) {
   if (this !=& that) copy_from (that);
   return *this;
}

astring::astring (astring&& that): capacity_ (that.capacity_),
                    size_ (that.size_), buffer_ (that.buffer_) {
   clear_that (that);
}

astring& astring::operator= (astring&& that) {
   if (this !=& that) {
      capacity_ = that.capacity_;
      size_ = that.size_;
      buffer_ = that.buffer_;
      clear_that (that);
   }
   return *this;
}

astring::~astring() {
   if (buffer_ != NULL) delete[] buffer_;
}


astring::astring (const char* that) {
   size_ = strlen (that);
   capacity_ = size_ + 1;
   buffer_ = new char [capacity_];
   strcpy (buffer_, that);
}

astring::astring (size_t capacity): capacity_ (capacity), size_ (0),
                    buffer_ (new char[size_]) {
   buffer_[size_] = '\0';
}

astring& astring::operator= (const char* that) {
   size_ = strlen (that);
   reserve (size_ + 1);
   strcpy (buffer_, that);
   return *this;
}

astring& astring::operator+= (const char achar) {
   ++size_;
   reserve (size_ + 1);
   buffer_[size_ - 1] = achar;
   buffer_[size_] = '\0';
   return *this;
}

astring& astring::operator+= (const char* cstr) {
   size_ += strlen (cstr);
   reserve (size_ + 1);
   strcat (buffer_, cstr);
   return *this;
}

char astring::operator[] (size_t pos) const {
   range_check (pos, "operator[]");
   return buffer_[pos]; // no bounds check
}

char& astring::operator[] (size_t pos) {
   range_check (pos, "operator[]");
   return buffer_[pos]; // no bounds check
}

void astring::reserve (size_t capacity) {
   if (capacity < capacity_) return;
   capacity_ *= 2;
   if (capacity_ < capacity) capacity_ = capacity + 1;
   char* oldbuffer_ = buffer_;
   buffer_ = new char[capacity_];
   strcpy (buffer_, oldbuffer_);
   delete[] oldbuffer_;
}


size_t astring::size() const {
   return size_;
}

const char* astring::c_str() const {
   return buffer_;
}

ostream& operator<< (ostream& out, const astring& that) {
   out << that.buffer_;
   return out;
}

/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main (int argc, char** argv) {
   astring first = "Hello, World!";
   cout << "first=" << first << endl;
   astring second;
   second = first;
   second += 'x'; second += 'y';
   for (int i = 0; i < 3; ++i) second[i] = i + '1';
   cout << "second=" << second << endl;
   for (size_t i = 5; i < second.size(); ++i) {
      cout << second[i] << endl;
   }
   astring allargs = "args:";
   for (char** arg = &argv[1]; arg < &argv[argc]; ++arg) {
      (allargs += " ") += *arg;
   }
   cout << allargs << endl;
   cout << allargs.c_str() << endl;
   return EXIT_SUCCESS;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=astring.out.grind \
//TEST//       astring foo bar baz >astring.out 2>&1
//TEST// mkpspdf astring.ps astring.cpp* astring.out*
*/

