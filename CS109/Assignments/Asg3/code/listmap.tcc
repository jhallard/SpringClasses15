// $Id: listmap.tcc,v 1.7 2015-04-28 19:22:02-07 - - $

// @author John Allard
// @file listmap.tcc
// @date May 9th 2015
// @project Asg3 UCSC CMPS-109 


#include "listmap.h"
#include "trace.h"

//
/////////////////////////////////////////////////////////////////
// Operations on listmap::node.
/////////////////////////////////////////////////////////////////
//

//
// listmap::node::node (link*, link*, const value_type&)
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::node::node (node* next, node* prev,
                                     const value_type& value):
            link (next, prev), value (value) {
}

//
/////////////////////////////////////////////////////////////////
// Operations on listmap.
/////////////////////////////////////////////////////////////////
//

//
// listmap::~listmap()
//
template <typename Key, typename Value, class Less>
listmap<Key,Value,Less>::~listmap() {
   TRACE ('l', (void*) this);

   for(auto it = begin(); it != end();) {
     auto tbd = it;
     ++it;
     erase(tbd);
   }
}


//
// iterator listmap::insert (const value_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::insert (const value_type& pair) {
   TRACE ('l', &pair << "->" << pair);
  
   // @TODO - This function is supposed to insert such that
   // the list will always be sorted, but the first two 
   // elements inserted always end up at the back. 
   node * new_n = new node(anchor()->next, anchor(), pair);
   if(find(pair.first) != end()) {
      erase(find(pair.first));
   }   
   auto it = begin();
   bool inserted = false;
   while(it != end()) {
      if(pair.first < it->first) {
        auto ti = it.where;
        if(ti->prev != nullptr) {
          ti->prev->next = new_n;
        }
        new_n->next = ti;
        new_n->prev = ti->prev;
        ti->prev = new_n;
        inserted = true;
        break;
      }
      ++it;
   }

   if(!inserted) {

    if(anchor()->prev) {
      anchor()->prev->next = new_n;
     }
     new_n->prev = anchor()->prev;
     anchor()->prev = new_n;
     new_n->next = anchor();
   }

   return iterator(new_n);
}

//
// listmap::find(const key_type&)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::find (const key_type& that) {
   TRACE ('l', that);

   for(auto it = anchor()->next; it != anchor(); it=it->next){
        // see if the node is the one we're looking for, if
        // so, return an iterator to it
        if(it->value.first == that) {
            return it;
        }
   }

   return end();
}

//
// iterator listmap::erase (iterator position)
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator
listmap<Key,Value,Less>::erase (iterator position) {
   TRACE ('l', &*position);
   
   auto pos = position.where;
   auto ret = pos->next;
   pos->next->prev = pos->prev;
   pos->prev->next = pos->next;

   position.erase();

   return iterator(ret);
}


//
/////////////////////////////////////////////////////////////////
// Operations on listmap::iterator.
/////////////////////////////////////////////////////////////////
//

//
// listmap::value_type& listmap::iterator::operator*()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type&
listmap<Key,Value,Less>::iterator::operator*() {
   TRACE ('l', where);
   return where->value;
}

//
// listmap::value_type* listmap::iterator::operator->()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::value_type*
listmap<Key,Value,Less>::iterator::operator->() {
   TRACE ('l', where);
   return &(where->value);
}

//
// listmap::iterator& listmap::iterator::operator++()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator++() {
   TRACE ('l', where);
   where = where->next;
   return *this;
}

//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
typename listmap<Key,Value,Less>::iterator&
listmap<Key,Value,Less>::iterator::operator--() {
   TRACE ('l', where);
   where = where->prev;
   return *this;
}



//
// listmap::iterator& listmap::iterator::operator--()
//
template <typename Key, typename Value, class Less>
void listmap<Key,Value,Less>::iterator::erase() {
   TRACE ('l', where);
   delete where;
}



//
// bool listmap::iterator::operator== (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator==
            (const iterator& that) const {
   return this->where == that.where;
}

//
// bool listmap::iterator::operator!= (const iterator&)
//
template <typename Key, typename Value, class Less>
inline bool listmap<Key,Value,Less>::iterator::operator!=
            (const iterator& that) const {
   return this->where != that.where;
}

