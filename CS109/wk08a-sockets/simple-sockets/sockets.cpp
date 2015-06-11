// $Id: sockets.cpp,v 1.1 2014-05-23 13:25:17-07 - - $

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
using namespace std;

#include <fcntl.h>
#include <limits.h>

#include "sockets.h"

base_socket::base_socket() {
   memset (&socket_addr, 0, sizeof (socket_addr));
}

base_socket::~base_socket() {
   if (socket_fd != CLOSED_FD) close();
}

void base_socket::close() {
   int status = ::close (socket_fd);
   if (status < 0) throw socket_sys_error ("close");
   socket_fd = CLOSED_FD;
}

void base_socket::create() {
   socket_fd = ::socket (AF_INET, SOCK_STREAM, 0);
   if (socket_fd < 0) throw socket_sys_error ("socket");
   int on = 1;
   int status = ::setsockopt (socket_fd, SOL_SOCKET, SO_REUSEADDR,
                            &on, sizeof on);
   if (status < 0) throw socket_sys_error ("setsockopt");
}

void base_socket::bind (const in_port_t port) {
   socket_addr.sin_family = AF_INET;
   socket_addr.sin_addr.s_addr = INADDR_ANY;
   socket_addr.sin_port = htons (port);
   int status = ::bind (socket_fd, (sockaddr*) &socket_addr,
                        sizeof socket_addr);
   if (status < 0) throw socket_sys_error ("bind");
}

void base_socket::listen() const {
   int status = ::listen (socket_fd, SOMAXCONN);
   if (status < 0) throw socket_sys_error ("listen");
}


void base_socket::accept (base_socket& new_socket) const {
   int addr_length = sizeof new_socket.socket_addr;
   new_socket.socket_fd = ::accept (socket_fd,
                            (sockaddr*) &new_socket.socket_addr,
                            (socklen_t*) &addr_length);
   if (new_socket.socket_fd < 0) throw socket_sys_error ("accept");
}

ssize_t base_socket::send (const string& message) {
   int nbytes = ::send (socket_fd, message.c_str(), message.size(),
                        MSG_NOSIGNAL);
   if (nbytes < 0) throw socket_sys_error ("send");
   return nbytes;
}

ssize_t base_socket::recv (string& message) {
   char buffer [MAXRECV + 1];
   message = "";
   memset (buffer, 0, MAXRECV + 1);
   ssize_t nbytes = ::recv (socket_fd, buffer, MAXRECV, 0);
   if (nbytes < 0) throw socket_sys_error ("recv");
   if (nbytes > 0) message = buffer;
   return nbytes;
}

void base_socket::connect (const string host, const in_port_t port) {
   struct hostent *hostp = ::gethostbyname (host.c_str());
   if (hostp == NULL) throw socket_h_error ("gethostbyname("
                            + host + ")");
   socket_addr.sin_family = AF_INET;
   socket_addr.sin_port = htons (port);
   socket_addr.sin_addr = *(in_addr*) hostp->h_addr;
   int status = ::connect (socket_fd, (sockaddr*) &socket_addr,
                           sizeof (socket_addr));
   if (status < 0) throw socket_sys_error ("connect(" + host + ":"
                         + to_string (port) + ")");
}

void base_socket::set_non_blocking (const bool blocking) {
   int opts = ::fcntl (socket_fd, F_GETFL);
   if (opts < 0) throw socket_sys_error ("fcntl");
   if (blocking) opts |= O_NONBLOCK;
            else opts &= compl O_NONBLOCK;
   opts = ::fcntl (socket_fd, F_SETFL, opts);
   if (opts < 0) throw socket_sys_error ("fcntl");
}


client_socket::client_socket (string host, in_port_t port) {
   base_socket::create();
   base_socket::connect (host, port);
}

server_socket::server_socket (in_port_t port) {
   base_socket::create();
   base_socket::bind (port);
   base_socket::listen();
}

string to_string (const hostinfo& info) {
   return info.hostname + " (" + to_string (info.addresses[0]) + ")";
}

string to_string (const in_addr& ipv4_addr) { 
   char buffer[INET_ADDRSTRLEN];
   const char *result = ::inet_ntop (AF_INET, &ipv4_addr,
                                     buffer, sizeof buffer);
   if (result == NULL) throw socket_sys_error ("inet_ntop");
   return result; 
}

string to_string (const base_socket& sock) {
   hostinfo info (sock.socket_addr.sin_addr);
   return info.hostname + " (" + to_string (info.addresses[0])
          + ") port " + to_string (ntohs (sock.socket_addr.sin_port));
}


string init_hostname (hostent* host) {
   if (host == nullptr) throw socket_h_error ("gethostbyname");
   return host->h_name;
}

vector<string> init_aliases (hostent* host) {
   if (host == nullptr) throw socket_h_error ("gethostbyname");
   vector<string> init_aliases;
   for (char** alias = host->h_aliases; *alias != nullptr; ++alias) {
      init_aliases.push_back (*alias);
   }
   return init_aliases;
}

vector<in_addr> init_addresses (hostent* host) {
   vector<in_addr> init_addresses;
   if (host == nullptr) throw socket_h_error ("gethostbyname");
   for (in_addr** addr = (in_addr**) host->h_addr_list;
        *addr != nullptr; ++addr) {
      init_addresses.push_back (**addr);
   }
   return init_addresses;
}

hostinfo::hostinfo (hostent* host):
   hostname (init_hostname (host)),
   aliases (init_aliases (host)),
   addresses (init_addresses (host)) {
}

hostinfo::hostinfo(): hostinfo (localhost()) {
}

hostinfo::hostinfo (const string& hostname):
          hostinfo (::gethostbyname (hostname.c_str())) {
}

hostinfo::hostinfo (const in_addr& ipv4_addr):
          hostinfo (::gethostbyaddr (&ipv4_addr, sizeof ipv4_addr,
                                     AF_INET)) {
}

string localhost() {
   char hostname[HOST_NAME_MAX];
   int rc = gethostname (hostname, sizeof hostname);
   if (rc < 0) throw socket_sys_error ("gethostname");
   return hostname;
}

