.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Summer\~2013 Final\~Exam
.RCS "$Id: cmps109-2013q3-exam3.mm,v 1.174 2013-08-28 18:11:47-07 - - $"
.DS
.PS
examboxes(4)
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
This test is shorter than the usual final exam
because summer session does not have an exam week.
The time limit is 100 minutes,
rather than the usual 180 minutes given in the other quarters.
.EQ
delim $$
tdefine suchthat "{type relation |}"
.EN
.de LIQ
.   LI
..
.ALX 1 . 4
.LI
Write a complete program
(everything that needs to be placed in the source file)
in C++ to print the message
``Hello, World!''.
.SCORE-HERE 1
.SP .75i
.LI
Write a template function to reverse a sequence,
given a pair of bidirectional iterators.
Its template argument is any iterator type and its two function
arguments are a begin and end iterator.
Assume the iterators have
.V= operator++ ,
.V= operator-- ,
unary
.V= operator* ,
and
.V= operator!= .
The iterators are passed by value, so you may modify them.
Use the STL function whose prototype is
.V= "template <class T> void swap (T& a, T& b);"
.SCORE-HERE 2
.SP 1i
.LI
Write a template function to print out a sequence,
given a pair of forward iterators.
Assume an appropriate
.V= operator<< ,
and print one space between each element,
but not on the front or end.
.SCORE-HERE 2
.SP 1i
.LI
Define a template function called
.V= swap
which exchanges two variables passed in by non-constant reference.
(Hint\(::
see above.)
Use mover, not copier, operations.
.SCORE-HERE 2
.SP 1i
.LI
Define a template function
.V= copy .
Its first template argument is an input iterator from which copying
is done.
Its second template argument is an output iterator.
Its first two function arguments are begin and end iterators describing
the input sequence.
Its third function argument is a begin iterator pointing at the
output sequence.
It is assumed that there is enough space in the output container.
.SCORE-HERE 3
.SP 10i
.LI
Define a
.V= "struct accumulator"
which acts as a function object to accumulate the sum of a sequence of 
.V= int s.
For example,
after the declaration
.V= "accumulator acc" ,
the call
.V= "for_each(v.begin(),v.end(),acc)"
will cause the sum of all elements in
.V= v
to be in
.V= acc.sum .
The function
.V= for_each
applies the function to each element in the range.
.SCORE-HERE 1
.SP .5i
.LI
Provide a partial interface and implementation of class
.V= complex .
Each object has a real and an imaginary field of type
.V= double .
Show only the following three function members\(::
.ALX i () "" 0
.LI
Show one constructor which takes zero, one or two arguments,
and may be used to implicitly convert a
.V= double
to a complex.
The constructor has two arguments,
both of which default to 0.
.LI
Show
.V= operator<< ,
which may be used to print a complex number.
It prints a left parenthesis, followed by the real part,
followed by a comma, followed by the imaginary part,
followed by a right parenthesis.
.LI
Show binary
.V= operator+ ,
which is a member,
which adds two complex numbers using the formula
$ ( a , b ) + ( c , d ) = ( a + c , b + d ) $.
.LE
Given the description above,
answer the following questions\(::
.ALX a ()
.LI
Based on that description and showing only what is asked,
what would go in the header file
.V= complex.h \(??
Make sure members have correct protection.
Show how to declare the data fields given above.
Do not put anything in the header file that can go into the 
implementation file.
.SCORE-HERE 2
.SP 1.2i
.LI
Show what would go in the implementation file
.V= complex.cpp \(::
.ALX i ()
.LI
For the constructor described above.
.SCORE-HERE 1
.SP .6i
.LI
For
.V= operator+ .
.SCORE-HERE 1
.SP .6i
.LI
For
.V= operator<< .
.SCORE-HERE 1
.SP .6i
.LE
.LE
.LI
Write a program in Java.
Define a class
.V= say
whose constructor argument is a string,
and which, when run as a thread,
prints that string to the standard output then quits.
Write a main program which starts up that class as a thread
twice, once with the argument ``Hello'', and once with the
argument ``World''.
.ALX a ()
.LI
Show the code for class
.V= say .
.SCORE-HERE 2
.SP 1i
.LI
Show the code for the
.V= main
function .
.SCORE-HERE 2
.LE
.LE
.SP 10i
.if t .2C
The following table contains
examples of various kinds of polymorphism.
For each one,
identify the classification as
.E= universal
or
.E= ad\~hoc .
Also identify the specific kind as one of
.E= conversion ,
.E= inheritance ,
.E= overloading ,
or
.E= generic .
.SCORE-HERE 2
.DS
.TS
tab(|) allbox; lw(210p)fCB.
T{
class foo { virtual void f(); }
class bar: public foo { virtual void f(); }
T}
T{
template <typename T>
class c { void f (T&); }
T}
T{
void f (int x);
void f (double x);
T}
T{
void f (double x);
f (6);
T}
.TE
.DE
.SP
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer.
Wrong answers are worth negative points.
.nr MULTCHOICE_MAX 10
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
The acronym RAII means\(::
.CHOOSE4 "Random Access Inhibits Implementation" \
"Reading An Iterator Incrementally" \
"Resource Acquisition Is Initialization" \
"Restoring Allocators Initially Inverted"
.CHOOSE-END
.CHOOSE-BEGIN
Reference counting for storage management fails with what kind
of data structure\(??
.CHOOSE4 binary\~tree cyclic\~graph hash\~table linked\~list
.CHOOSE-END
.CHOOSE-BEGIN
Even though all run in $ O ( n ) $ time,
given the following loop\(::
.VTCODE* 0 "for (i=v.begin(); i!=v.end(); *i++=0);"
For which declaration of
.V= v
will the code run fastest\(??
.CHOOSE4V list<int>\~v; map<int,int>\~v; unordered_map<int,int>\~v; \
vector<int>\~v;
.CHOOSE-END
.CHOOSE-BEGIN
Which statement causes the pointer
.V= p
to become dangling\(??
.CHOOSE4V delete\~p; free\~p; malloc\~p; new\~p;
.CHOOSE-END
.CHOOSE-BEGIN
What keyword introduces a function that is
selected at run-time and dynamically
dispatched based on a pointer\(??
.CHOOSE4V friend static template virtual
.CHOOSE-END
.CHOOSE-BEGIN
If a virtual function in a base class has the same signature
as one in a derived class, 
we say that the function in the derived class \l'.25i'
the one in the base class.
.CHOOSE4 overflows overloads overrides overwrites
.CHOOSE-END
.CHOOSE-BEGIN
In the bigint project, multiplying an $m$-digit number by an $n$-digit
number should take how long\(??
.CHOOSE
$ O ( m + n ) $
.CHOOSE
$ O ( m 10 sup n ) $
.CHOOSE
$ O ( m log n ) $
.CHOOSE
$ O ( m n ) $
.CHOOSE-END
.CHOOSE-BEGIN
A non-static variable declared inside a function is bound to
a particular address at\(::
.CHOOSE
compile time.
.CHOOSE
link time.
.CHOOSE
program load time.
.CHOOSE
the time the function is called.
.CHOOSE-END
.CHOOSE-BEGIN
In class
.V= vector<T> ,
which operator necessarily returns a
.V= T* \(??
.CHOOSE4V operator* operator++ operator-> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
A thread that sits in the background waiting for
another thread to make a request of it,
then which performs the request, then waits again,
is called a \l'.25i' thread.
.CHOOSE4 daemon vampire werewolf zombie
.CHOOSE-END
.LE
.SP 10i
Write out the
\f[BI]C++11\f[P]\kx\v'2p'\h'|0'\l'\nxu'\v'2p'\h'|0'\l'\nxu'\v'-4p'
prototypes of all members of class
.V= foo
as they would appear in a header file without implementations.
.SCORE-HERE 2
.DS
.TS
box; lw(210p)fCB.
class foo {
.SP 9
};
.TE
.DE
.SP
Multiple choice.
To the
.E= left
of each question,
write the letter that indicates your answer.
Write
.E= Z
if you don't want to risk a wrong answer.
Wrong answers are worth negative points.
.nr MULTCHOICE_MAX 10
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
For some
.V= vector\~v ,
what is the same as
.V= v.begin() \(??
.CHOOSE4V \~v[0] !v[0] &v[0] *v[0]
.CHOOSE-END
.CHOOSE-BEGIN
For class
.V= foo ,
what should the parameter list look like
for the non-member declaration
.VTCODE* 0 "ostream& operator<< (" \l'.25i' ");"
.CHOOSE4V "const ostream&, const foo&" "const ostream&, foo&" \
"ostream&, const foo&" "ostream&, foo&"
.CHOOSE-END
.CHOOSE-BEGIN
In a systems programming application,
where we need to make an unsigned integer from a pointer,
what cast would be used\(??
.CHOOSE4V const_cast dynamic_cast reinterpret_cast static_cast
.CHOOSE-END
.CHOOSE-BEGIN
A virtual function table exists as a __(x)__ table for each __(y)__
in a program.
.CHOOSE
(x) = dynamic\(;) (y) = class
.CHOOSE
(x) = dynamic\(;) (y) = object
.CHOOSE
(x) = static\(;) (y) = class
.CHOOSE
(x) = static\(;) (y) = object
.CHOOSE-END
.CHOOSE-BEGIN
A Java class that implements
.V= Runnable
must have a method named\(::
.CHOOSE4V run start synchronized wait
.CHOOSE-END
.CHOOSE-BEGIN
A web server written in Java,
having opened a
.V= ServerSocket ,
allows a client to connect by calling what method\(??
.CHOOSE4V accept getInputStream start wait
.CHOOSE-END
.CHOOSE-BEGIN
If two or more threads access the same variable without
synchronization,
what results\(??
.CHOOSE4 deadlock livelock race\~condition segmentation\~fault
.CHOOSE-END
.CHOOSE-BEGIN
In this picture of a page,
in which corner is the Postscript page coordinate (0,0)\(??
.CHOOSE4 upper\~left upper\~right lower\~left lower\~right
.if dPSPIC \{
.sp -6.95v
.in 168p
.PS .7i
C: "" at (0,0)
D: "" at (.85,0)
A: "" at (0,1.1)
B: "" at (.85,1.1)
line from A to B
line from A to C
line from B to D
line from C to D
circle thick 2 radius .2 at (.425,.55)
circle fill 1 radius .02 at (.35,.6)
circle fill 1 radius .02 at (.5,.6)
arc thick 2 radius .08 from (.35,.5) to (.5,.5)
"(C)" at C+(.15,.11)
"(D)" at D+(-.15,.11)
"(A)" at A+(.15,-.11)
"(B)" at B+(-.15,-.11)
.PE
.sp -1.5v
.\}
.CHOOSE-END
.CHOOSE-BEGIN
An abstract class in C++\(::
.CHOOSE
can not be instantiated.
.CHOOSE
can not be used like a Java interface.
.CHOOSE
has no virtual functions.
.CHOOSE
must be a derived class.
.CHOOSE-END
.CHOOSE-BEGIN
.V= vector<T>::push_back
has an amortized time complexity of\(::
.CHOOSE
$ O ( 1  ) $
.CHOOSE
$ O ( log sub 2 n  ) $
.CHOOSE
$ O ( n  ) $
.CHOOSE
$ O ( n log sub 2 n  ) $
.CHOOSE-END
.LE
.de BX
.nr bxw \w'\\$1'+.4m
\Z'\v'.20m'\D'l 0 -1m'\D'l \\n[bxw]u 0'\D'l 0 1m'\D'l -\\n[bxw]u 0''\
\Z'\h'.2m'\\$1'\
\h'\\n[bxw]u'
.. 
.de footnote
.  br
The following refers to which
of Shakespeare's plays\(??
.BX \f[CB]2BORD4\f[P]
.  br
..
.wh -1i-2v footnote
.FINISH
