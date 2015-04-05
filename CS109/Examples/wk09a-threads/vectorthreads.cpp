// $Id: vectorthreads.cpp,v 1.7 2014-06-03 13:20:33-07 - - $

// Have a vector of chatty threads.

#include <iostream>
#include <string>
#include <thread>
#include <vector>
using namespace std;

void hello (size_t seqnr) {
   cout << "Hello " << seqnr << " is thread id "
        << this_thread::get_id() << endl;
}

int main () {
   cout << "thread::hardware_concurrency() = "
        << thread::hardware_concurrency() << endl;
   vector<thread> threads;
   for (size_t i = 0; i < 16; ++i) {
      cout << "Starting thread " << i << endl;
      threads.push_back (thread (hello, i));
   }
   for (auto& thr: threads) {
      cout << "Joining" << endl;
      thr.join();
   }
}

//TEST// vectorthreads >vectorthreads.out
//TEST// mkpspdf vectorthreads.ps vectorthreads.cpp* vectorthreads.out
