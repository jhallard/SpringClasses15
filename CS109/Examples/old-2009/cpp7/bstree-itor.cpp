// $Id: bstree-itor.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

//
// Show how to use a stack to make a tree iterator.
// Code is only partially written with needed functions.
//

#include <cstdlib>
#include <iostream>
#include <stack>
#include <utility>

using namespace std;

template <typename item_t>
class bstree {
   private:
      struct node {
         item_t item;
         node *left;
         node *right;
         node (const item_t &item):
               item (item), left (NULL), right (NULL) {}
      } *root;
      typedef int (*comparefn) (const item_t &, const item_t&);
      comparefn &compare;
   public:
      bstree (): root (NULL), compare (NULL) {}
      bstree (const comparefn &fn): root (NULL), compare (fn) {}
      class iterator {
         friend class bstree;
         private:
            enum view {AS_NODE, AS_TREE};
            typedef pair <node *, view> pairview;
            stack <pairview> state;
            const bstree *tree;
            node *curr;
         public:
            iterator (): curr (NULL) {};
            iterator (const bstree &);
            bool operator!= (const iterator &that) const;
            iterator &operator++ ();
            item_t &operator* ();
      };
      iterator begin ();
      iterator end ();
      void insert (const item_t &);
};

template <typename item_t>
bstree <item_t>:: iterator:: iterator (const bstree &initree):
            tree (&initree), curr (NULL) {
   state.push (pairview (tree->root, AS_TREE));
   ++*this;
}

template <typename item_t>
bool bstree <item_t>:: iterator:: operator!=
(const typename bstree <item_t>:: iterator &that) const {
   return this->curr != that.curr;
}

template <typename item_t>
typename bstree <item_t>:: iterator &
bstree <item_t>:: iterator:: operator++ () {
   if (curr == NULL && state.empty ()) {
      throw domain_error (string (typeid (*this).name ())
            + "::operator++(): increment past end()"); 
   }
   for (;;) {
      if (state.empty ()) {
         curr = NULL;
         break;
      }
      pairview toppair = state.top ();
      state.pop ();
      node *top = toppair.first;
      switch (toppair.second) {
         case AS_NODE:
            curr = top;
            return *this;
         case AS_TREE:
            if (top->right) state.push (pairview (top->right, AS_TREE));
            state.push (pairview (top, AS_NODE));
            if (top->left) state.push (pairview (top->left, AS_TREE));
      }
   }
   return *this;
}

template <typename item_t>
item_t &bstree <item_t>:: iterator:: operator* () {
   return curr->item;
}

template <typename item_t>
typename bstree <item_t>:: iterator
bstree <item_t>:: begin () {
   return bstree <item_t>:: iterator (*this);
}

template <typename item_t>
typename bstree <item_t>:: iterator
bstree <item_t>:: end () {
   return iterator ();
}

template <typename item_t>
void bstree <item_t>:: insert (const item_t &item) {
   // Don't bother with balancing.  See red-black trees in CMPS-101.
   node **currp = &root;
   while (*currp != NULL) {
      int cmp = compare ((*currp)->item, item);
      if (cmp == 0) return;
      if (cmp < 0) currp = &(*currp)->right;
              else currp = &(*currp)->left;
   }
   *currp = new node (item);
}

int strcompare (const string &left, const string &right) {
   return left.compare (right);
}

string basename (const string &arg) {
   return arg.substr (arg.find_last_of ('/') + 1);
}

int main (int argc, char **argv) {
   try {
      bstree <string> tree (strcompare);
      static char *names[] = {"D", "B", "F", "A", "C", "E", "G"};
      static int namesize = sizeof names / sizeof *names;
      for (char **namep = names; namep < names + namesize; ++namep) {
         tree.insert (*namep);
      }
      bstree <string>:: iterator itor = tree.begin ();
      bstree <string>:: iterator end = tree.end ();
      for (; itor != end; ++itor) {
         cout << "*itor = " << *itor << endl;
      }
   }catch (exception &error) {
      cerr << basename (argv[0]) << ": " << error.what () << endl;
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

