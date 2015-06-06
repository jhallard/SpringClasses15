// $Id: cix.cpp,v 1.2 2015-05-12 18:59:40-07 - - $

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include <libgen.h>
#include <sys/types.h>
#include <unistd.h>

#include "protocol.h"
#include "logstream.h"
#include "sockets.h"
#include "util.h"

logstream log (cout);
struct cix_exit: public exception {};

unordered_map<string,cix_command> command_map {
   {"exit", CIX_EXIT},
   {"help", CIX_HELP},
   {"ls"  , CIX_LS  },
   {"put" , CIX_PUT  },
   {"rm"  , CIX_RM  },
   {"get" , CIX_GET },
};


void cix_help() {
   static vector<string> help = {
      "exit         - Exit the program.  Equivalent to EOF.",
      "get filename - Copy remote file to local host.",
      "help         - Print help summary.",
      "ls           - List names of files on remote server.",
      "put filename - Copy local file to remote host.",
      "rm filename  - Remove file from remote server.",
   };
   for (const auto& line: help) cout << line << endl;
}

void cix_ls (client_socket& server) {
   cix_header header;
   header.command = CIX_LS;
   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != CIX_LSOUT) {
      log << "sent CIX_LS, server did not return CIX_LSOUT" << endl;
      log << "server returned " << header << endl;
   }else {
      char buffer[header.nbytes + 1];
      recv_packet (server, buffer, header.nbytes);
      log << "received " << header.nbytes << " bytes" << endl;
      buffer[header.nbytes] = '\0';
      cout << buffer;
   }
}

void cix_rm(client_socket& server, const string & fn) {
   // TODO: send filename to server, get ack and conf. that
   // file has been deleted.
   cix_header header;
   header.command = CIX_RM;
   if(fn.size() > 59) {
      log << "Error : filename longer than 59 bytes" << endl;
   }
   for(int i = 0; i < fn.size(); i++) {
      header.filename[i] = fn[i];
   } 
   header.filename[59] = '\0';

   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);
   
   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;
   if (header.command != CIX_ACK) {
      log << "send CIX_RM, did not receive CIX_ACK" << endl;
      log << "server returned " << header << endl;
   }else {
      log << "file " << fn << " : deleted from server" << endl;
   }
}

void cix_get(client_socket& server, const string & fn) {
   // TODO: send filename to server, get ack and conf. that
   // file has been deleted.
   cix_header header;
   string data = "";

   header.command = CIX_GET;
   header.nbytes = 0;
   if(fn.size() > 59) {
      log << "Error : filename longer than 59 bytes" << endl;
   }
   for(int i = 0; i < fn.size(); i++) {
      header.filename[i] = fn[i];
   } 
   header.filename[59] = '\0';

   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);

   recv_packet (server, &header, sizeof header);

   if(header.command != CIX_FILE) {
      log << "error : invalid response from server" << endl;
      log << "file possible does not exist" << endl;
      return;
   }

   char buffer[header.nbytes+1];

   recv_packet (server, buffer, header.nbytes);

   if(write_file(fn, buffer)) {
      log << "file : " << fn << " : received from server" << endl;
   }
   else {
      log << "file : " << fn << " : failed to receive" << endl;
   }
}

void cix_put(client_socket& server, const string & fn) {
   // TODO: send file to server
   cix_header header;
   string data = "";

   header.command = CIX_PUT;

   if(fn.size() > 59) {
      log << "Error : filename longer than 59 bytes" << endl;
   }
   for(int i = 0; i < fn.size(); i++) {
      header.filename[i] = fn[i];
   } 
   header.filename[59] = '\0';

   try {
      data = read_file(fn);
   } catch(exception & e) {
      log << e.what() << endl;
      return;
   }

   // data.push_back('\0');
   header.nbytes = data.size();

   log << "sending header " << header << endl;
   send_packet (server, &header, sizeof header);

   log << "sending contents of : " << fn << endl;
   send_packet (server, data.c_str(), data.size());

   recv_packet (server, &header, sizeof header);
   log << "received header " << header << endl;

   if(header.command == CIX_ACK) {
      log << fn << " successfully transferred" << endl;
   }
   else {
      log << fn << " failed to transfer" << endl;
   }
}


void usage() {
   cerr << "Usage: " << log.execname() << " [host] [port]" << endl;
   throw cix_exit();
}

int main (int argc, char** argv) {
   log.execname (basename (argv[0]));
   log << "starting" << endl;
   vector<string> args (&argv[1], &argv[argc]);
   if (args.size() > 2) usage();
   string host = get_cix_server_host (args, 0);
   in_port_t port = get_cix_server_port (args, 1);
   log << to_string (hostinfo()) << endl;
   try {
      log << "connecting to " << host << " port " << port << endl;
      client_socket server (host, port);
      log << "connected to " << to_string (server) << endl;
      for (;;) {
         string line;
         getline (cin, line);
         if (cin.eof()) throw cix_exit();
         log << "command " << line << endl;

         vector<string> words = split (line, " \t");
         const auto& itor = command_map.find (words[0]);
         cix_command cmd = itor == command_map.end()
                         ? CIX_ERROR : itor->second;
         switch (cmd) {
            case CIX_EXIT:
               throw cix_exit();
               break;
            case CIX_HELP:
               cix_help();
               break;
            case CIX_LS:
               cix_ls (server);
               break;
            case CIX_PUT:
               log << line << " : command detected" << endl;
               // ensure fn argument is given
               if(words.size() < 2) {
                  log << "error : put : " << 
                  "requires filename argument" << endl;
               }
               cix_put (server, words[1]);
               break;
            case CIX_GET:
               log << line << " : command detected" << endl;
               // ensure fn argument is given
               if(words.size() < 2) {
                  log << "error : get : " << 
                  "requires filename argument" << endl;
               }
               cix_get (server, words[1]);
               break;
            case CIX_RM:
               log << line << " : command detected" << endl;
               // ensure fn argument is given
               if(words.size() < 2) {
                  log << "error : rm : " << 
                  "requires filename argument" << endl;
               }
               cix_rm (server, words[1]);
               break;
            default:
               log << line << ": invalid command" << endl;
               break;
         }
      }
   }catch (socket_error& error) {
      log << error.what() << endl;
   }catch (cix_exit& error) {
      log << "caught cix_exit" << endl;
   }
   log << "finishing" << endl;
   return 0;
}

