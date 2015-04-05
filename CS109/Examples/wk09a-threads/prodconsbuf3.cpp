// $Id: prodconsbuf3.cpp,v 1.29 2014-06-04 12:06:43-07 - - $

// Producer/consumer problem using mutex and condition_variable.

#include <array>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <iomanip>
#include <iostream>
#include <mutex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

//
// Timer.
//
class elapsed_time {
   private:
      using clock = chrono::high_resolution_clock;
      clock::time_point start {clock::now()};
   public: 
      double elapsed_nanoseconds() {
         clock::time_point now = clock::now();
         return chrono::duration_cast<chrono::nanoseconds> (now - start)
                .count() / 1e9;
      }
} timer;


//
// Printer for synchronized output accepts a variable number
// of arguments.
//

class synch_printer {
   private:
      mutex out_mutex;
      ostream& out;
      void print_();
      template <typename Head, typename... Tail>
      void print_ (const Head& head, Tail... tail);
   public:
      synch_printer (ostream& out): out(out){}
      template <typename... Type>
      void print (Type... params);
};

void synch_printer::print_() {
}

template <typename Head, typename... Tail>
void synch_printer::print_ (const Head& head, Tail... tail) {
   out << head;
   print_ (tail...);
}

template <typename... Type>
void synch_printer::print (Type... params) {
   unique_lock<mutex> lock {out_mutex};
   out << setw(9) << setprecision(6) << fixed
       << timer.elapsed_nanoseconds() << " ";
   print_ (params...);
   out << endl << flush;
}

//
// Trace block/function entry/exit.

class start_trace {
   private:
      const string name;
      synch_printer& printer;
   public:
      start_trace (string name, synch_printer& printer):
                   name(name), printer(printer) {
         printer.print (name, " STARTING");
      }
      ~start_trace() { printer.print (name, " FINISHED"); }
};


//
// class bounded_buffer
// NOT synchronized.
// Just your ordinary Data Structures queue.
//

template <typename Type, size_t size>
class bounded_buffer {
   public:
      using value_type = Type;
   private:
      static constexpr ssize_t EMPTY {-1};
      ssize_t head {EMPTY};
      ssize_t tail {EMPTY};
      array<Type,size> items;
   public:
      bool empty() const { return head == EMPTY; }
      bool full() { return (tail + 1) % size == head; }
      const value_type& front() const;
      void pop_front();
      void push (const value_type& val);
};

class bounded_buffer_error: public runtime_error {
   public:
      explicit bounded_buffer_error (const string& what);
};

bounded_buffer_error::bounded_buffer_error (const string& what):
            runtime_error (what) {
}

template <typename Type, size_t size>
const Type& bounded_buffer<Type,size>::front() const {
   if (empty()) throw bounded_buffer_error ("front (empty)");
   return items[head];
}

template <typename Type, size_t size>
void bounded_buffer<Type,size>::pop_front() {
   if (empty()) throw bounded_buffer_error ("pop_front (empty)");
   if (head == tail) head = tail = EMPTY;
                else head = (head + 1) % size;
}

template <typename Type, size_t size>
void bounded_buffer<Type,size>::push (const value_type& val) {
   if (full()) throw bounded_buffer_error ("push (full)");
   if (empty()) head = tail = 0;
           else tail = (tail + 1) % size;
   items[tail] = val;
}


//
// class synchronized_buffer
// prevents concurrent access and uses the bounded_buffer.
//

template <typename Type, size_t size>
class synchronized_buffer {
   public:
      using value_type = Type;
   private:
      bounded_buffer<Type,size> buffer;
      mutex lock;
      condition_variable put_wait;
      condition_variable get_wait;
      bool producers_gone {false};
   public:
      struct end_data: public exception{};
      void put (const value_type& val);
      value_type get();
      void end_data_notify_all();
};

template <typename Type, size_t size>
void synchronized_buffer<Type,size>::put (const value_type& val) {
   unique_lock<mutex> ulock (lock);
   while (buffer.full()) put_wait.wait (ulock);
   buffer.push (val);
   get_wait.notify_one();
}

template <typename Type, size_t size>
Type synchronized_buffer<Type,size>::get() {
   unique_lock<mutex> ulock (lock);
   while (buffer.empty()) {
      if (producers_gone) throw end_data();
                     else get_wait.wait (ulock);
   }
   value_type result = buffer.front();
   buffer.pop_front();
   put_wait.notify_one();
   return result;
}

template <typename Type, size_t size>
void synchronized_buffer<Type,size>::end_data_notify_all() {
   unique_lock<mutex> ulock (lock);
   producers_gone = true;
   get_wait.notify_all();
}


//
// Producer and consumer threads.
//

using buf_data = pair<string,int>;
using synch_buffer = synchronized_buffer<buf_data,5>;
string to_string (const buf_data& data) {
   return " [\"" + data.first + "\"," + to_string (data.second) + "]";
}

void producer (int id, synch_buffer& buffer, synch_printer &mcout,
               const vector<string>& words) {
   start_trace trace ("producer " + to_string (id), mcout);
   for (const auto& word: words) {
      this_thread::sleep_for (chrono::milliseconds (id * 300));
      buf_data data {word, id};
      buffer.put (data);
      mcout.print ("producer ", id, to_string (data));
   }
}

void consumer (int id, synch_buffer& buffer, synch_printer &mcout) {
   start_trace trace ("consumer " + to_string (id), mcout);
   try {
      for(;;) {
         this_thread::sleep_for (chrono::milliseconds (id * 600));
         auto data = buffer.get();
         mcout.print ("consumer ", id, to_string (data));
      }
   }catch (synch_buffer::end_data&) {
      mcout.print ("consumer ", id, " caught end_data");
   }
}


//
// Main.
//

template <typename number, class Function>
void for_each (number start, number end, Function fn) {
   for (; start != end; ++start) fn (start);
}

int main() {
   synch_printer mcout (cout);
   start_trace trace ("main", mcout);
   synch_buffer buffer;
   vector<thread> producers;
   vector<thread> consumers;
   vector<string> words {"Hello", "World", "foo", "bar", "baz", "qux"};
   for_each (1, 4, [&] (int id) {
      producers.push_back (thread (producer, id, ref (buffer),
                           ref (mcout), ref (words)));
   });
   for_each (4, 7, [&] (int id) {
      consumers.push_back (thread (consumer, id, ref (buffer),
                           ref (mcout)));
   });
   for (auto& t: producers) t.join();
   buffer.end_data_notify_all();
   for (auto& t: consumers) t.join();
   return 0;
}

//TEST// prodconsbuf3 >prodconsbuf3.out 2>&1
//TEST// mkpspdf prodconsbuf3.ps prodconsbuf3.cpp* prodconsbuf3.out

