// $Id: unique_ptr.cpp,v 1.1 2014-06-06 18:30:08-07 - - $

#include <iostream>
#include <memory>
#include <string>
using namespace std;

class tree;
using tree_ptr = unique_ptr<tree>;
class tree {
   private:
      string value;
      tree_ptr left;
      tree_ptr right;
      void trace();
      void* addr (tree_ptr);
   public:
      tree (const string& val, tree_ptr left = {}, tree_ptr right = {});
      tree();
      ~tree();
      tree (const tree&);
      tree (tree&&);
      tree& operator= (const tree&);
      tree& operator= (tree&&);
};

void* tree::addr (const tree* ptr) {
   return static_cast<void*> (ptr);
}

void tree::trace (const string& caller, const tree* ptr) {
   cout << caller << ": " << addr(ptr) << "->tree{" << value << ","
        << addr(ptr->left) << addr(ptr->right) << "}" << endl;
}

tree::tree (const string& val, tree_ptr left, tree_ptr right):
            value(val), left(left), right(right) {
   trace ("tree::tree(,,)", this);
}

tree::tree(): tree(string{}) {
   trace ("tree::tree()", this);
}

tree::~tree() {
   trace ("tree::~tree()", this);
}

tree::tree (const tree& that) {
}

tree::tree (tree&& that) {
}

tree& tree::operator= (const tree& that) {
   if (this == &that) return *this;
   this->value = that.value;
}

tree& tree::operator= (tree&& that) {
}

