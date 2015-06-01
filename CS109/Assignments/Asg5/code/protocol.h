// $Id: protocol.h,v 1.2 2015-05-12 18:59:40-07 - - $

#ifndef __PROTOCOL__H__
#define __PROTOCOL__H__

#include <cstdint>
#include <cstring>
#include <iostream>
using namespace std;

#include "sockets.h"

enum cix_command {CIX_ERROR = 0, CIX_EXIT,
                  CIX_GET, CIX_HELP, CIX_LS, CIX_PUT, CIX_RM,
                  CIX_FILE, CIX_LSOUT, CIX_ACK, CIX_NAK};

size_t constexpr FILENAME_SIZE = 59;
struct cix_header {
   uint32_t nbytes {0};
   uint8_t command {0};
   char filename[FILENAME_SIZE] {};
};

void send_packet (base_socket& socket,
                  const void* buffer, size_t bufsize);

void recv_packet (base_socket& socket, void* buffer, size_t bufsize);

ostream& operator<< (ostream& out, const cix_header& header);

string get_cix_server_host (const vector<string>& args, size_t index);

in_port_t get_cix_server_port (const vector<string>& args,
                               size_t index);

#endif

