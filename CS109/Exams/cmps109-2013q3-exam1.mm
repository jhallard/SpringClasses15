.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Summer\~2013 Test\~#1
.RCS "$Id: cmps109-2013q3-exam1.mm,v 1.37 2013-07-17 16:54:10-07 - - $"
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
tdefine suchthat "{type relation |}"
.EN
.de LIQ
.   LI
..
.ALX 1 . 4
.LI
Given class
.V= foo ,
write out the prototypes of the four C++98 members that are
automatically defined.
.SCORE-HERE 2
.VTCODE* 0 "class foo {"
.SP .75i
.LI
Given the declaration
.VTCODE* 1 "vector<int> vec;"
assume it was filled with data,
write a
.V= for -loop
which uses a
.V= vector<int>::const_iterator
to print out all of the integers one per line.
.SCORE-HERE 2
.SP 1i
.LI
Write a complete function which will print out all of the
key and value pairs in a
.V= map<string,string> .
Print each pair, one per line, with the key first, then a space,
then the value associated with that key.
.SCORE-HERE 3
.DS
.ft CB
typedef map<string,string> mapss;
void print_mapss (const mapss &themap) {
.DE
.SP 1i
.LI
Write a function to compute the inner product of two vectors of doubles.
The inner product is the sum of pairwise products of correstponding
elements of each vector.
The mathematical formula for this is given in the box at left.
Throw the exception
.V= length_error
if the arrays have different lengths.
.SCORE-HERE 3
.DS
.TS
tab(|); |l| lfCB.
_|
T{
.SP .5v
.EQ
p = sum from { i = 0 } to { n - 1 } a sub i b sub i
.EN
.SP .5v
T}|T{
double inner_prod (const vector<double> &a, const vector<double> &b) {
T}
_|
.TE
.DE
.SP 10i
.LI
Write a function 
.V= list_to_vector ,
which accepts two iterators over a list as arguments,
and which copies all approved elements of the list into the vector,
maintaining the same order.
An approved element is one for which the predicate passed in as
the third argument,
when applied to an element of the list,
returns true.
Hint\(::
append to a vector with
.V= push_back .
.SCORE-HERE 3
.DS
.ft CB
typedef bool (*predicate) (const string &);
typedef list<string>::const_iterator list_citor;
vector<string> list_to_vector (const list_citor &begin,
                              const list_citor &end,
                              predicate approved) {
.DE
.SP 1.5i
.LI
Write a program to read words from
.V= cin ,
and using a
.V= map<string,int> ,
count the number of times each word appears.
At end of file,
print out each word, one per line in lexicographic order,
followed by the number of times the word occurred.
If you declare
.V= "string word" ,
then the loop
.V= "while (cin >> word)"
will skip white space and read in one word each time it is executed.
The loop stops at end of file.
.SCORE-HERE 4
.DS
.ft CB
#include <iostream>
#include <cstdlib>
using namespace std;
.DE
.SP 1.5i
.LI
Define a class
.V= intstack
which holds a stack of integers.
It uses a single private field of type
.V= vector<int>
and has no pointers in the class.
Code all functions as inline functions that do nothing
more than forward the operation to the vector.
Implement the following functions\(::
.SCORE-HERE 3
.ALX a () "" 0
.LI
.V= push
pushes a new element onto the end of the vector.
It uses vector's
.V= push_back .
.LI
.V= pop
removes an element from the end of the vector and returns it.
It uses vector's
.V= back
and
.V= pop_back .
If
.V= pop
is called on an empty stack,
it throws an
.V= out_of_range
exception.
.LI
.V= empty
returns a
.V= bool
indicating the result of the vector's
.V= empty
function.
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
Given the iterators over some container
.V= c ,
where
.V= "b=c.begin()"
and
.V= "e=c.end()" ,
what will be true for an empty container\(??
.CHOOSE4V "b < e" "b == e" "b == e + 1" "b == e - 1"
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= "i=c.begin()"
what is the most efficient way to move the iterator
.V= i
toward
.V= c.end() \(??
.CHOOSE4V ++i --i i++ i--
.CHOOSE-END
.CHOOSE-BEGIN
The idea of an iterator is based on a half-open interval
$ [ a , b ) $,
which refers to what set\(??
.CHOOSE
$ roman "{" x suchthat a < x < b roman "}" $
.CHOOSE
$ roman "{" x suchthat a < x <= b roman "}" $
.CHOOSE
$ roman "{" x suchthat a <= x < b roman "}" $
.CHOOSE
$ roman "{" x suchthat a <= x <= b roman "}" $
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= i
is a
.V= map<string,string>::const_iterator ,
returned by
.V= map::find ,
what expression will yield the value\(??
.CHOOSE4V (*i)->second i->*second i->second i.second
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following definitions of
.V= f
will cause a copy of its argument of class
.V= T
to be made\(??
.CHOOSE4V "void f (T &&x);" "void f (T &x);" "void f (T *x);" \
"void f (T x);"
.CHOOSE-END
.CHOOSE-BEGIN
What keyword is used in a statement that will permit one class
to see the private members of another class\(??
.CHOOSE4V explicit friend inline operator
.CHOOSE-END
.CHOOSE-BEGIN
Which operator uses lazy evaluation\(??
.CHOOSE4V ++ << == ||
.CHOOSE-END
.CHOOSE-BEGIN
What should be the first non-comment line in 
.V= foo.h \(??
.CHOOSE4V "#define __FOO_H__" "#ifndef __FOO_H__" \
"#include \[Dq]foo.h\[Dq]" "class foo {"
.CHOOSE-END
.CHOOSE-BEGIN
Given a class outlined as follows
.VTCODE* 0 "class foo {"
.VTCODE* 0 "  private: string s;"
.VTCODE* 0 "  public: foo (const bar &);"
.VTCODE* 0 "};"
What is the most efficient way to implement a constructor\(??
.CHOOSE4V \
"foo::foo (const bar &x) { s = x; }" \
"foo::foo (const bar &x): s(x) {}" \
"void foo (const bar &x): s(x) {}" \
"void foo::foo (const bar &x) { s = x; }"
.CHOOSE-END
.CHOOSE-BEGIN
For class
.V= node ,
what is the correct way to declare a pointer
.V= p
to point at a
.V= node ,
and to allocate a node on the heap\(??
.CHOOSE4V "node &p = new node();" "node *p = &new node[];" \
"node *p = new node();" "node p = new node();"
.CHOOSE-END
.CHOOSE-BEGIN
For
.V= "int a"
and
.V= "int b"
if we want to swap them using the call
.V= swap(a,b) ,
what is the prototype for 
.V= swap \(??
.CHOOSE4V "void swap (auto a, auto b);" "void swap (int &a, int &b);" \
"void swap (int *a, int *b);" "void swap (int a, int b);"
.CHOOSE-END
.LE
.FINISH
