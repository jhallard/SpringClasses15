// $Id: prodconsbuf2.cpp,v 1.1 2014-06-02 11:47:42-07 - - $

// Producer/consumer problem using mutex and condition_variable.

#include <array>
#include <condition_variable>
#include <iomanip>
#include <cassert>
#include <chrono>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

#include <sys/time.h>

//
// Timer.
//
class elapsed_time {
   private:
      struct timeval start;
   public: 
      elapsed_time() { gettimeofday (&start, nullptr); }
      string elapsed() {
         struct timeval now;
         gettimeofday (&now, nullptr);
         double secs = (double) (now.tv_sec - start.tv_sec)
                     + (double) (now.tv_usec - start.tv_usec) * 1e-6; 
         ostringstream result; 
         result << setw(7) << setprecision(3) << fixed << secs;
         return result.str();
      }
} timer;


//
// class bounded_buffer
// NOT synchronized.
// Just your ordinary 12B Data Structures queue.
//

template <typename T, size_t size>
class bounded_buffer {
   public:
      using value_type = T;
   private:
      static constexpr ssize_t EMPTY = -1;
      ssize_t head = EMPTY;
      ssize_t tail = EMPTY;
      array<T,size> items;
   public:
      // Six synthesizeable are all OK.
      bool empty() const { return head == EMPTY; }
      bool full() { return (tail + 1) % size == head; }
      const value_type& front() const;
      void pop();
      void push (const value_type& val);
};

template <typename T, size_t size>
const T& bounded_buffer<T,size>::front() const {
   if (empty()) throw runtime_error ("bounded_buffer::front (empty)");
   return items[head];
}

template <typename T, size_t size>
void bounded_buffer<T,size>::pop() {
   if (empty()) throw runtime_error ("bounded_buffer::pop (empty)");
   if (head == tail) head = tail = EMPTY;
                else head = (head + 1) % size;
}

template <typename T, size_t size>
void bounded_buffer<T,size>::push (const value_type& val) {
   if (full()) throw runtime_error ("bounded_buffer::push (full)");
   if (empty()) head = tail = 0;
           else tail = (tail + 1) % size;
   items[tail] = val;
}


//
// class synchronized_buffer
// prevents concurrent access and uses the bounded_buffer.
//

template <typename T, size_t size>
class synchronized_buffer {
   public:
      using value_type = T;
   private:
      bounded_buffer<T,size> buffer;
      mutex lock;
      condition_variable prod_wait;
      condition_variable cons_wait;
   public:
      void put (const value_type& val);
      value_type get();
      struct end_data: public exception{};
      bool producers_gone {false};
};

template <typename T, size_t size>
void synchronized_buffer<T,size>::put (const value_type& val) {
   unique_lock<mutex> ulock (lock);
   if (buffer.full()) prod_wait.wait (ulock);
   buffer.push (val);
   cons_wait.notify_one();
}

template <typename T, size_t size>
T synchronized_buffer<T,size>::get() {
   unique_lock<mutex> ulock (lock);
   if (buffer.empty()) {
      if (producers_gone) throw end_data();
                     else cons_wait.wait (ulock);
   }
   value_type result = buffer.front();
   buffer.pop();
   prod_wait.notify_one();
   return result;
}


//
// Buffer and data declarations and printer.
//

using buf_data = pair<string,size_t>;
using synch_buffer = synchronized_buffer<buf_data,5>;
string to_string (const buf_data& data) {
   return " [\"" + data.first + "\"," + to_string (data.second) + "]";
}

class printer {
   private:
      mutex out_mutex;
      ostream& out;
      void prt() {}
      template <typename Head, typename... Tail>
      void prt (const Head& head, Tail... tail) {
         out << head;
         prt (tail...);

      }
   public:
      printer (ostream& out): out(out){}
      template <typename... T>
      void print (T... params) {
         unique_lock<mutex> lock {out_mutex};
         out << timer.elapsed() << " ";
         prt (params...);
         out << endl;
      }
};
printer mcout (cout);


//
// Producer and consumer threads.
//

void producer (size_t id, synch_buffer* buffer,
               const vector<string>* words) {
   mcout.print ("producer ", id, " STARTING");
   for (const auto& word: *words) {
      this_thread::sleep_for (chrono::milliseconds (id * 200));
      buf_data data {word, id};
      buffer->put (data);
      mcout.print ("producer ", id, to_string (data));
   }
   mcout.print ("producer ", id, " FINISHED");
}

void consumer (size_t id, synch_buffer* buffer) {
   mcout.print ("consumer ", id, " STARTING");
   try {
      for(;;) {
         this_thread::sleep_for (chrono::milliseconds (id * 400));
         auto data = buffer->get();
         mcout.print ("consumer ", id, to_string (data));
      }
   }catch (synch_buffer::end_data&) {
      // No more producers, so no more data.
   }
   mcout.print ("consumer ", id, " FINISHED");
}

//
// Main.
//

int main() {
   cout << boolalpha;
   mcout.print ("main STARTING");
   synch_buffer buffer;
   vector<thread> producers;
   vector<thread> consumers;
   vector<string> words {"Hello", "World", "foo", "bar", "baz", "qux"};
   for (size_t i = 1; i <= 3; ++i) {
      producers.push_back (thread (producer, i, &buffer, &words));
   }
   for (size_t i = 1; i <= 3; ++i) {
      consumers.push_back (thread (consumer, i, &buffer));
   }
   for (auto& t: producers) t.join();
   buffer.producers_gone = true;
   for (auto& t: consumers) t.join();
   mcout.print ("main FINISHED");
   return 0;
}

//TEST// prodconsbuf >prodconsbuf.out 2>&1
//TEST// mkpspdf prodconsbuf.ps prodconsbuf.cpp* prodconsbuf.out

