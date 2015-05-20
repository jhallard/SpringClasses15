.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Summer\~2014 Final\~Exam
.RCS "$Id: cmps109-2014q3-exam2.mm,v 1.71 2014-08-12 14:49:06-07 - - $"
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
Assume the
.=V `` "using namespace std;" ''
directive.
.ft R
.EQ
delim $$
tdefine suchthat "{type relation |}"
.EN
.ALX 1
.LI
Rewrite the following statement using the two-semicolon form of
.V= for -loop
and iterators instead of the colon form\(::
\0\0\0
.BOX "\f[CB]\0for (auto i&: c) f(i);\0\f[P]"
\0\0\0
.SCORE-HERE 1
.SP .5i
.LI
The following table contains
fragmentary examples of various kinds of polymorphism.
For each example\(::
identify the general kind of polymorphism by writing one of the words
.E= universal
or
.E= ad\~hoc \(;;
also identify the specific kind of polymorphism by writing one of the
words
.E= conversion ,
.E= inheritance ,
.E= overloading ,
or
.E= template .
.SCORE-HERE 2
.DS
.TS
tab(|) allbox; lw(212p)efCB lefCB.
T{
class foo {virtual void f(); }
class bar: public foo {
   virtual void f();
}
T}|T{
class stack<item_t> {
   void push (item_t);
}
T}
T{
int add (int x, int y);
double add (double x, double y);
\&\0
T}|T{
double f (double x);
f (6);
\&\0
T}
.TE
.DE
.LI
Write a
.V= main
function that reads in (white-space delimited) words from
.V= cin
using
.V= >> .
The input file has two words per line,
the first is a key and the second is its value.
Put each key/value pair into a map.
At end of file,
print each key and value pair on a line by itself,
with the keys sorted into lexicographic order.
.SCORE-HERE 3
.SP 1.5i
.LI
Code the template function 
.V= merge ,
which merges two sorted ranges into a single output range.
It has two template arguments\(::
an iterator type capable of iterating over the input ranges,
and a container type with a
.V= push_back
operation for the output container.
For example, if we have two sorted vectors
.V= v1
and
.V= v2
and wish to merge them into an output vector
.V= vo ,
we could use the statement
.VTCODE* 1 "merge (v1.cbegin(), v1.cend(), v2.cbegin(), v2.cend(), vo);"
Assume the elements can be compared with
.V= operator<
and that they are sorted into ascending order.
.SCORE-HERE 4
.SP 10i
.LI
Write the function
.V= draw_square ,
which will draw a square (as a
.V= GL_POLYGON )
in an OpenGL window,
given the $ ( x , y ) $ position of
the lower left corner,
and the width and color of the square.
The edges of the square should be parallel to the edges of the window.
.SCORE-HERE 3
.DS
.ft CB
void draw_square (GLfloat xpos, GLfloat ypos, GLfloat width, \
GLubyte* color) {
.DE
.SP 1.5i
.LI
Define three classes\(::
.V= shape ,
which is entirely abstract\(;;
.V= rectangle ,
non-abstract, which inherits from
.V= shape \(;;
and
.V= square ,
which inherits from
.V= rectangle .
Assume there are many other things that might inherit from
.V= shape ,
but they are not part of this questions.
.ALX i () "" 0
.LI
The ctor for
.V= shape
should not be accessible except to its subclasses.
.LI
If we declare
.V= "shape* p" ,
then
.V= p->area()
and
.V= p->perimeter()
should compute the values required.
.LI
Do not duplicate code when defining
.V= area
and
.V= perimeter ,
so make them abstract, virtual, inherited, etc.,
as appropriate.
.LI
Use field initializers as appropriate.
.V= Rectangle
should keep its length and width information.
.LE
Complete the following classes\(::
.ALX a ()
.LI
.SCORE-HERE 2
.V= "class shape"
.SP 1i
.LI
.SCORE-HERE 2
.V= "class rectangle"
.SP 1i
.LI
.SCORE-HERE 1
.V= "class square"
.SP 1i
.LE
.LI
Assuming that the previous question defined the virtual abstract
function
.V= print
in class
.V= shape ,
define
.V= operator<<
so that an arbitrary object of type
.V= shape*
can be printed.
Example\(::
The following two statements should print a shape.
.SCORE-HERE 2
.VTCODE* 1 "shape *p;"
.VTCODE* 1 "cout << p << endl;"
.SP 10i
.LI
Given a class
.V= complex
outlined here, with real and imaginary fields,
show what would go in the header file to define\(::
.ALX a () "" 0
.LI
A friend
.V= operator<<
which can be used to print it.
.SCORE-HERE 1
.LI
A member binary
.V= operator*
which multiplies two complex  numbers.
.SCORE-HERE 1
.LE
.DS
.ft CB
class complex {
   private:
      double real;
      double imag;
   public:
.DE
.SP 1i
.LI
For the previous question,
show what would go into an implementation file for the two
definitions above\(::
.ALX a () "" 0
.LI
.V= operator<<
prints a complex number in parentheses with the fields separated
by a comma.
The imaginary part is suffixed with the letter
.=V `` i ''.
For example\(::
.V= (8.3,4.9i) .
.SCORE-HERE 2
.LI
Some mathematics for
.V= operator* \(::
.SCORE-HERE 2
.br
$ (a + b i ) ~ ( c + d i ) = ( a c - b d ) + ( a d + b c ) i $,
where $ i = sqrt { - 1 } $.
.LE
.SP 1.7i
.LI
Write the body of a function
.V= inner_product ,
which has two arguments of type
.V= vector<double>
and returns the inner product,
which is a
.V= double .
.SCORE-HERE 2
.br
The formula for the inner product of two vectors $u$ and $v$ is
$ p = sum from { i = 0 } to { n - 1 } u sub i v sub i $.
.SP 1.3i
.LI
Write a complete template function whose argument is a
.V= vector
and which prints out all the elements of the vector,
with one space between successive elements.
There is no space before or after the sequence.
Assume
.V= operator<<
has been defined for the elements of the vector.
.SCORE-HERE 2
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
If
.V= p
is an iterator,
which expression will return the address of the object
that it refers to\(??
.CHOOSE4V &&p &*p *&p **p
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following statements will change meaning if
the parentheses are removed\(??
.CHOOSE4V "a = (b);" "double d();" "int (i);" "return (x);"
.CHOOSE-END
.CHOOSE-BEGIN
Which one of these operators may be defined with an arbitrary
number of arguments\(??
.CHOOSE4V operator() operator<< operator== operator[]
.CHOOSE-END
.CHOOSE-BEGIN
For
.V= vector<int>\~v ,
the call to
.V= v.crbegin()
will return an iterator pointing at\(::
.CHOOSE4V v[-1] v[0] v[v.size()-1] v[v.size()]
.CHOOSE-END
.CHOOSE-BEGIN
For
.V= vector<int>\~v ,
the call to
.V= v.begin()
will return an iterator pointing at\(::
.CHOOSE4V v[-1] v[0] v[v.size()-1] v[v.size()]
.CHOOSE-END
.CHOOSE-BEGIN
Which is a
.V= Makefile
comment\(??
.CHOOSE4V #\~comment --\~comment /*\~comment\~*/ //\~comment
.CHOOSE-END
.CHOOSE-BEGIN
What category of membership in a class allows a member to
be accessed by the class itself and also by any class
derived from it,
but by no other class\(??
.CHOOSE4V friend private protected public
.CHOOSE-END
.CHOOSE-BEGIN
Which is a declaration of an abstract function\(??
.CHOOSE4V "const void virtual f();" "virtual void f() = 0;" \
"virtual void f() override;" "void f() const virtual;"
.CHOOSE-END
.CHOOSE-BEGIN
An IP address such as 128.114.108.152 is an example of what
address family passed to the
.V= socket (2)
system call\(??
.CHOOSE4V AF_INET AF_INET6 AF_IPX AF_UNIX
.CHOOSE-END
.CHOOSE-BEGIN
What initializer should be appended to the statement
.VTCODE* 0 "const GLubyte GREEN[] ="
.CHOOSE4V "{0x00, 0x00, 0xFF};" "{0x00, 0xFF, 0x00};" \
"{0x00, 0xFF, 0xFF};" "{0xFF, 0x00, 0x00};"
.CHOOSE-END
.CHOOSE-BEGIN
In the linked list implementation of project 3,
if there are $n$ data items in the list,
then how many occurrences will there be of
.V= "struct link" \(??
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( n - 1 ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n + 1 ) $
.CHOOSE-END
.CHOOSE-BEGIN
In the library implementation of class
.V= list ,
how long does it take to access the $ n sup { roman th } $
element of a list\(??
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( log sub 2 n ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n log sub 2 n ) $
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
The keyword
.V= override
is used in the definition of what kind of function\(??
.CHOOSE4V const static template virtual
.CHOOSE-END
.CHOOSE-BEGIN
The highest AF_INET port number is\(::
.CHOOSE4 \0\0\0\0\0\0\0255 \0\0\0\0\065535 \0\016777215 4294967295
.CHOOSE-END
.CHOOSE-BEGIN
When two threads update the same variable without synchronization,
the result is a\(::
.CHOOSE4 deadlock livelock memory\~leak race\~condition
.CHOOSE-END
.CHOOSE-BEGIN
Which is a move constructor\(??
.CHOOSE4V T(T&&); T(T**); T(const\~T&&); T(const\~T**);
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= Foo
is an abstract class,
and we have the declarations\(::
.V= Foo*\~p;
.V= Foo\~f;
.br
Then the declaration of\(::
.CHOOSE
.V= p
is good,
.V= f
is an error.
.CHOOSE
.V= p
is an error,
.V= f
is good.
.CHOOSE
both are good.
.CHOOSE
both are errors.
.CHOOSE-END
.CHOOSE-BEGIN
If an object is called as a function,
what operator must it have defined\(??
.CHOOSE4V operator() operator* operator-> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
Which container allows direct access via
.V= operator[]
and also allows the push and pop functions at both the
front and back in $O ( 1 ) $ time\(??
.CHOOSE4V deque list stack vector
.CHOOSE-END
.CHOOSE-BEGIN
After starting a thread with a command like
.V= "thread t1(hello);"
how does the call\%ing function then suspend until
.V= t1
finishes\(??
.CHOOSE4V t1.catch(); t1.join(); t1.pause(); t1.wait();
.CHOOSE-END
.CHOOSE-BEGIN
Which member of a class must do different things,
depending on whether its left operand is the same as its right
operand or not\(??
.CHOOSE
copy constructor
.CHOOSE
copy
.V= operator=
.CHOOSE
default constructor
.CHOOSE
.V= operator==
.CHOOSE-END
.CHOOSE-BEGIN
The keywords
.V= class
and
.V= struct
mean the same thing,
except that by default,
members of a
.V= class
are __(x)__
and members of a
.V= struct
are __(y)__.
.CHOOSE4 "(x) = private, (y) = private" "(x) = private, (y) = public" \
"(x) = public, (y) = private" "(x) = public, (y) = public"
.CHOOSE-END
.CHOOSE-BEGIN
To convert a 
.V= sockaddr_in*
to a
.V= sockaddr* ,
which are two different types unrelated by inheritance,
what kind of cast is used\(??
.CHOOSE4V const_cast dynamic_cast reinterpret_cast static_cast
.CHOOSE-END
.CHOOSE-BEGIN
Given a pair of variables,
an operation to swap (exchange) their values will be done efficiently
by a\(::
.CHOOSE
copy constructor
.CHOOSE
copy
.V= operator=
.CHOOSE
move constructor 
.CHOOSE
move
.V= operator=
.CHOOSE-END
.LE
.FINISH
