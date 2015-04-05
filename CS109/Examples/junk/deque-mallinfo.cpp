#include <cstring>
#include <iostream>
#include <list>
#include <unordered_map>
#include <deque>
#include <vector>
using namespace std;

#include <malloc.h>

class bdeque: public deque<size_t> {
   public:
      using deque<size_t>::_Map_pointer;
      using deque<size_t>::_S_buffer_size;
};

void print_mallinfo() {
   struct mallinfo info = mallinfo();
   cout << info.arena << " non-mmapped space from system" << endl;
   cout << info.ordblks << " number of free chunks" << endl;
   cout << info.smblks << " number of fastbin blocks" << endl;
   cout << info.hblks << " number of mmapped regions" << endl;
   cout << info.hblkhd << " space in mmapped regions" << endl;
   cout << info.usmblks << " maximum total allocated space" << endl;
   cout << info.fsmblks << " space in freed fastbin blocks" << endl;
   cout << info.uordblks << " total allocated space" << endl;
   cout << info.fordblks << " total free space" << endl;
   cout << info.keepcost << " top-most, releasable space" << endl;
}

int main () {
   deque<size_t> di;
   cout << sizeof di << endl;
   print_mallinfo();
   for (size_t i = 0; i < 1000; ++i) {
      for (size_t j = 0; j < 10000; ++j) di.push_back (j);
      while (di.size() > 1000) di.pop_front();
   }
   print_mallinfo();
   return 0;
}
