// $Id: mutexclick.cpp,v 1.5 2014-05-30 22:46:35-07 - - $

// Hello to threads.

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
using namespace std;

constexpr size_t LOOPS = 1000000;

class counter {
   private:
      size_t count {0};
      mutex lock;
   public:
      counter& operator++() {
         lock.lock();
         ++count;
         lock.unlock();
         return *this;
      }
      friend ostream& operator<< (ostream&, const counter&);
};

ostream& operator<< (ostream& out, const counter& ctr) {
   out << ctr.count;
   return out;
}

void racer (size_t id, counter* count) {
   cout << "racer " << id << " looping " << LOOPS << " times" << endl;
   for (size_t i = 0; i < LOOPS; ++i) ++*count;
   cout << "racer " << id << " finished counter " << *count << endl;
}

int main () {
   counter count;
   cout << "main starting" << endl;
   vector<thread> vecthr;
   for (size_t i = 0; i < 4; ++i) {
      vecthr.push_back (thread (racer, i, &count));
   }
   for (auto& t: vecthr) t.join();
   cout << "main finished counter " << count << endl;
   return 0;
}

//TEST// alias TIME='/usr/bin/time -f "%E elapsed, %S kernel, %U user"'
//TEST// for i in 1 2 3 4
//TEST// do
//TEST//    TIME mutexclick >mutexclick.out$i 2>&1
//TEST// done
//TEST// more mutexclick.out* >mutexclick.lis </dev/null
//TEST// mkpspdf mutexclick.ps mutexclick.cpp* mutexclick.lis

