// $Id: itortempl.cpp,v 1.3 2013-02-26 16:53:38-08 - - $

#include <cassert>
#include <iostream>
#include <string>

using namespace std;

/////////////////////////////////////////////////////////////////
// queue.h
/////////////////////////////////////////////////////////////////

template <class item_t>
class queue {
   private:
      class node {
         friend class queue;
         friend class iterator;
         item_t item;
         node *link;
         node (const item_t &);
         ~node ();
      };
      node *head;
      node *tail;
   public:
      class iterator {
         friend class queue;
         public:
            ~iterator ();
            item_t &operator* () const;
            iterator &operator++ (); // ++itor.
            bool operator != (const iterator &) const;
         private:
            explicit iterator (node *where);
            iterator () = delete;
            node *where;
      };
      queue ();
      queue (const queue &);
      queue &operator= (const queue &);
      ~queue ();
      bool empty () const;
      item_t front () const;
      void push_back (const item_t &);
      void pop_front ();
      iterator begin () const;
      iterator end () const;
};

/////////////////////////////////////////////////////////////////
// queue.cc
/////////////////////////////////////////////////////////////////

template <class item_t>
queue<item_t>::node::node (const item_t &item): item(item) {
}

template <class item_t>
queue<item_t>::node::~node () {
}

template <class item_t>
item_t &queue<item_t>::iterator::operator* () const {
   return where->item;
}

template <class item_t>
typename queue<item_t>::iterator &
queue<item_t>::iterator::operator++ () {
   where = where->link;
   return *this;
}

template <class item_t>
queue<item_t>::iterator::~iterator () {
}

template <class item_t>
bool queue<item_t>::iterator::operator!= (const iterator &that) const {
   return where != that.where;
}

template <class item_t>
queue<item_t>::iterator::iterator (node *where): where(where) {
}

template <class item_t>
queue<item_t>::queue (): head(NULL), tail(NULL) {
}

template <class item_t>
queue<item_t>::queue (const queue<item_t> &that) {
   *this = that;
}

template <class item_t>
queue<item_t> &queue<item_t>::operator= (const queue<item_t> &that) {
   if (this == &that) return *this;
   while (! empty ()) pop_front ();
   queue<item_t>::iterator itor = that.begin ();
   queue<item_t>::iterator end = that.end ();
   for (; itor != end; ++itor) {
      push_back (*itor);
   }
   return *this;
}

template <class item_t>
queue<item_t>::~queue () {
   while (! empty()) pop_front ();
}

template <class item_t>
bool queue<item_t>::empty () const {
   return head == NULL;
}

template <class item_t>
item_t queue<item_t>::front () const {
   return head->item;
}

template <class item_t>
void queue<item_t>::push_back (const item_t &that) {
   node *newnode = new node (that);
   if (empty()) head = newnode;
           else tail->link = newnode;
   tail = newnode;
}

template <class item_t>
void queue<item_t>::pop_front () {
   assert (! empty());
   node *first = head;
   head = head->link;
   if (empty()) tail = NULL;
   delete first;
}

template <class item_t>
typename queue<item_t>::iterator queue<item_t>::begin () const {
   return iterator (head);
}

template <class item_t>
typename queue<item_t>::iterator queue<item_t>::end () const {
   return iterator (NULL);
}

/////////////////////////////////////////////////////////////////
// main.cc
/////////////////////////////////////////////////////////////////

template <class item_t>
void exercise (item_t *array, int size) {
   queue<item_t> list;
   for (int itor = 0; itor < size; ++itor) {
      list.push_back (array[itor]);
   }
   typename queue<item_t>::iterator itor = list.begin();
   typename queue<item_t>::iterator end = list.end();
   for (; itor != end; ++itor) {
      cout << *itor << endl;
   }
}

int main () {
   string str[] = {"hello", "world", "foo", "bar"};
   exercise (str, sizeof str / sizeof *str);
   int num[] = {3, 1, 4, 1, 5, 9};
   exercise (num, sizeof num / sizeof *num);
   return 0;
}

