.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Spring\~2014 Final\~Exam
.RCS "$Id: cmps109-2014q2-exam3.mm,v 1.47 2014-05-29 17:21:42-07 - - $"
.DS
.PS
examboxes(5)
.PE
.DE
.P
.ft BI
No books\(;;
No calculator\(;;
No computer\(;;
No email\(;;
No internet\(;;
No notes\(;;
No phone.
Neatness counts\(!!
Do your scratch work elsewhere and enter only your final
answer into the spaces provided.
.ft R
.EQ
delim $$
tdefine suchthat "{type relation |}"
.EN
.de LIQ
.   LI
..
.ALX 1
.LI
Write the template function
.V= find
which takes a key and a pair of
.E= forward
iterators and returns the
iterator which indicates the
first item in the container that is
.V= ==
to the key.
.SCORE-HERE 2
.DS
.ft CB
template <typename Keytype, typename Itertype>
Itertype find (Itertype begin, Itertype end, const Keytype& key) {
.DE
.SP 0.9i
.LI
Write the template function
.V= find
which takes a pair of
.E= forward
iterators and a predicate and which
returns the iterator indicating the first item in the container
for which the predicate is true.
Hint\(::
the predicate takes a
.V= const\~Keytype&
and returns a
.V= bool .
.SCORE-HERE 2
.DS
.ft CB
template <typename Keytype, typename Itertype>
Itertype find (Itertype begin, Itertype end, \
bool (*pred) (const Keytype& key) {
.DE
.SP 0.9i
.LI
Write the function
.V= circle
in OpenGL,
which draws a circle with the center at the coordinates $ ( x , y ) $
given to it.
The radius and color are also given.
.SCORE-HERE 3
.DS
.ft CB
void draw_circle (float xcenter, float ycenter, \
float radius, const GLubyte* color) {
   glBegin (GL_POLYGON);
.DE
.SP 1.2i
.LI
Assuming the
.V= sockets
library from project 5,
and assuming that a date server exists that sends a single
message back to the client then quits,
write a function
.V= date_client ,
which when called from
.V= main ,
will contact the server for the date and print it.
.SCORE-HERE 3
.DS
.ft CB
void date_client (string host, in_port_t port) {
.DE
.SP 10i
.LI
In the multiprecision project,
it was necessary to add two vectors of digits,
each digit being represented in a byte.
Write a function which takes to such vectors
(signs are ignored here, only absolute values are used)
and adds them together.
.SCORE-HERE 4
.DS
.ft CB
typedef unsigned char byte;
typedef vector<byte> unumber;
unumber absadd (const unumber& u1, const unumber& u2) {
.DE
.SP 2i
.LI
Define an object-oriented hierarchy as shown in the three
parts described here.
Show all code as it would appear in a header file so that no
implementation file is needed.
All classes have the virtual functions
.V= area
and
.V= circumference
as well as suitable constructors.
Make sure the constructors can not be used in implicit conversions.
.ALX a ()
.LI
Class
.V= shape
is the base class with abstract functions, and
a suitably protected constructor.
.SCORE-HERE 2
.SP 1.5i
.LI
Class
.V= circle \*F
has a single radius field which is initialized by the constructor.
.FS
For the mathematically challenged\(::
$ A = pi r sup 2 $ and $ C = 2 pi r $.
.br
And
.V= <cmath>
defines
.V= M_PI \(::
.V= "# define M_PI 3.14159265358979323846 /* pi */"
.FE
.SCORE-HERE 2
.SP 1.5i
.LI
Class
.V= square
has a single edge field (the length of one edge) initialized
by the constructor and also the two other functions.
.SCORE-HERE 2
.LE
.SP 10i
.LI
Referring to the question on the previous page,
write a function that will take a pair of iterators pointing into
a container, and print two numbers\(::
the sum of the areas
and the sum of the circumferences.
.SCORE-HERE 3
.DS
.ft CB
typedef vector<shared_ptr<shape>>::const_iterator vec_iterator;
void print_data (vec_iterator begin, vec_iterator end) {
.DE
.SP 2i
.LI
Define a template class
.V= queue
with a single typename parameter
.V= T .
Show only what should be in
.V= queue.h ,
not anything from
.V= queue.cpp ,
except for when an inline is explicitly requred.
.ALX i () "" 0
.LI
Declare the private node which contains a T and a link to the
next node in the list.
.SCORE-HERE 1
.LI
Declare the head and tail pointers to be automatically initiallized
to the null pointer.
.SCORE-HERE 1
.LI
Disable the copy constructor and copy
.V= operator= .
.SCORE-HERE 1
.LI
Declare a
.V= front
function which is a constant function returning a constant reference
to the data in the first node.
.SCORE-HERE 1
.LI
Declare a non-constant
.V= front
function which returns a non-constant reference to the data in the first
node.
.SCORE-HERE 1
.LI
Declare
.V= pop_front
in the way consistent with other containers.
Do not show the implementation.
.SCORE-HERE 1
.LI
Declare
.V= push_back .
Do not show the implementation.
.SCORE-HERE 1
.LE
.LE
.SP 10i
.if t .2C
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer,
which count negative points.
.nr MULTCHOICE_MAX 12
.SCORE-HERE \n[MULTCHOICE_MAX]
.P
.DS
.TS
tab(|); |l2 |r2w(32p) |l0 r2 |r0w(32p) l |.
_
number of||×|1 =||$= a$
correct answers
_
number of||×|\[12] =||$= b$
wrong answers
_
number of|\0\0\0|×|0 =|0
missing answers
_
column total|\n[MULTCHOICE_MAX]||||$= c$
$ c = max ( a - b , 0 ) $
_
.TE
.DE
.ALX 1
.CHOOSE-BEGIN
A process which stays in the background doing nothing
until it accepts a request from a client is called a\(::
.CHOOSE4 daemon vampire werewolf zombie
.CHOOSE-END
.CHOOSE-BEGIN
The value of a
.V= constexpr
identifier is computed at\(::
.CHOOSE4 compile\~time.  link\~time.  program\~load\~time. \
funcation\~call\~time.
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following makes use of the least amount of heap space\(??
.CHOOSE4V deque<T> list<T> map<T> vector<T>
.CHOOSE-END
.CHOOSE-BEGIN
Two processes communicate via a socket,
but each does only writing to the socket,
never reading.
This results in a\(::
.CHOOSE4 deadlock livelock memory\~leak race\~condition
.CHOOSE-END
.CHOOSE-BEGIN
The declaration
.V= "int x;"
inside a function results in 
.V= x
being allocated in what memory segment\(??
.CHOOSE4 data heap stack text
.CHOOSE-END
.CHOOSE-BEGIN
To prevent a constructor from being used implicitly in a conversion
operation,
precede its declaration by what keyword\(??
.CHOOSE4V const explicit inline private
.CHOOSE-END
.CHOOSE-BEGIN
If an object is to be used as if it were a function,
it must have what operator defined\(??
.CHOOSE4V operator() operator* operator-> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= i
is an iterator pointing into a
.V= map ,
then the value associated with a given key is accessed via\(::
.CHOOSE4V i->first i->second i.first i.second
.CHOOSE-END
.CHOOSE-BEGIN
What are the maximum and minimum values of the exit status
value returned by a program\(??
.CHOOSE
$-1$ for error and $0$ for success.
.CHOOSE
$-128$ to $127$.
.CHOOSE
$0$ to $255$.
.CHOOSE
$0$ to $65535$.
.CHOOSE-END
.CHOOSE-BEGIN
In a client/server application,
the client indicates a need to talk
to a server via what system call\(??
.CHOOSE8V= accept (2) bind (2) connect (2) socket (2)
.CHOOSE-END
.CHOOSE-BEGIN
What is a possible way to implement
.V= map
in C++ so that performance is acceptable\(??
.CHOOSE4 double-ended\~queue hash\~table linear\~linked\~list \
red-black\~tree
.CHOOSE-END
.CHOOSE-BEGIN
What class performs storage management by reference counting\(??
.CHOOSE4V auto_ptr<T> counted_ptr<T> shared_ptr<T> unique_ptr<T>
.CHOOSE-END
.LE
.SP 10i
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer,
which count negative points.
.nr MULTCHOICE_MAX 12
.SCORE-HERE \n[MULTCHOICE_MAX]
.P
.DS
.TS
tab(|); |l2 |r2w(32p) |l0 r2 |r0w(32p) l |.
_
number of||×|1 =||$= a$
correct answers
_
number of||×|\[12] =||$= b$
wrong answers
_
number of|\0\0\0|×|0 =|0
missing answers
_
column total|\n[MULTCHOICE_MAX]||||$= c$
$ c = max ( a - b , 0 ) $
_
.TE
.DE
.ALX 1
.CHOOSE-BEGIN
After a process exits but before its parent waits for it,
it is a\(::
.CHOOSE4 daemon vampire werewolf zombie
.CHOOSE-END
.CHOOSE-BEGIN
In OpenGL without transformations on a 2D plane,
the $x$-axis increases \l'.25i'-ward and
the $y$-axis increases \l'.25i'-ward.
.CHOOSE
$x$ leftward and $y$ downward.
.CHOOSE
$x$ leftward and $y$ upward.
.CHOOSE
$x$ rightward, and $y$ downward.
.CHOOSE
$x$ rightward, and $y$ upward.
.CHOOSE-END
.CHOOSE-BEGIN
To register an interrupt handler, such as, for example,
to catch a
.V= SIGINT
without having the program crash,
what function is used\(??
.CHOOSE8V= accept (2) listen (2) sigaction (2) socket (2)
.CHOOSE-END
.CHOOSE-BEGIN
When a
.V= runtime_exception
is caught, how is the specific message found\(??
.CHOOSE4V e.getMessage() e.strerror() e.to_string() e.what()
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following will be flagged
(the compiler issues a warning)
as a narrowing conversion\(??
.CHOOSE4V "int a (4.8);" "int a = 4.8;" "int a = {int(4.8)};" \
"int a {4.8};"
.CHOOSE-END
.CHOOSE-BEGIN
If we have a class
.V= T
and a variable
.V= "T x;" ,
Then normally we would expect
.V= operator<<
that allows
.V= cout<<x;
to be\(::
.CHOOSE
a member of class
.V= T .
.CHOOSE
a member of class
.V= ostream .
.CHOOSE
a virtual function dispatched on
.V= x .
.CHOOSE
not a member of any class.
.CHOOSE-END
.CHOOSE-BEGIN
For class
.V= T ,
in order to ensure that there is no copy constructor for itself
nor for any derived classes,
it should be declared as\(::
.CHOOSE4V "T (const T&) = 0;" "T (const T&) = delete;" \
"T (const T&) = void;" "T (const T&) {}"
.CHOOSE-END
.CHOOSE-BEGIN
What would one expect to be the first non-comment line in
.V= foo.h \(??
.CHOOSE4V #define\~__FOO_H__ #ifdef\~__FOO_H__ #ifndef\~__FOO_H__ \
#include\~\[Dq]foo.h\[Dq]
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following will generate a compile time error message\(??
.CHOOSE4V "\[Dq]a\[Dq] + \[Dq]b\[Dq]" \
"\[Dq]a\[Dq] + string(\[Dq]b\[Dq])" \
"string(\[Dq]a\[Dq]) + \[Dq]b\[Dq]" \
"string(\[Dq]a\[Dq]) + string(\[Dq]b\[Dq])"
.CHOOSE-END
.CHOOSE-BEGIN
Which system call when executed by a server causes it to block
until another process tries to connect to it or until an
interrupt occurs\(??
.CHOOSE8V= accept (2) listen (2) sigaction (2) socket (2)
.CHOOSE-END
.CHOOSE-BEGIN
What is the preferred way of referring to the null pointer in C++11\(??
.CHOOSE4V 0 NULL null nullptr
.CHOOSE-END
.CHOOSE-BEGIN
A move constructor for class
.V= T
would be declared as\(::
.CHOOSE4V T\~(T&&); T\~(T**); T\~(const\~T&); T\~(const\~T*);
.CHOOSE-END
.LE
.FINISH
