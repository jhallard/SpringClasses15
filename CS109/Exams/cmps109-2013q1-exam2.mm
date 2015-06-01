.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Winter\~2013 Test\~#2
.RCS "$Id: cmps109-2013q1-exam2.mm,v 1.25 2013-02-27 17:30:13-08 - - $"
.DS
.PS
examboxes(3)
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
Assume a declaration
.V= "intvector v;"
followed by some code to put things into the vector.
Finish the classes
.V= intvector
and
.V= intvector::iterator
adding only those members which are needed to make the following
code work\(::
.V= "for (intvector::iterator i = v.begin(); i != v.end(); ++i) \
cout << *i << endl;
.br
Code all functions as inline functions,
not in the usual way as separate prototypes and implementations.
.ALX a ()
.LI
Code added directory to
.V= intvector \(::
.V= begin
and
.V= end .
.SCORE-HERE 4
.DS
.ft CB
class intvector {
   private:
      size_t size;
      int *data;
   public:
      class iterator;
.DE
.SP 1.5i
.LI
Code added to
.V= intvector::iterator \(::
Any function or operator used in the for-loop and
any constructor needed by
.V= begin
or
.V= end .
Assume that
.V= iterator
is declared inside of class
.V= intvector.
.SCORE-HERE 6
.DS
.ft CB
class iterator {
   friend class intvector;
   private:
      int *pointer;
.SP .5i
   public:
.DE
.LE
.SP 10i
.LI
Define a template function called
.V= printthem
which takes a pair
of input iterators as arguments and prints each element of
the data structure, one per line,
assuming that
.V= operator<<
is defined on the elements.
.SCORE-HERE 1
.DS
.ft CB
template <typename itor>
void printthem (const itor &begin, const itor &end) {
.DE
.SP 1i
.LI
Write a template function 
.V= copyreverse
whose argument is any vector passed in by constant reference
and whose result, returned by value is a new vector.
It uses a
.E= reverse
iterator
.=V ( rbegin ,
.V= rend )
to access successive elements of the argument vector.
.SCORE-HERE 3
.SP 1.5i
.LI
Consider an object-oriented hierarchy with a class
.V= base ,
from which is extended classes
.V= rectangle
and
.V= circle .
Code only those specific members/functions specified here
and ignore the others.
.ALX a ()
.LI
Define an abstract base class 
.V= base
with a default constructor.
Its only protected field is a serial number which is
initialized successively to integers starting from 1,
and an abstract function
.V= area
which returns a
.V= double .
.SCORE-HERE 2
.SP 1.25i
.LI
Define a derived class
.V= circle
which has a ctor that accepts a diameter as an argument
and which overrides
.V= area .
.SCORE-HERE 2
.SP 1.25i
.LI
Define a derived clas
.V= rectangle
whose ctor takes a length and a width (both
.V= double s)
and implements
.V= area .
.SCORE-HERE 2
.LE
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
What form of polymorphism describes template classes and functions\(??
.CHOOSE4 conversion generic inheritance overloading
.CHOOSE-END
.CHOOSE-BEGIN
If one wishes to define a stack of integers in terms of a vector,
but prohibit all vector operations from being used by the stack's
client, except for those explicitly listed,
what is the proper form of inheritance\(??
.CHOOSE4V "class stack: private vector<int> {" \
"class stack: protected vector<int> {" \
"class stack: public vector<int> {" \
"class stack: template vector<int> {"
.CHOOSE-END
.CHOOSE-BEGIN
If we declare
.V= "foo x;"
and call a function with the syntax
.V= f(x);
what declaration of 
.V= f
will allow it to modify
.V= x \(??
.CHOOSE4V "void f (const foo &);" "void f (foo &);" \
"void f (foo *);" "void f (foo);"
.CHOOSE-END
.CHOOSE-BEGIN
If a module's interface is specified in
.V= foo.h ,
what should the first non-comment line be\(??
.CHOOSE4V #define\~__FOO_H__ #ifdef\~__FOO_H__ #ifndef\~__FOO_H__ \
#include\~__FOO_H__
.CHOOSE-END
.CHOOSE-BEGIN
It is necessary to make a destructor virtual if any\(::
.CHOOSE4 "constructor is virtual" "member field is a pointer" \
"member function is virtual" "time inheritance is used"
.CHOOSE-END
.CHOOSE-BEGIN
If class
.V= complex
is implemented as a pair of
.V= double s,
what is an appropriate overloaded constructor\(??
.CHOOSE4V "\[ti]complex (vector<double>);" \
"\[ti]complex (double, double);" \
"complex (double r = 0, double i = 0);" \
"explicit complex (double r);"
.CHOOSE-END
.CHOOSE-BEGIN
If it is desirable to suppress creation of
.V= operator=
in a given class,
define it as a member and append what to the end of the
definition in the header\(??
.CHOOSE4V =\~default =\~delete =\~virtual =\~void
.CHOOSE-END
.CHOOSE-BEGIN
The average speed of
.V= vector::push_back
is\(::
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( log sub 2 n ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n log sub 2 n ) $
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= foo\~*p;
the expression 
.V= ++p
changes the address in
.V= p
by how many bytes\(??
.CHOOSE4V sizeof(1) sizeof(*p) sizeof(foo) sizeof(uintptr_t)
.CHOOSE-END
.CHOOSE-BEGIN
The
.V= operator--
is available on what kind of iterator\(??
.CHOOSE4 bidirectional forward input output
.CHOOSE-END
.CHOOSE-BEGIN
By default,
members of a
.V= class
are __(x)__ and members of a
.V= struct
are __(y)__.
.CHOOSE
(x) = private, and (y) = private
.CHOOSE
(x) = private, and (y) = public
.CHOOSE
(x) = public, and (y) = private
.CHOOSE
(x) = public, and (y) = public
.CHOOSE-END
.LE
.FINISH
