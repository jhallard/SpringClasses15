// $Id: raceclick.cpp,v 1.16 2014-05-30 22:45:27-07 - - $

// Hello to threads.

#include <iostream>
#include <thread>
#include <vector>
using namespace std;

constexpr size_t LOOPS = 1000000;

void racer (size_t id, size_t* counter) {
   cout << "racer " << id << " looping " << LOOPS << " times" << endl;
   for (size_t i = 0; i < LOOPS; ++i) ++*counter;
   cout << "racer " << id << " finished counter " << *counter << endl;
}

int main () {
   size_t counter {0};
   cout << "main starting" << endl;
   vector<thread> vecthr;
   for (size_t i = 0; i < 4; ++i) {
      vecthr.push_back (thread (racer, i, &counter));
   }
   for (auto& t: vecthr) t.join();
   cout << "main finished counter " << counter << endl;
   return 0;
}

//TEST// alias TIME='/usr/bin/time -f "%E elapsed, %S kernel, %U user"'
//TEST// for i in 1 2 3 4
//TEST// do
//TEST//    TIME raceclick >raceclick.out$i 2>&1
//TEST// done
//TEST// more raceclick.out* >raceclick.lis </dev/null
//TEST// mkpspdf raceclick.ps raceclick.cpp* raceclick.lis

