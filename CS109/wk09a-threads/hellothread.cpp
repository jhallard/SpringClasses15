// $Id: hellothread.cpp,v 1.9 2014-06-03 13:19:51-07 - - $

// Hello to threads.

#include <iostream>
#include <thread>
using namespace std;

void hello() {
   cout << "Hello, threads." << endl;
}

int main () {
   thread t1 (hello);
   t1.join();
   return 0;
}

//TEST// hellothread >hellothread.out
//TEST// mkpspdf hellothread.ps hellothread.cpp* hellothread.out

