//$Id: server.cpp,v 1.9 2014-05-23 13:25:17-07 - - $

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>

#include "logstream.h"
#include "sockets.h"

int main (int argc, char** argv) {
   logstream clog (cout, basename (argv[0]));
   vector<string> args (&argv[1], &argv[argc]);
   in_port_t port = args.size() < 1 ? 50000 : stoi (args[0]);
   try {
      if (port <= IPPORT_USERRESERVED) {
         throw socket_error ("unprivileged server port ("
               + to_string (port) + ") <= IPPORT_USERRESERVED ("
               + to_string (IPPORT_USERRESERVED) + ")");
      }
      // Create the socket
      server_socket listener (port);
      for (;;) {
         clog << to_string (hostinfo())
              << " accepting port " << to_string (port) << endl;
         accepted_socket client_sock;
         listener.accept (client_sock);
         clog << "accepted " << to_string (client_sock) << endl;
         try {
            for (;;) {
               string data;
               ssize_t nbytes = client_sock.recv (data);
               if (nbytes == 0) break;
               clog << "received \"" << data << "\"" << endl;
               client_sock.send (data);
            }
         }catch (socket_error& error) {
            clog << error.what() << endl;
         }
         clog << "client is gone" << endl;
      }
   }catch (socket_error& error) {
      clog << error.what() << endl;
   }
   return 0;
}
