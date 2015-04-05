// $Id: signalintr.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

//
// Program does nothing except echo input line by line.
// However, at every SIGINT (Ctrl/C), it prints a message
// acknowledging the Ctrl/C, but the program does not abort
// as is usual without a signal.
//

#include <cerrno>
#include <csignal>
#include <csignal>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

using namespace std;

string progname;

string basename (const string &arg) {
   return arg.substr (arg.find_last_of ('/') + 1);
}

void syserror (const string &object) {
   throw runtime_error (object + ": " + strerror (errno));
}

class interrupt: public exception {};

extern "C" {
   typedef void (*signal_rc) (int);
   void sig_interrupt (int signo) {
      static volatile int count = 0;
      signal_rc sigrc = signal (SIGINT, sig_interrupt);
      if (sigrc == SIG_ERR) syserror ("signal (SIGINT)");
      cout << "Caught signal " << signo << ", count = " << ++count
           << ", sigrc = " << reinterpret_cast <uintptr_t> (sigrc)
           << endl;
      throw interrupt ();
   }
}

void shell () {
   int pid = getpid ();
   for (;;) {
      try {
         cout << "[" << pid << "]" << progname << "% ";
         string line;
         getline (cin, line);
         if (cin.eof ()) break;
         if (cin.fail ()) {
            cout << "Getline: failed." << endl;
            cin.clear ();
            continue;
         }
         cout << "Command = " << line << endl;
      }catch (interrupt error) {
         cout << progname << ": Caught interrupt." << endl;
      }
   }
}

int main (int argc, char **argv) {
   progname = basename (argv[0]);

   try {

      // Initialize signal handler.
      signal_rc sigrc = signal (SIGINT, sig_interrupt);
      if (sigrc == SIG_ERR) syserror ("signal (SIGINT)");
      cout << progname << ": " << "signal (SIGINT) = " << sigrc << endl;

      // Run the echo shell.
      shell ();
      
   }catch (exception &error) {
      cerr << progname << ": " << error.what () << endl;
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

