// $Id: dateserver.cpp,v 1.15 2014-05-23 20:10:08-07 - - $

//
//
// NAME
//    dateserver - accept connections and reply with current date
//
// SYNOPSIS
//    dateserver [host] port
//
// DESCRIPTION
//    If port and host are given, operates as a client and gets
//    the date from the server.
//    if only port is given, operates as a server in an infinite
//    loop returning the date for each connection.
//    Should probably use UDP instead of TCP, but it is easier
//    if we avoid two different protocol discussions.
//    The server also accepts a telnet connection.
//

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>
using namespace std;

#include <libgen.h>
#include <time.h>

#include "../simple-sockets/sockets.h"

string execname;
int exit_status = EXIT_SUCCESS;

template <typename Type>
Type from_string (const string &str) {
   stringstream stream;
   stream << str;
   Type result;
   if (not (stream >> result and stream.eof())) {
      throw domain_error (string (typeid (Type).name())
            + " from_string (" + str + ")");
   }
   return result;
}

void usage() {
   cerr << "Usage: " << execname << " [host] port" << endl;
   exit_status = EXIT_FAILURE;
}


void date_client (vector<string> args) {
   client_socket server (args[0], from_string<in_port_t> (args[1]));
   for (;;) {
      string buffer;
      int nbytes = server.recv (buffer);
      if (nbytes == 0) break;
      cout << buffer;
   }
}

void date_server (vector<string> args) {
   server_socket listener (from_string<in_port_t> (args[0]));
   for (;;) {
      accepted_socket client;
      listener.accept (client);
      time_t now = time (NULL);
      struct tm* localnow = localtime (&now);
      char buffer[64];
      size_t bufbytes = strftime (buffer, sizeof buffer,
                        "%a %b %e %H:%M:%S %Z %Y\n", localnow);
      for (char* bufp = buffer; bufbytes > 0; ){
         int nbytes = client.send (bufp);
         bufp += nbytes;
         bufbytes -= nbytes;
      }
   }
}

int main (int argc, char** argv) {
   execname = basename (argv[0]);
   vector<string> args (&argv[1], &argv[argc]);
   try {
      switch (args.size()) {
         case 1: date_server (args); break;
         case 2: date_client (args); break;
         default: usage(); break;
      }
   }catch (socket_error& error) {
      cerr << execname << ": " << error.what() << endl;
   }catch (domain_error& error) {
      cerr << execname << ": " << error.what() << endl;
   }
   return exit_status;
}

// This is not the correct way do #include.  We should have
// a Makefile to do this, but mkc and mkt assume standalone
// programs.  But it's easier to have a standalone example
// for such a simple program.
#include "../simple-sockets/sockets.cpp"

//TEST// mkpspdf dateserver.ps dateserver.cpp* dateserver.output

