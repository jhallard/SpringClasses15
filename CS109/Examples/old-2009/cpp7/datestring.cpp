// $Id: datestring.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

#include <cassert>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

string datestring () {
   time_t clock = time (NULL);
   assert (clock >= 0);
   struct tm tm_buf;
   struct tm *tm_ptr = localtime_r (&clock, &tm_buf);
   char timebuf[64];
   size_t bufsize = strftime (timebuf, sizeof timebuf,
          "%a %b %e %H:%M:%S %Z %Y", tm_ptr);
   assert (bufsize > 0);
   return timebuf;
}

int main () {
   cout << datestring () << endl;
   return EXIT_SUCCESS;
}

