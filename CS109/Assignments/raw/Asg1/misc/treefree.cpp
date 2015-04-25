// $Id: treefree.cpp,v 1.71 2015-03-26 22:15:48-07 - - $

// Shared_ptrs use reference counting in order to automatically
// free objects, but that does not work for cyclic data structures.
// This illustrates how to avoid the problem.

#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
using namespace std;

/////////////////////////////////////////////////////////////////
// tree.h
/////////////////////////////////////////////////////////////////

class tree;
using tree_ptr = shared_ptr<tree>;
using tree_dir = map<string,tree_ptr>;
using tree_itor = tree_dir::iterator;

class tree {
      friend ostream& operator<< (ostream&, const tree*);
   private:
      static size_t next_seq;
      size_t seq;
      tree_dir data;
      void print (size_t);
      void disown (size_t);
   public:
      static const string PARENT;
      static tree_ptr make_root();
      static tree_ptr make (tree_ptr ptr);
      tree (tree_ptr parent);
      ~tree();
      void emplace (const tree_dir::key_type&,
                    const tree_dir::mapped_type&);
      const tree_itor begin() { return data.begin(); }
      const tree_itor end() { return data.end(); }
      void print() { print (0); }
      void disown() { disown (0); }
};


/////////////////////////////////////////////////////////////////
// tree.cpp
/////////////////////////////////////////////////////////////////

size_t tree::next_seq {0};
const string tree::PARENT = "..";

ostream& operator<< (ostream& out, const tree* ptr) {
   if (ptr == nullptr) return out << "nullptr";
                  else return out << "[" << ptr->seq << "]"
                           << static_cast<const void*> (ptr);
}

tree::tree (tree_ptr parent): seq(next_seq++), data({{PARENT,parent}}) {
   cout << this << "->" << __func__ << "(" << parent << ")" << endl;
}

tree::~tree() {
   cout << this << "->" << __func__ << "()" << endl;
}

void tree::emplace (const tree_dir::key_type& key,
                    const tree_dir::mapped_type& value) {
   data.emplace (key, value);
}

void tree::disown (size_t depth) {
   cout << __func__ << ": " << setw (depth * 3) << "" << this << endl;
   data.erase (PARENT);
   for (auto n: data) n.second->disown (depth + 1);
}

// Depth-first pre-order traversal.
void tree::print (size_t depth) {
   for (const auto itor: data) {
      cout << __func__ << ": " << setw (depth * 3) << "" << this
           << ": \"" << itor.first << "\" -> " << itor.second
           << " (" << itor.second.use_count() << ")" << endl;
      if (itor.first != PARENT and itor.second != nullptr) {
         itor.second->print (depth + 1);
      }
   }
}

tree_ptr tree::make_root() {
   tree_ptr ptr = make_shared<tree> (nullptr);
   ptr->data[PARENT] = ptr;
   return ptr;
}

tree_ptr tree::make (tree_ptr parent) {
   if (parent == nullptr) throw logic_error ("tree::make(nullptr)");
   return make_shared<tree> (parent);
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main (int argc, char** argv) {
   (void) argc;
   (void) argv;
   shared_ptr<tree> root = tree::make_root();
   root->emplace ("foo", tree::make (root));
   root->emplace ("bar", tree::make (root));
   for (auto itor: *root) {
      if (itor.first == tree::PARENT) continue;
      for (int count = 0; count < 3; ++count) {
         string quux = "qux";
         quux.insert (1, count, 'u');
         itor.second->emplace (quux, tree::make (itor.second));
      }
   }
   cout << "[seq]address: key -> value (use count)" << endl;
   root->print();
   root->disown();
   return 0;
}

//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind treefree >treefree.out 2>treefree.ground
//TEST// mkpspdf treefree.ps treefree.cpp* treefree.out treefree.ground

