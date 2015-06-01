.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-109 Spring\~2015 Program\~5 "Client/Server and Sockets"
.RCS "$Id: asg5-client-server.mm,v 1.53 2015-05-12 17:25:01-07 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.hw ac-cu-mu-la-ted
.de COMMAND
.   LI "\f[CB]\\$[1]\0\f[I]\\$[2]\f[R]" \\$[3]
..  
.de MESSAGE
.   LI "\f[CB]\\$[1]\0\f[R]\\$[2]" \\$[3]
..
.H 1 "Overview"
This project will implement a client/server application using
sockets.
A daemon 
.=V ( cixd )
listens on a socket for client connection requests.
Each connection will cause the server to fork a child process 
to serve the client.
The daemon runs in an infinite loop listening.
The server exits when the client disconnects.
A client
.=V ( cix )
connects to a server and can send files, receive files,
and get a summary listing of all files present.
.P
A socket is a two-way means of communication between processes,
not necessarily running on the same host.
An IPv4 host is know by a 4-octet sequence such as
128.114.108.152,
and a port is an unsigned 16-bit number (0 to 65535).
Communication will be done via TCP/IP over IPv4 sockets.
.H 1 "Programs"
In this project,
two main programs are to be written
for the three parts of the project\(::
the daemon and server,
and the client.
There will also be several library files written to be used
by the programs.
The general function is similar to
.V= sftp (1).
.MANPAGE=BVL
.V=LI cixd
Usage\(::
\f[CB]cixd\f[P] \|[\f[I]port\f[P]]
.P
Creates a server socket and goes into an infinite loop\(::
When it accepts a client socket,
it uses
.V= fork (2)
to create a child process, 
which functions as the server to communicate with the client.
.P
The daemon listens for connections on the given port,
if specified.
If not,
the environment variable
.V= CIX_SERVER_PORT
is used to determine the port.
There is no default port.
.P
The server is forked
with an open socket communicating with the client.
Its loop repeatedly reads commands and information from the
client and acts on those commands,
returning information back to the client.
Its loop will be a receive followed by a send,
responding to client requests.
It exits when the client closes the socket.
It does no terminal I/O except possibly for debugging purposes.
.P
.V=LI cix
Usage\(::
\f[CB]cix\f[P] \|[\f[I]host\f[P]] \|[\f[I]port\f[P]]
.P
The client interacts with the user.
Commands are read from the terminal (or redirect),
each of which is executed one at a time by communicating
with the server.
Results are then displayed at the terminal.
.P
The client connects to the given host, if specified.
If not specified,
the environment variable
.V= CIX_SERVER_HOST
is used as the host to connect to.
If not specified,
.V= localhost
is used.
It tries to connect to the given port,
if specified.
If not,
the environment variable
.V= CIX_SERVER_PORT
is used to determine the port.
There is no default port.
.LE
.H 1 "Interactive Commands"
The 
.V= cix-client
responds to commands read from the standard output
and writes output to the standard output and error and accesses files.
In the syntax below,
.V= "Courier Bold"
are literal characters actually typed in, while
.IR "Roman Italic"
stands for appropriate substitutions.
.MANPAGE=BVL
.COMMAND exit
Quit the program.
An end of file marker or Control/D is equivalent.
.COMMAND get filename
Copy the file named
.IR filename
on the remote server and create or overwrite a file of the 
same name in the current directory.
.COMMAND help
A summary of available commands is printed.
.COMMAND ls
Causes the remote server to execute the command
.V= "ls -l"
and prints the output to the user's terminal.
.COMMAND put filename
Copies a local file into the socket and causes the remote server to
create that file in its directory.
.COMMAND rm filename
Causes the remote server to remove the file.
.LE
.H 1 "Protocol used by the \f[CB]cix*\f[P] programs"
In order for the client and server to communicate,
a protocol needs to be established.
This means that each message needs to be framed in terms of a header
and a payload.
The header always consists of a
.V= struct
of size 64 bytes.
All messages between client and server consist of these 64 bytes,
possibly followed by a payload.
For alignment purposes, the
.V= nbytes
field is first.
Before filling in the fields, use
.V= memset (3)
to clear the struct.
.DS
.in +\n[Pi]n
.ft CB
enum cix_command {CIX_ERROR = 0, CIX_EXIT,
                  CIX_GET, CIX_HELP, CIX_LS, CIX_PUT, CIX_RM,
                  CIX_FILE, CIX_LSOUT, CIX_ACK, CIX_NAK};
struct cix_header {
   uint32_t cix_nbytes;
   uint8_t cix_command;
   char cix_filename[59];
};
.DE
The purposes of the fields are as follows\(::
.MANPAGE=BVL
.V=LI "uint32_t cix_nbytes;"
The number of bytes in the payload if there is any payload.
Otherwise it must be zero (MBZ).
This field is sent in network byte order and so must use the
functions 
.V= ntohl (3)
and
.V= htonl (3)
when loading and storing data.
.V=LI "uint8_t cix_command;"
A single byte containing one of the
.V= cix_command
constants.
.V=LI "char cix_filename[59];"
The name of the file being transferred or removed.
The filename may not have any slash
.=V ( '/' )
characters in it and must be null-terminated (with
.V= '\[rs]0' ).
All bytes following the null must also be null.
Pathnames with slashes and filenames longer than 58 characters
are prohibited.
.LE
.P
Following are the meanings of each of the
.V= cix_command
values.
.ds CTS (C\[->]S)
.ds STC (S\[->]C)
Each is either client to server \*[CTS] or
server to client \*[STC], but never both.
.MANPAGE=BVL
.MESSAGE CIX_ERROR
An error flag to indicate an invalid header.
Used internally.
.MESSAGE CIX_EXIT
Internal to
.V= cix-client ,
not used in communication.
.MESSAGE CIX_GET \*[CTS]
Request a file from the server.
The filename is used both remotely and locally.
The payload length is 0.
.MESSAGE CIX_HELP
Internal to
.V= cix-client ,
not used in communication.
.MESSAGE CIX_LS \*[CTS]
Request file
.=V ( ls )
information.
The payload length and filename are zeroed.
.MESSAGE CIX_PUT \*[CTS]
The length of the payload is the number of bytes in the file.
The contents of the file immediately follow the header.
The bytes of the payload are unstructured and may contain null bytes.
Binary files are acceptable.
.MESSAGE CIX_RM \*[CTS]
Request to remove a file.
The payload length is 0.
.MESSAGE CIX_FILE \*[STC]
Response to a
.V= CIX_GET .
The filename is the same as in the request and the payload length
reflects the number of bytes in the file.
The payload consists of the bytes of the file.
.MESSAGE CIX_LSOUT \*[STC]
Response to a
.V= CIX_LS .
The filename is zeroed and the payload length is the number of bytes
sent in the payload.
The payload is the output of the command
.V= "ls -l" .
.MESSAGE CIX_ACK \*[STC]
Response to either a
.V= CIX_PUT
or a
.V= CIX_RM 
indicating that the request was successfully completed.
.MESSAGE CIX_NAK \*[STC]
Response to any request that fails.
There is no payload.
The filename field is the same as was in the original request.
The payload field is set to the value of
.V= errno
in the server's attempt to preform a task.
.LE
.H 1 "Procedures"
Each of the above commands requires procedures for accessing files,
including reading files from disk and writing files to disk,
as well as accessing directories.
When any of the system calls fails in the server,
the server immediately terminates the operation and sends
the value of
.V= errno
back to the client in a 
.V= CIX_NAK
message.
.ALX a ()
.LI
For the client or server to send a file it must first be read into
a buffer.
Binary files must be properly handled, 
so protocols which assume text files won't work.
To load a file from disk, use 
.V= istream::read() ,
collecting characters into a buffer.
Read the entire file into a buffer then close it.
After that,
it may be sent down the socket.
Alternatively,
.V= stat (2)
the file to see how large it is,
and send the file down the socket piecemeal.
.LI
When receiving a file from the socket,
Receive the header and determine the size of the file.
Create an
.V= ostream
and use
.V= ostream::write()
to write the parts of the file as they are received from the socket.
A C++ stream is closed
when the variable goes out of scope,
or you can call
.V= close .
.LI
To delete a file for the
.V= CIX_RM
command, use
.V= unlink (2)\(::
.VTCODE* 1 "rc = unlink (filename);"
.LI
To execute the
.V= CIX_LS
command use
.V= popen (2)
and
.V= pclose (2)
to create a pipe stream from the
.V= ls (1)
command
.VTCODE* 1 "FILE* pipe = popen (\[Dq]ls -l\[Dq], \[Dq]r\[Dq]);"
Then read the characters from the pipe in the easiest way,
probably by using 
.V= fgets (3).
Finally,
.V= "pclose(pipe)" .
Then send the output back the client in a 
.V= CIX_LSOUT
message.
.LE
.H 1 "Modules"
There will need to be several modules in this suite of programs.
Each of the programs, of course, will have its own source file
with a main function in it.
.P
The
.V= sockets
module will be a useful inclusion into the program
as its own module.
.P
There should also be a
.V= cix_protocol
module to implement the protocols and contain code for accessing
files and sockets,
since these will be used by both the client and the server.
.H 1 "Use of ports"
If your daemon listens on a port that has been bound by another
process, you will get the message ``Address already in use''
because only one process at any given time is allowed to listen
on a particular process.
To avoid this, choose a port number not being used by anyone
else on the same server.
.P
.ne 4
To avoid having to type in a port number every time you start
your server, 
put the following line in your
.V= \&.bashrc
or
.V= \&.bash_profile
file\(::
.VTCODE* 1 "export CIX_CLIENT_PORT 60000"
except that each person in class should use a different number.
You should pick a dynamic or private port number from the
range 49152 through 65535
(0xC000 through 0xFFFF).
.H 1 "Runaway Processes"
Be careful in using
.V= fork (2)
so that you don't accidentally create a fork-bomb.
The command
.V= pkill (1)
can be used to kill all processes matching a particular pattern.
So the command
.VTCODE* 1 "pkill cix"
will kill all of your processes whose executables contain the string
.=V `` cix ''.
A really quick way to log out is to use
.V= kill (1)\(::
.VTCODE* 1 "kill -9 -1"
.VTCODE* 1 "kill -s KILL -1"
will send
.V= SIGKILL
to all of your processes,
thus logging you out.
.H 1 "What to Submit"
Submit
.V= Makefile
which builds the three programs,
all necessary C++ header and implementation files.
And if doing pair programming, the
.V= PARTNER
file.
When the grader uses the command
.V= make
in the submit directory,
the three binaries should be built.
.FINISH
