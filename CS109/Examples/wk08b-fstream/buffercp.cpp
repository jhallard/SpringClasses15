// $Id: buffercp.cpp,v 1.5 2014-06-02 16:10:33-07 - - $

//
// Queue of buffers and file I/O.
//

#include <array>
#include <cassert>
#include <cstring>
#include <fstream>
#include <iostream>
#include <memory>
#include <queue>
using namespace std;

string execname;
int exit_status {EXIT_SUCCESS};

struct exec_error: public runtime_error {
   exec_error (const string& message): runtime_error (message) {
      assert (execname.size() > 0);
   }
};

struct sys_errno: public exec_error {
   sys_errno (const string& obj):
              exec_error (execname + ": " + obj + ": "
                          + strerror (errno)){}
};

void usage () {
   throw exec_error ("Usage: " + execname + " infile outfile");
}


struct buffer {
   static constexpr size_t MAX_BYTES = 0x100;
   size_t nbytes {};
   array<char,MAX_BYTES>  bytes;
};
using buffer_uptr = unique_ptr<buffer>;
using buffer_queue = queue<buffer_uptr>;

buffer_queue readfile (const string& filename) {
   buffer_queue que;
   ifstream infile {filename};
   if (infile.fail()) throw sys_errno (filename);
   while (not infile.eof()) {
      buffer_uptr uptr {new buffer()};
      infile.read (uptr->bytes.data(), uptr->MAX_BYTES);
      uptr->nbytes = infile.gcount();
      que.push (std::move (uptr));
   }
   return std::move (que);
}

void writefile (const string& filename, buffer_queue& que) {
   ofstream outfile {filename};
   if (outfile.fail()) throw sys_errno (filename);
   while (not que.empty()) {
      buffer_uptr uptr = std::move (que.front());
      que.pop();
      outfile.write (uptr->bytes.data(), uptr->nbytes);
   }
}

int main (int argc, char** argv) {
   execname = basename (argv[0]);
   try {
      if (argc != 3) usage();
      buffer_queue que = readfile (argv[1]);
      writefile (argv[2], que);
   }catch (exec_error& error) {
      cerr << error.what() << endl;;
      exit_status = EXIT_FAILURE;
   }
   return exit_status;
}
