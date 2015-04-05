.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-109 Winter\~2015 Program\~1 "Function pointers, a shell"
.RCS "$Id: asg1-shell-fnptrs.mm,v 1.64 2015-03-25 19:10:29-07 - - $"
.PWD
.URL
.ds dots \|.\|.\|.
.nr bash_count 0 1
.de UNIX_COMMAND
.   nop bash-\\n+[bash_count]\[Do] \f[CB]\\$*\f[P]
.   pso \\$*
..
.hw un-a-vail-a-ble
.EQ
delim $$
.EN
.H 1 "Overview"
Your first \[C++] program will familiarize you with the basics of
the language,
as well as the standard library, 
which contains many classes which make data structures problems
very easy.
You will maintain a tree structure with a simple hierarchy,
maintained by a map of functions.
Programming will be done \[C++] style, not C style,
as shown in the following table.
.DS
.TS
center tab(|); |le |le |.
_
Do not use\(::|Instead, use\(::
_
\f[CB]char*\fP strings|\f[CB]<string>\fP
C arrays|\f[CB]<vector>\fP
\f[CB]<stdio.h>\fP|\f[CB]<iostream>\fP
pointers|\f[CB]<shared_ptr>\fP
\f[CB]union\fP|inheritance
\f[CB]<\fP\fIheader\fP\f[CB].h>\fP|\f[CB]<c\fP\fIheader\fP\f[CB]>\fP
_
.TE
.DE
Header files\(::
Include only C++11 header files and facilities where feasable,
and
.V= "use namespace std" .
Include 
.VI <c header >
files only when C++-style files are unavailable.
Include
.VI < header \&.h>
files from C only when an appropriate
.VI <c header >
files is unavailable.
.H 1 "Program Specification"
The program specification is given in terms of a Unix 
.V= man (1)
page.
.SH=BVL
.B=LI "NAME"
yshell
\[em]
in memory simulated tree shell
.B=LI "SYNOPSIS"
.V= yshell
.=V \|[ -@
.IR flags ]
.B=LI "DESCRIPTION"
This shell reads commands from stdin and write output to stdout,
with errors being set to stderr.
Each line read by the shell is parsed into words by splitting
using space characters, 
with any number of spaces between words.
There may also be leading and trailing spaces.
The first word on any line is a command to be simulated,
and the rest are operands to that command.
If either stdin or stdout is not a tty,
each line from stdin is echoed to stdout.
.P
The commands modify an inode tree,
where each inode is either a file or a directory.
Files contain data and directories contain inodes.
An inode is specified by means of a pathname.
A pathname consists of a sequence of characters separated by
slash
.=V ( / )
characters.
.P
The inode tree has a root, which is a special node,
and also a current inode as well.
Whenever a pathname is decoded,
if the first character is a slash
.=V ( / ),
decoding begins at the root,
otherwise it begins with the current directory.
Whenever a pathname component is a dot
.=V ( . ),
it refers to the current directory.
If a component is a double dot
.=V ( .. )
it refers to the parent of the current directory.
Every directory has both of these entries,
with the root being its own parent.
Multiple adjacent slashes are treated as a single slash.
Trailing slashes are permitted only on directories.
.P
Every inode has three attributes\(::
an inode number, which is uniquely assigned,
starting from 1 for the root\(;;
contents, which is a map from filenames to inodes for a directory,
and text for a file\(;;
and a size, which is the byte count for text,
and the number of sub-inodes for a directory.
.B=LI "OPERANDS"
None.
All input comes from stdin.
.B=LI "OPTIONS"
The
.V= -@
option is followed by a sequence of flags to enable debug output,
written to stderr.
.B=LI "COMMANDS"
The following commands are interpreted.
Error messages are printed and nothing is done in the case
of invalid operands.
.BVL \n[Pi]
.LI "\f[CB]#\f[R] \|\f[I]string\f[R]"
If the first non-space character on a line is a hash,
the line is a comment and is ignored.
.LI "\f[CB]cat\f[R] \|\f[I]pathname\*[dots]\f[R]"
The contents of each file is copied to stdout.
An error is reported if no files are specified,
a file does not exist,
or is a directory.
.LI "\f[CB]cd\f[R] \|[\f[I]pathname\f[R]]"
The current directory is set the the pathname given.
If no pathname is specified, the root directory
.=V ( / )
is used.
It is an error if the pathname does not exist or is a plain file,
or if more than one operand is given.
.LI "\f[CB]echo\f[R] \|[\f[I]words\*[dots]\f[R]]"
The string, which may be empty, is echoed to stdout on a line by
itself.
.LI "\f[CB]exit\f[R] \|[\f[I]status\f[R]]"
Exit the program with the given status.
If the status is missing, exit with status 0.
If a non-numeric argument is given, exit with status 127.
.LI "\f[CB]ls\f[R] \|[\f[I]pathname\*[dots]\f[R]]"
A description of the files or directories are printed to stdout.
It is an error if any of the file or directory does not exist.
If no pathname is specified, the current working directory is used.
If a pathname specified is a directory,
then the contents of the directory are listed.
A directory listed within a directory is shown by a terminating slash.
Elements of a directory are listed lexicographically.
.P
For each file listed,
output consists of
the inode number, then the size, then the filename.
Output is lined up into columns and each column is separated
from the next by two spaces.
The numeric fields are exactly 6 characters wide and the units
position in a column must be aligned.
.LI "\f[CB]lsr\f[R] \|[\f[I]pathname\*[dots]\f[R]]"
As for \f[CB]ls\f[R],
but a recursive depth-first preorder traversal
is done for subdirectories.
.LI "\f[CB]make\f[R] \|\f[I]pathname\f[R] \|[\f[I]words\*[dots]\f[R]]"
The file specified is created and the rest of the words are put
in that file.
If the file already exists,
a new one is not created, but its contents are replaced.
It is an error to specify a directory.
If there are no words, the file is empty.
.LI "\f[CB]mkdir\f[R] \|\f[I]pathname\f[R]"
A new directory is created.
It is an error if a file or directory of the same name already exists,
or if the complete pathname to the parent of this new directory
does not already exist.
Two entries are added to the directory, namely dot
.=V ( . )
and dotdot
.=V ( .. ).
Directory entries are always kept in sorted lexicographic order.
.LI "\f[CB]prompt\f[R] \|\f[I]string\f[R]"
Set the prompt to the words specified on the command line.
Each word is separated from the next by one space and the prompt
itself is terminated by an extra space.
The default prompt is a single percent sign and a space
.=V ( %\[VS] ).
.LI "\f[CB]pwd\f[R]"
Prints the current working directory.
.LI "\f[CB]rm\f[R] \|\f[I]pathname\f[R]"
The specified file or directory is deleted
(removed from its parent's list of files and subdirectories).
It is an error for the pathname not to exist.
If the pathname is a directory, it must be empty.
.LI "\f[CB]rmr\f[R] \|\f[I]pathname\f[R]"
A recursive removal is done, 
using a depth-first postorder traversal.
.LE
.B=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
Error messages were printed to
.V= cerr .
.LE
.H 1 "A Sample Run"
The following table shows a sample run.
Each interaction with the shell is listed in a separate box
with shell output in
.T= "Courier Roman"
and user input in
.V= "Courier Bold"
typeface.
A commentary about what is happening is opposite in the right column.
.TS H
allbox tab(|); lw(219p)fCR lw(219p).
.TH
T{
.nf
.=V "% " "pwd"
/
T}|T{
Initially the cwd is the root directory.
T}
T{
.nf
.=V "% " "ls"
/:
     1       2  .
     1       2  ..
T}|T{
The absence of an operand to 
.V= ls
means that dot is used as its operand,
which is currently the root.
Directories always contain at least two items,
namely dot and dotdot.
The inode number of the root is always inode #1.
The parent of dotdot is itself.
T}
T{
.nf
.=V "% " "make foo this is a test"
T}|T{
Make a file called
.V= foo
which contains the string
.=V `` "this is a test" '',
which is 14 characters.
An inode is allocated, namely inode #2.
T}
T{
.nf
.=V "% " "make bar test a is this"
T}|T{
Another file, similarly created, with inode #3.
T}
T{
.nf
.=V "% " "ls"
/:
     1       4  .
     1       4  ..
     3      14  bar
     2      14  foo
T}|T{
Same as the previous output of
.V= ls ,
except with two more files.
Note that files are kept in lexicographic order, so
.V= bar
is listed before
.V= foo .
T}
T{
.nf
.=V "% " "cat food"
cat: food: No such file or directory
T}|T{
An error message is printed, 
causing the return code from the shell eventually to be 1 rather
than 0.
Note the error format\(::
command followed by object causing the problem followed by
the reason for the failure.
T}
T{
.nf
.=V "% " "cat foo"
this is a test
T}|T{
Files can consist of only one line, 
namely a string.
T}
T{
.nf
.=V "% " "echo O for a muse of fire"
O for a muse of fire
T}|T{
Arguments to
.V= echo
are simply written to the standard output.
T}
T{
.nf
.=V "% " "prompt =>"
T}|T{
The prompt is changed to the characters
.=V `` => ''
followed by a space.
Multiple words would have been permitted.
T}
T{
.nf
.=V "=> " "rm bar"
T}|T{
The file
.V= bar
is deleted and the size of the root directory is reduced by 1.
T}
T{
.nf
.=V "=> " "make baz foo bar baz"
T}|T{
A new file is created with inode #4.
T}
T{
.nf
.=V "=> " "mkdir test"
T}|T{
Inode #5 is created as a directory called 
.V= test .
This directory is a child of the root and contains the
two usual entries, dot and dotdot.
T}
T{
.nf
.=V "=> " "prompt %"
T}|T{
The prompt is changed back to a
.V= %
followed by a space.
T}
T{
.nf
.=V "% " "ls /"
/:
     1       5  .
     1       5  ..
     4      11  baz
     2      14  foo
     5       2  test/
T}|T{
Just checking the contents of the root.
T}
T{
.nf
.=V "% " "cd test"
T}|T{
The cwd is now
.V= test .
T}
T{
.nf
.=V "% " "pwd"
/test
T}|T{
Yes, it is.
T}
T{
.nf
.=V "% " "cd"
T}|T{
Without arguments
.V= cd
goes back to the root directory.
T}
T{
.nf
.=V "% " "pwd"
/
T}|T{
OK.
T}
T{
.nf
.=V "% " "cd test"
T}|T{
Go to a directory called
.V= test
which is a subdirectory of the cwd, whose alias name is always dot.
T}
T{
.nf
.=V "% " "pwd"
/test
T}|T{
T}
T{
.nf
.=V "% " "cd .."
T}|T{
Dotdot is always an alias for the parent of the cwd.
T}
T{
.nf
.=V "% " "pwd"
/
T}|T{
T}
T{
.nf
.=V "% " "cd test"
.=V "% " "make me me me me"
T}|T{
This would have errored out if 
.V= test
were not a directory or did not exist.
The next available inode is #6.
T}
T{
.nf
.=V "% " "cat me"
me me me
T}|T{
T}
T{
.nf
.=V "% " "cd .."
.=V "% " "cd test"
T}|T{
T}
T{
.nf
.=V "% " "cat me"
me me me
T}|T{
T}
T{
.nf
.=V "% " "cd"
T}|T{
T}
T{
.nf
.=V "% " "lsr /"
/:
     1       5  .
     1       5  ..
     4      11  baz
     2      14  foo
     5       3  test/
/test:
     5       3  .
     1       5  ..
     6       8  me
T}|T{
Recursive directory listing.
This is done using a preorder traversal.
Withing a given level, lexicographic ordering is used.
Recursion will go through all subdirectories at all levels.
T}
T{
.nf
.=V "% " "cd test"
T}|T{
T}
T{
.nf
.=V "% " "mkdir foo"
.=V "% " "cd foo"
.=V "% " "mkdir bar"
.=V "% " "cd bar"
.=V "% " "mkdir baz"
.=V "% " "cd baz"
T}|T{
Note that
.V= foo
uses inode #7,
.V= bar
uses inode #8, and
.V= baz
uses inode #9.
T}
T{
.nf
.=V "% " "ls ."
\&.:
     9       2  .
     8       3  ..
T}|T{
At this point dot is
.V= baz
and dotdot is
.V= bar .
T}
T{
.nf
.=V "% " "cd /"
.=V "% " "lsr test"
/test:
     5       4  .
     1       5  ..
     7       3  foo/
     6       8  me
/test/foo:
     7       3  .
     5       4  ..
     8       3  bar/
/test/foo/bar:
     8       3  .
     7       3  ..
     9       2  baz/
/test/foo/bar/baz:
     9       2  .
     8       3  ..
T}|T{
A rather large test showing inode numbers,
file and directory sizes, and filenames.
Note that directory names are indicated in the listing with
a trailing slash.
Again, the size of a file is the number of characters in it
and the size of a directory is the sum of the number of files
The subdirectory count is not recursive.
T}
T{
.nf
.=V "% " "\[ha]D"
T}|T{
End of file or Control/D causes the shell to exit.
T}
.TE
.H 1 "A Tour of the Code"
Begin by studying the code provided in the
.V= code/
subdirectory.
There are four modules arranged into a header
.=V ( \&.h )
file and an implementation
.=V ( \&.cpp )
file, the main program in
.V= main.cpp ,
and, of course, a 
.V= Makefile .
Notice that comments are in the header for when specifying general
functionality,
and only in the implementation as a way of explaining how something
works.
.nr file-Pi \n[Pi]*4
.VL \n[file-Pi]
.V=LI Makefile
Study the various targets
.V= all ,
.V= \[Do]{EXECBIN} ,
.V= %.o ,
.V= ci ,
.V= lis ,
.V= clean ,
.V= spotless ,
.V= submit ,
.V= verify ,
and
.V= deps ,
which perform their usual functions.
.V=LI debug.{h,cpp}
The
.V= debug
module is already written for you.
It is useful in tracing through your code.
Other parts of the code may want to have more 
.V= DEBUGF
and
.V= DEBUGS
calls added.
Note that you should also use
.V= gdb
to track down bugs.
Use
.V= valgrind
to check for invalid memory references and memory leak.
.V=LI util.{h,cpp}
The
.V= util
module is just a collection of independent functions which are
herded together.
It is a module without any cohesion,
but a useful place to park various random functions.
.V=LI main.cpp
The main program is mostly complete.
It scans options, then loops reading and executing commands.
.V=LI commands.{h,cpp}
Note that the functions are provided but do not do more than print
a trace.
Each function as a 
.V= inode_state 
argument, passed by reference, which it might update,
and a
.V= wordvec
arlgument.
.V= words[0]
is the name of the command itself,
so the first argument is
.V= words[1] .
This will take the most work, but commands can be added one at a time,
by addition to the organization that is already there.
You may add private functions is you need to.
This is the major execution engine.
.V=LI inode.{h,cpp}
The 
.V= inode ,
or file system, module is the main data structure that you are working
on.
As you implement commands,
also implement the functions of this module as well.
.H 1 "What to Submit"
Submit the files
.V= Makefile ,
.V= README ,
and all C++ header and source files.
All header files must end with
.V= \&.h ,
and source files must end with either
.V= \&.cpp
or
.V= \&.cc 
as the suffix.
You must be consistent and
use one or the other suffix for all files.
.P
Run
.V= gmake
to verify that the build is possible.
And when you run
.V= submit ,
do so from the 
.V= Makefile
target of that name.
That way you won't forget to submit a file.
If you forget to submit a file,
or submit the wrong version,
you will lose at least 50% of your program's value.
Make sure that you do not get any warnings from
.V= g++
and that
.V= checksource
does not complain about anything.
Do not submit any file that is built by the
.V= Makefile .
.P
If you are doing pair programming,
follow the additional instructions in\(::
.VTCODE* 1 \
/afs/cats.ucsc.edu/courses/cmps012b-wm/Syllabus/pair-programming/ 
.P
The code must compile and run using
.V= g++
on
.V= unix.ucsc.edu ,
regardless of whether it runs elsewhere.
As of the time of formatting this document,
that was\(::
.DS
.in +\n[VCODENWIDTH]u
.ft CR
.UNIX_COMMAND "g++ --version | head -1"
.UNIX_COMMAND "uname -srp"
.UNIX_COMMAND "hostname"
.DE
For a summary of C++11 support in GCC, refer to\(::
.VTCODE* 1 http://gcc.gnu.org/projects/cxx0x.html
.FINISH
