// $Id: linkstrstack.cpp,v 1.4 2013-08-08 14:45:56-07 - - $

//
// linkstrstack - show the linked list implementation of a stackk
//

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////
// linkstrstack.h
/////////////////////////////////////////////////////////////////

class linkstrstack {
   private:
      struct node {
         string item;
         node *link;
      };
      node *topnode;
      int count;
      linkstrstack (const linkstrstack &) = delete;
      linkstrstack (linkstrstack &&) = delete;
      linkstrstack &operator= (const linkstrstack &) = delete;
      linkstrstack &operator= (linkstrstack &&) = delete;
   public:
      linkstrstack();
      ~linkstrstack();
      void push (const string &);
      void pop();
      string &top();
      const string &top() const;
      size_t size() const;
      bool empty() const;
};


/////////////////////////////////////////////////////////////////
// linkstrstack.cpp
/////////////////////////////////////////////////////////////////

linkstrstack::linkstrstack(): topnode (NULL), count(0) {
}

linkstrstack::~linkstrstack() {
   while (not empty()) pop();
}

void linkstrstack::push (const string &item) {
   node *tmp = new node();
   tmp->item = item;
   tmp->link = topnode;
   topnode = tmp;
   ++count;
}

void linkstrstack::pop() {
   if (empty()) throw out_of_range ("linkstrstack::pop()");
   node *tmp = topnode;
   topnode = topnode->link;
   delete tmp;
   --count;
}

string &linkstrstack::top() {
   if (empty()) throw out_of_range ("linkstrstack::top()");
   return topnode->item;
}

const string &linkstrstack::top() const {
   if (empty()) throw out_of_range ("linkstrstack::top()");
   return topnode->item;
}

size_t linkstrstack::size() const {
   return count;
}

bool linkstrstack::empty() const {
   return count == 0;
}


/////////////////////////////////////////////////////////////////
// main.cpp
/////////////////////////////////////////////////////////////////

int main (int argc, char **argv) {

   linkstrstack stkstr;
   for (int argi = 1; argi < argc; ++argi) {
      stkstr.push (argv[argi]);
   }
   while (stkstr.size() > size_t (argc / 2)) {
      cout << stkstr.top() << endl;
      stkstr.pop();
   }

   return 0;
}

/*
//TEST// valgrind --leak-check=full --show-reachable=yes \
//TEST//       --log-file=linkstrstack.out.grind \
//TEST//       linkstrstack this is some test data for the stack \
//TEST//       >linkstrstack.out 2>&1
//TEST// mkpspdf linkstrstack.ps linkstrstack.cpp* linkstrstack.out*
*/

