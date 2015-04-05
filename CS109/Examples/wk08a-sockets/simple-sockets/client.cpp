// $Id: client.cpp,v 1.6 2014-05-23 13:25:17-07 - - $

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "logstream.h"
#include "sockets.h"

string progname;

int main (int argc, char** argv) {
   logstream clog (cout, basename (argv[0]));
   vector<string> args (&argv[1], &argv[argc]);
   string host = args.size() < 1 ? "localhost" : args[0];
   in_port_t port = args.size() < 2 ? 50000 : stoi (args[1]);
   clog << to_string (hostinfo()) << endl;
   try {
      clog << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      clog << "connected to " << to_string (server) << endl;
      for (int count = 0; count < 4; ++count) {
         string reply;
         try {
            ostringstream message;
            message << "Message " << count << " from client "
                    << getpid();
            clog << "to server: \"" << message.str() << "\"" << endl;
            server.send (message.str());
            server.recv (reply);
         }catch (socket_error& error) {
            clog << error.what() << endl;
         }
         clog << "from server: \"" << reply << "\"" << endl;
      }
   }catch (socket_error& error) {
      clog << error.what() << endl;
   }
   return 0;
}
