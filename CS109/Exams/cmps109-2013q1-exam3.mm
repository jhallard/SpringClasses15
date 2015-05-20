.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Winter\~2013 Final\~Exam
.RCS "$Id: cmps109-2013q1-exam3.mm,v 1.33 2013-03-21 13:35:22-07 - - $"
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
.EN
.de LIQ
.   LI
..
.ALX 1 . 4
.LI
.E= C++\(::
Define a template function which will merge two ranges into a
single container.
.SCORE-HERE 5
.ALX a () "" 0
.LI
It has three template parameters\(::
a forward iterator,
a container,
and a binary predicate.
.LI
It has six actual parameters\(::
two iterators indicating one range,
two iterators indicating another range,
a container into which the ranges are to be merged,
and a binary predicate returning a boolean which computes
a less-than function.
.LI
Assume the output container has a
.V= push_back
method.
.LI
Example call\(::
.V= "merge (c1.begin(), c1.end(), c2.begin(), c2.end(), vec, less);"
.br
will assume the
.V= c1 
range is already sorted into order given by the
.V= less
function,
as is the
.V= c2
range.
The two ranges will then be copied in sorted order into the output
container
.V= vec .
From inside
.V= merge ,
the call
.V= less(a,b)
will be true if 
.V= a
is considered less than 
.V= b .
.LE
.SP 3i
.LI
.E= C++\(::
Define a template class
.V= stack
with all methods defined inline.
.SCORE-HERE 5
.ALX a () "" 0
.LI
It uses a private 
.V= vector
field to hold the stack.
.LI
None of the four default members are declared,
since the automatic defaults are acceptable.
.LI
.V= pop
removes but does not return the top of the stack.
.LI
.V= push
pushes a new element onto the stack.
.LI
.V= top
returns the top of the stack but does not modify the stack.
.LI
.V= empty
tells whether the stack is empty or not.
.LE
.SP 10i
.LI
.E= C++\(::
Write a template function
.V= swap
that will exchange the values of any two variables.
Example\(::
.V= swap(a,b);
should exchange the values of
.V= a
and
.V= b
if the type of those variables has a copy constructor and an
.V= operator= .
.SCORE-HERE 2
.SP 1.25i
.LI
.E= Java\(::
Write a client/server application that shares the current date and time.
Assume, but do not code, any necessary
.V= import 
statements.
.ALX a ()
.LI
Class
.V= date_client
connects to port 10000 of
.V= localhost ,
reads one line, prints it, then exits.
.SCORE-HERE 2
.DS
.ft CB
class date_client {
   public static void main (String[] args) throws IOException {
.DE
.SP 1.25i
.LI
Class
.V= date_server
creates a server socket on port 10000,
then goes into an infinite loop waiting for clients.
Whenever a client connects,
it replies by sending the current date,
after which it disconnects the client and waits for the next client.
Create a
.V= "new Date()"
object each time a date is needed and use its
.V= toString
method.
.SCORE-HERE 3
.DS
.ft CB
class date_server {
   public static void main (String[] args) throws IOException {
.DE
.LE
.SP 1.35i
.LI
.E= C++\(::
Define a template function called
.V= find .
Its first template argument is a forward iterator,
and its second template argument is a predicate of one argument.
The function itself has three arguments,
the first and second being a pair of iterators that bound the
search space,
and the third being a function of one argument which returns a
boolean value.
Return the first occurrence in the range for which the predicate is
true,
and if not found, return the end iterator.
Example call\(::
.V= "find (c.begin(), c.end(), ispositive);"
.SCORE-HERE 3
.SP 10i
.LI
.E= C++\(::
Write a loop that will copy program arguments
(but not the program name)
into the vector.
.SCORE-HERE 1
.DS
.ft CB
int main (int argc, char **argv) {
   vector<string> args;
.DE
.SP 1i
.LI
.E= C++\(::
Consider the trivial class shown here.
.ALX a ()
.LI
Write the prototypes for the
.V= operator=
and the destructor
that would otherwise be provided by default.
.SCORE-HERE 1
.DS
.ft CB
struct box {
   size_t size;
   int *data;
.DE
.LI
Implement
.V= operator=
for this class.
It needs to copy the data instead of sharing it with the source object.
Code it as it would appear in the implementation
.=V ( \&.cpp )
file.
.SCORE-HERE 3
.SP 1.5i
.LI
Implement the destructor as it would appear in the implementation file.
.SCORE-HERE 1
.SP 1i
.LE
.LI
.E= C++\(::
Finish the function,
which returns the average value in the range.
.SCORE-HERE 2
.DS
.ft CB
template <typename iterator>
double average (const iterator &begin, const iterator &end) {
.DE
.SP 1i
.LI
.E= C++\(::
Define
.V= operator<<
which can print all of the elements of a vector of any type,
assuming that the constituent elements already have an appropriate
.V= operator<<
defined.
The operator prints all of the elements with a single space between
successive elements.
.SCORE-HERE 2
.LE
.SP 10i
.if t .2C
.\".nr Ds 0
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer.
Wrong answers are worth negative points.
.nr MULTCHOICE_MAX 11
.SCORE-HERE \n[MULTCHOICE_MAX]
.P
.DS
.TS
tab(|); |l |r2w(.4i) |l1 r1 l |rw(.2i) l |.
_
number of||×|1|\&=||$= a$
correct answers
_
number of||×|\[12]|\&=||$= b$
wrong answers
_
number of|\0\0\0|×|0|\&=|0
missing answers
_
column total|\n[MULTCHOICE_MAX]|||||$= c$
$ c = max ( a - b , 0 ) $
_
.TE
.DE
.ALX 1 . 4
.CHOOSE-BEGIN
If
.V= v
is a 
.V= vector ,
then
.V= v.begin()
is the same as\(::
.CHOOSE4V v[0] &v[0] *v[0] \[ti]v[0]
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following operators does a bidirectional iterator
have that a forward iterator does not have\(??
.CHOOSE4V *i ++i --i i->f
.CHOOSE-END
.CHOOSE-BEGIN
For an integer
.V= a ,
if
.V= a
is __(x)__
then
.V= a/8
is equivalent to
__(y)__.
.CHOOSE
(x)
.V= signed \(;;
(y)
.V= a<<3
.CHOOSE
(x)
.V= signed \(;;
(y)
.V= a>>3
.CHOOSE
(x)
.V= unsigned \(;;
(y)
.V= a<<3
.CHOOSE
(x)
.V= unsigned \(;;
(y)
.V= a>>3
.CHOOSE-END
.CHOOSE-BEGIN
What is the declaration of the postfix operator
.V= ++
which is a member of class
.V= foo \(??
.CHOOSE4V "foo &operator++ ();" "foo &operator++ (foo &);" \
"foo operator++ (foo &, int);" "foo operator++ (int);"
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following instance fields will most strongly suggest
that a default
.V= operator=
is inappropriate for a class\(??
.CHOOSE4 inline\~object pointer primitive reference
.CHOOSE-END
.if t .ne 20
.CHOOSE-BEGIN
The outermost container in a Java GUI is a
.CHOOSE4V JArea JFrame JGrid JPanel
.CHOOSE-END
.CHOOSE-BEGIN
Storage management by reference counting fails on what kind of data
structure\(??
.CHOOSE4 acyclic\~graph binary\~tree cyclic\~graph hash\~table
.CHOOSE-END
.CHOOSE-BEGIN
The
.V= std::map
data structures is a\(::
.CHOOSE4 directed\~acyclic\~graph hash\~table linear\~linked\~list \
red-black\~tree
.CHOOSE-END
.CHOOSE-BEGIN
Which data structure uses a contiguous block of heap memory\(??
.CHOOSE4V std::deque std::list std::map std::vector
.CHOOSE-END
.CHOOSE-BEGIN
If the exception
.V= exn
is thrown,
what is the proper way to catch it\(??
.CHOOSE4V "catch (exn &e)" "catch (exn *e)" "catch (exn \[ti]e)" \
"catch (exn e)"
.CHOOSE-END
.CHOOSE-BEGIN
The first language to use concepts such as
.E= class
and
.E= virtual
was\(::
.CHOOSE4 Algol Fortran Lisp Simula
.CHOOSE-END
.LE
.SP 10i
.\".nr Ds 0
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer.
Wrong answers are worth negative points.
.nr MULTCHOICE_MAX 11
.SCORE-HERE \n[MULTCHOICE_MAX]
.P
.DS
.TS
tab(|); |l |r2w(.4i) |l1 r1 l |rw(.2i) l |.
_
number of||×|1|\&=||$= a$
correct answers
_
number of||×|\[12]|\&=||$= b$
wrong answers
_
number of|\0\0\0|×|0|\&=|0
missing answers
_
column total|\n[MULTCHOICE_MAX]|||||$= c$
$ c = max ( a - b , 0 ) $
_
.TE
.DE
.ALX 1 . 4
.CHOOSE-BEGIN
When two threads update the same variable without synchronization,
leading to unpredictable results,
this is called a \l'.25i' condition.
.CHOOSE4 daemon deadlock race spinlock
.CHOOSE-END
.CHOOSE-BEGIN
An abstract class\(::
.CHOOSE
can not be instantiated
.CHOOSE
can not specify an interface
.CHOOSE
has no virtual functions
.CHOOSE
must be derived from a base class
.CHOOSE-END
.CHOOSE-BEGIN
The Java GUI considers the coordinate $ ( 0 , 0 ) $ to be at what
part of the screen\(??
.CHOOSE4 lower\~left lower\~right upper\~left upper\~right
.CHOOSE-END
.CHOOSE-BEGIN
The Postscript coordinate system considers $ ( 0 , 0 ) $ to be at what
part of the page\(??
.CHOOSE4 lower\~left lower\~right upper\~left upper\~right
.CHOOSE-END
.CHOOSE-BEGIN
What is an interface that requires implementation of the metnod
.V= run \(??
.CHOOSE4V Runnable Synchronized Thread Throwable
.CHOOSE-END
.CHOOSE-BEGIN
In C++11,
if an implicitly generated member should be suppressed
as inappropriate for the class,
what should be done\(??
.CHOOSE
Declare it as private and not implement it.
.CHOOSE
Declare it as public and throw a logic_error exception if it is called.
.CHOOSE
Declare it as public but instead of implementing it, mark it as
.V= =\~delete .
.CHOOSE
Declare it but put an
.V= assert(false)
statement in the body.
.CHOOSE-END
.CHOOSE-BEGIN
Which operator may be declared with any number of arguments,
depending on the semantics of the operator\(??
.CHOOSE4V operator() operator++ operator<> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
A keyword in C++11 that has a radically different meaning from 
what it has in ANSI C is\(::
.CHOOSE4V auto struct typedef volatile
.CHOOSE-END
.CHOOSE-BEGIN
Following the
.V= Makefile
dependency
.V= "%.o : %.cpp"
an appropriate compilation command would be\(::
.CHOOSE4V "\[Do]{GPP} %.cpp" "\[Do]{GPP} -c \[Do]<" \
"\[Do]{GPP} -c \[Do]@" "\[Do]{GPP} -o \[Do]<"
.CHOOSE-END
.CHOOSE-BEGIN
Given the declaration of
.V= i ,
what will print out a string\(??
.VTCODE* 1 "vector<string*>::iterator i;"
.CHOOSE4V cout<<i; cout<<*i; cout<<**i; cout<<***i;
.CHOOSE-END
.CHOOSE-BEGIN
Following
.V= "foo x;"
the statement
.V= "foo y = x;"
is a call to\(::
.CHOOSE
assignment
.V= operator=
.CHOOSE
the copy constructor
.CHOOSE
the default constructor
.CHOOSE
the destructor
.CHOOSE-END
.LE
.FINISH
