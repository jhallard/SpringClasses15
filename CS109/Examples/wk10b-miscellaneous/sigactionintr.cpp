// $Id: sigactionintr.cpp,v 1.2 2013-03-13 19:42:36-07 - - $

//
// Program does nothing except echo input line by line.
// However, at every SIGINT (Ctrl/C), it prints a message
// acknowledging the Ctrl/C, but the program does not abort
// as is usual without a signal.
//

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <stdexcept>

#include <signal.h>
#include <unistd.h>

using namespace std;

string progname;

string basename (const string &arg) {
   return arg.substr (arg.find_last_of ('/') + 1);
}

void syserror (const string &object) {
   throw runtime_error (object + ": " + strerror (errno));
}

void print_pid() {
   static int pid = getpid();
   cout << "[" << pid << "]" << progname << ": ";
}

extern "C" {
   static volatile int action_count = 0;
   void action_handler (int signo) {
      ++action_count;
      print_pid();
      cout << "Caught signal " << signo
           << ", action_count " << action_count << endl;
   }
}

void shell() {
   // Fake shell.  Just loop printing messages.  Watch for SIGINT.
   cout << "Entering shell." << endl;
   for (int count = 0; ; ++count) {
      sleep (1);
      print_pid();
      cout << "Shell count " << count
           << ", action_count " << action_count << endl;
      if (action_count > 9) throw runtime_error ("action_count > 9");
   }
}

int main (int argc, char **argv) {
   argc = argc; // warning: unused parameter 'argc'
   progname = basename (argv[0]);

   try {

      // Initialize signal handler.
      struct sigaction newaction, oldaction;
      sigemptyset (&newaction.sa_mask);
      newaction.sa_handler = action_handler;
      newaction.sa_flags = 0;
      int sigaction_rc = sigaction (SIGINT, &newaction, &oldaction);
      if (sigaction_rc < 0) syserror ("sigaction (SIGINT)");
      cout << progname << ": " << "signal (SIGINT) = " << sigaction_rc
           << endl;

      cout << "Just before calling shell." << endl;
      shell();
      
   }catch (exception &error) {
      cerr << progname << ": " << error.what() << endl;
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

