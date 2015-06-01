// $Id: addrinfo.cpp,v 1.12 2014-05-22 14:35:13-07 - - $

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

string socktype (int socktype) {
   static unordered_map<int,string> socktype_map {
      {SOCK_DGRAM , "dgram" },
      {SOCK_RAW   , "raw"   },
      {SOCK_STREAM, "stream"},
   };
   const auto& result = socktype_map.find (socktype);
   return result == socktype_map.end() ? "(\?\?\?\?)" : result->second;
}

string af_family (int family) {
   static unordered_map<int,string> family_map {
      {AF_FILE  , "File"  },
      {AF_INET  , "IPv4"  },
      {AF_INET6 , "IPv6"  },
      {AF_UNIX  , "Unix"  },
      {AF_UNSPEC, "Unspec"},
   };
   const auto& result = family_map.find (family);
   return result == family_map.end() ? "(\?\?\?\?)" : result->second;
}

string inet_address (addrinfo* info) {
   sockaddr* addr = nullptr;
   switch (info->ai_family) {
      case AF_INET:
         addr = (sockaddr*) &((sockaddr_in*) info->ai_addr)->sin_addr;
         break;
      case AF_INET6:
         addr = (sockaddr*) &((sockaddr_in6*) info->ai_addr)->sin6_addr;
         break;
   }
   char textstr[INET6_ADDRSTRLEN];
   const char* text = inet_ntop (info->ai_family, addr,
                                 textstr, sizeof textstr);
   if (text == nullptr) text = strerror (errno);
   return textstr;
}


void print_addrinfo (const string& hostname) {
   addrinfo hints;
   memset (&hints, 0, sizeof hints);
   hints.ai_flags = AI_CANONNAME;
   hints.ai_family = AF_UNSPEC;
   addrinfo* results;
   cout << "IP addresses for " << hostname << ":" << endl;
   int rc = getaddrinfo (hostname.c_str(), NULL, &hints, &results);
   if (rc != 0) {
      cout << "   " << gai_strerror (rc) << endl;
      return;
   }
   for (auto info = results; info != nullptr; info = info->ai_next) {
      cout << "   " << setw(6) << socktype (info->ai_socktype)
           << " " << setw(6) << af_family (info->ai_family)
           << " " << inet_address (info);
      if (info->ai_canonname) cout << " " << info->ai_canonname;
      cout << endl;
   }
   freeaddrinfo (results);
}

int main (int argc, char** argv) {
   string progname (argv[0]);
   vector<string> args (&argv[1], &argv[argc]);
   for (const auto& hostname: args) {
      print_addrinfo (hostname);
   }
   return 0;
}

/*
//TEST// addrinfo www.google.com www.nohost.zone www.soe.ucsc.edu \
//TEST//          unix.ucsc.edu unix1.lt.ucsc.edu unix2.lt.ucsc.edu \
//TEST//          localhost >addrinfo.output 2>&1
//TEST// mkpspdf addrinfo.ps addrinfo.cpp* addrinfo.output
*/

