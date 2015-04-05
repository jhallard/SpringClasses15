// $Id: queue_vec.cpp,v 1.10 2014-07-18 15:53:49-07 - - $

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

template <typename item_t>
class queue {
   private:
      vector<item_t> front_vec;
      vector<item_t> back_vec;
      size_t front_pos {};
      void maybe_switch();
   public:
      item_t& front() { return front_vec[front_pos]; }
      const item_t& front() const { return front_vec[front_pos]; }
      void pop_front();
      void push_back (const item_t& val);
      void push_back (item_t&& val);
      size_t size() const;
      bool empty() const { return size() == 0; }
};

template <typename item_t>
void queue<item_t>::maybe_switch() {
   if (front_pos == front_vec.size()) {
      front_vec.clear();
      front_pos = 0;
      if (back_vec.size() > 0) std::swap (front_vec, back_vec);
   }
}

template <typename item_t>
void queue<item_t>::pop_front() {
   item_t tmp = std::move (front_vec[front_pos++]);
   maybe_switch();
}

template <typename item_t>
void queue<item_t>::push_back (const item_t& val) {
   back_vec.push_back (val);
   maybe_switch();
}

template <typename item_t>
void queue<item_t>::push_back (item_t&& val) {
   back_vec.push_back (val);
   maybe_switch();
}

template <typename item_t>
size_t queue<item_t>::size() const {
   return back_vec.size() + front_vec.size() - front_pos;
}


int main (int argc, char** argv) {
   queue<string> que;
   for_each (&argv[0], &argv[argc],
             [&] (char* arg) { que.push_back (arg); });
   while (not que.empty()) {
      cout << que.front() << endl;
      que.pop_front();
   }
   cout << "sizeof queue<string> = " << sizeof (queue<string>) << endl;
}

/*
//TEST// alias grind='valgrind --leak-check=full --show-reachable=yes'
//TEST// grind queue_vec This is a test of queue_vec. \
//TEST//       >queue_vec.out 2>&1
//TEST// mkpspdf queue_vec.ps queue_vec.cpp* queue_vec.out
*/

