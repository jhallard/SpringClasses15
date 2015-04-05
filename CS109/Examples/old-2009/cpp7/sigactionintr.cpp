// $Id: sigactionintr.cpp,v 1.1 2012-06-05 22:12:27-07 - - $

//
// Program does nothing except echo input line by line.
// However, at every SIGINT (Ctrl/C), it prints a message
// acknowledging the Ctrl/C, but the program does not abort
// as is usual without a signal.
//

#include <cerrno>
#include <csignal>
#include <cstdlib>
#include <iostream>
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

void prompt () {
   static int cmdnr = 0;
   static int pid = getpid ();
   cout << "[" << pid << "]" << progname << "-" << ++cmdnr << "% ";
}

extern "C" {
   void action_handler (int signo) {
      static volatile int count = 0;
      cout << endl
           << "Caught signal " << signo << ", count = " << ++count
           << endl;
      prompt ();
   }
}

void shell () {
   for (;;) {
      prompt ();
      string line;
      getline (cin, line);
      if (cin.eof ()) break;
      if (cin.fail()) {
         cout << "File cin failure" << endl;
         cin.clear ();
         continue;
      }
      cout << "Command = " << line << endl;
   }
}

int main (int argc, char **argv) {
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

      // Run the echo shell.
      shell ();
      
   }catch (exception &error) {
      cerr << progname << ": " << error.what () << endl;
      return EXIT_FAILURE;
   }
   return EXIT_SUCCESS;
}

