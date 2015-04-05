// $Id: arraystritor.cpp,v 1.7 2015-01-06 17:24:07-08 - - $

//
// Array of string class with iterator.
//

#include <iostream>
#include <string>
using namespace std;

class arraystr {
   private:
      size_t size_;
      string* data_ {};
      arraystr() = delete;
      arraystr (arraystr&) = delete;
      arraystr (arraystr&&) = delete;
      arraystr& operator= (arraystr&) = delete;
      arraystr& operator= (arraystr&&) = delete;
   public:
      class iterator {
         friend class arraystr;
         private:
            string* pointee_;
            iterator (string*);
         public:
            bool operator!= (iterator&);
            string& operator*();
            iterator& operator++();
      };
      arraystr (size_t size);
      ~arraystr();
      iterator begin();
      iterator end();
      string& operator[] (size_t index);
      size_t size();
};

arraystr::arraystr (size_t size):
            size_(size),
            data_(new string[size]) {
}

arraystr::~arraystr() {
   delete[] data_;
}

arraystr::iterator arraystr::begin() {
   return iterator (&data_[0]);
}

arraystr::iterator arraystr::end() {
   return iterator (&data_[size_]);
}

string& arraystr::operator[] (size_t index) {
   return &data_[index];
}

size_t arraystr::size() {
   return size_;
}

arraystr::iterator::iterator (string* pointee):
            pointee_(pointee) {
}

bool arraystr::iterator::operator!= (iterator& that) {
   return this->pointee_ != that.pointee_;
}

string& arraystr::iterator::operator*() {
   return *pointee_;
}

arraystr::iterator& arraystr::iterator::operator++() {
   ++pointee_;
   return *this;
}

int main (int argc, char** argv) {
   arraystr as (argc - 1);
   for (int index = 1; index < argc; ++index) {
      as[index - 1] = argv[index];
   }
   for (auto itor = as.begin(); itor != as.end(); ++itor) {
      cout << *itor << endl;
   }
   return 0;
}

