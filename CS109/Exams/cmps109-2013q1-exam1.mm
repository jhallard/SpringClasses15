.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Winter\~2013 Test\~#1
.RCS "$Id: cmps109-2013q1-exam1.mm,v 1.22 2013-01-30 21:32:51-08 - - $"
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
Write the function 
.V= filter .
It takes a pair of iterators
values which indicate the bounds of an input vector,
and a predicate which decides whether its argument is good or bad.
Return a list containing a copy of all elements in the
original range which are considered good.
Note that both
.V= list
and
.V= vector 
have a function
.V= push_back .
.SCORE-HERE 2
.DS
.ft CB
typedef vector<string>::const_iterator citer;
typedef bool (*isgood) (const string &);
list<string> filter (const citer &begin, const citer &end, isgood p) {
.SP 1i
.DE
.LI
Write a header file for class
.V= queue .
Do not show anything that might appear in the implementation file.
Show only those parts of the header file required here.
Use proper judgement as to what is public and what is private.
.ALX a () "" 0
.LI
It has a
.V= head
and a
.V= tail
pointer to a linked list of
.V= node s,
which are private to the queue.
Each node contains an
.V= int
and a pointer to the next node.
Define the head and tail pointers and the nested class node.
.SCORE-HERE 2
.LI
Define the friend declaration and prototype for a shift
.=V ( << )
operator which can be used to print it.
.SCORE-HERE 2
.LI
Define
.V= pop_front ,
.V= front ,
and
.V= push_back
in a way consistent with STL conventions.
.SCORE-HERE 2
.LI
Define the four members which would otherwise be supplied as
default members.
.SCORE-HERE 2
.LE
.SP 10i
.LI
Using a
.V= typedef ,
define a type
.V= mathfn
that is a pointer to a function with a single
.V= double
argument and which returns a single
.V= double
result.
Declare a 
.V= map
with
.V= string
keys and
.V= mathfn
values.
Use assignment statements to load the functions
.V= log ,
.V= sqrt ,
and
.V= sin
into the table with keys that spell their names.
.SCORE-HERE 2
.SP 1.25i
.LI
Referring to class
.V= queue
from the previous page,
code the function
.V= push_back
as it would appear in the implementation
.=V ( cpp )
file.
.SCORE-HERE 3
.SP 1.5i
.LI
Write a function which will find the lexicographically least
string in a vector of strings.
Return an iterator pointing at that string.
If the vector is empty,
return the end iterator.
If the smallest string occurs more than once,
you may return an iterator pointing at any of them.
.SCORE-HERE 3
.DS
.ft CB
vector<string>::iterator least (
   vector<string>::const_iterator begin,
   vector<string>::const_iterator end) {
.DE
.SP 2i
.LI
Complete the following beginning of a program so that
all of the command line arguments, but not the program name,
are pushed onto a vector in the same order as they appear on
the command line.
.SCORE-HERE 2
.DS
.ft CB
int main (int argc, char **argv) {
   vector<string> argvec;
.DE
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
What is the way to stop an iterator loop for all iterators
in the following 
.V= for
statement\(??
What goes in the blank\(??
.VTCODE* 0 "for (i = c.begin(); \l'.25i' ; ++i)"
.CHOOSE4V "i == c.end()" "i != c.end()" "i < c.end()" "i > c.end()"
.CHOOSE-END
.CHOOSE-BEGIN
If a vector has 10 elements,
.V= v.end()
is effectively the address of\(::
.CHOOSE4V v[-1] v[0] v[9] v[10]
.CHOOSE-END
.CHOOSE-BEGIN
The most efficient way to increment an iterator\(::
.CHOOSE4V ++i i++ i=1+i i=i+1
.CHOOSE-END
.CHOOSE-BEGIN
Which is a copy constructor\(??
.CHOOSE4V "foo (const foo &);" "foo (foo &);" "foo (const foo);" \
"foo (foo);"
.CHOOSE-END
.CHOOSE-BEGIN
A search of a
.V= std::map
is done in how much time\(??
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( log sub 2 n ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n log sub 2 n ) $
.CHOOSE-END
.ne 2i
.CHOOSE-BEGIN
Given class
.V= foo
has a field
.V= bar\~x ,
what is the most efficient way to write a constructor\(??
.CHOOSE4V "foo (const bar &y) { x (y); }" \
"foo (const bar &y) { x = y; }" \
"foo (const bar &y): x (y) {}" \
"foo (const bar &y): y = x {}"
.CHOOSE-END
.CHOOSE-BEGIN
A single-argument constructor that should not be available 
as an implicit conversion operator is preceded by what keyword\(??
.CHOOSE4V delete explicit override virtual
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= p
is a pointer or a direct-access iterator,
and
.V= n
is an integer,
which one of the following operations is illegal\(??
.CHOOSE4V n\~-\~n n\~-\~p p\~-\~n p\~-\~p
.CHOOSE-END
.CHOOSE-BEGIN
In the absence of any other considerations,
what is the most efficient way to pass an object of
most classes\(??
.CHOOSE4V "void f (foo_t);" "void f (foo_t &);" \
"void f (const foo_t);" "void f (const foo_t &);"
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following is the definition of a destructor\(??
.CHOOSE4V \[ti]foo(){} foo\[ti](){} foo()\[ti]{} foo(){}\[ti]
.CHOOSE-END
.CHOOSE-BEGIN
.PS
.sp -2
linethick=2
G: "\f[CB]\s[+12]\v'3p'goto\v'-3p'\s[-12]\f[R]"
C: circle rad .3 outline "red" at G
line outline "red" from C.nw to C.se 
.PE
.in \n[li*tind]u
.sp -.5v
.CHOOSE4 "Edsger Dijkstra" "Donald Knuth" "Bjarne Stroustrup" \
"Andrew Tanenbaum"
.CHOOSE-END
.LE
.FINISH
