// $Id: showhost.cpp,v 1.4 2014-05-20 19:51:15-07 - - $

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

int main (int argc, char** argv) {
   string progname (argv[0]);
   vector<string> args (&argv[1], &argv[argc]);

   for (const string& hostname: args) {
      if (args.size() > 1) cout << endl;
      hostent* host = gethostbyname (hostname.c_str());
      if (host == nullptr) {
         cout << hostname << ": " << hstrerror (h_errno) << endl;
      }else {
         cout << "Hostname:  " << hostname << endl;
         cout << "h_name:    " << host->h_name << endl;
         for (char** alias = host->h_aliases; *alias; ++alias) {
            cout << "h_alias:   " << *alias << endl;
         }
         for (in_addr** addr_list = (in_addr**) host->h_addr_list;
              *addr_list; ++addr_list) {
            cout << "h_addr:    " << inet_ntoa (**addr_list) << endl;
         }
      }
   }

   return 0;
}

/*
//TEST// showhost www.soe.ucsc.edu soe.ucsc.edu \
//TEST//          www.ucsc.edu unix.ucsc.edu \
//TEST//          unix1.lt.ucsc.edu unix2.lt.ucsc.edu \
//TEST//          www.google.com www.nohost.zone >showhost.output
//TEST// mkpspdf showhost.ps showhost.cpp* showhost.output
*/

