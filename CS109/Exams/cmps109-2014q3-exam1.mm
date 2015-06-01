.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Summer\~2014 Midterm\~Exam
.RCS "$Id: cmps109-2014q3-exam1.mm,v 1.39 2014-07-16 17:48:46-07 - - $"
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
Load the command line arguments (but not the program name)
into a
.V= vector<string> .
Just show the necessary code after the opening line of
.V= main .
.SCORE-HERE 1
.DS
.ft CB
int main (int argc, char** argv) {
.DE
.SP .5i
.LI
For class
.V= foo ,
write the prototypes for the six members that are automatically
synthesized by the compiler.
.SCORE-HERE 3
.DS
.ft CB
class foo {
.DE
.SP 1i
.LI
Write the function
.V= sum
that would return the sum of all elements in a range,
given a pair of iterators that indicate the range in the usual way.
Assume a dereferenced iterator returns a
.V= double .
.SCORE-HERE 2
.DS
.ft CB
template <typename Iterator>
double sum (Iterator begin, Iterator end) {
.DE
.SP 1i
.LI
Define a template class
.V= stack ,
which contains (does not inherit) a private
.V= vector .
It supports the operations
.V= push ,
.V= pop ,
.V= top ,
.V= size ,
and
.V= empty .
Code all functions inline,
using bodies which just call the appropriate
.V= vector
function.
Show everything that should be in the header file
.V= stack.h
so that no implementation file
.V= stack.cpp
is needed.
Be consistent with the rest of the library.
.SCORE-HERE 4
.SP 10i
.LI
Define a single constructor for class
.V= complex
which takes zero, one, or two arguments.
For zero arguments, both fields are initialized to 0.0.
For a single argument, the real field is initialized to its value,
and the imaginary field to 0.0.
For two arguments, the real field's value is the first argument,
and the imaginary field's value is the second argument.
Define the function entirely in the header.
.SCORE-HERE 1
.DS
.ft CB
class complex:
   private:
      double real;
      double imag;
   public:
      complex (
.DE
.LI
Write a function that finds the smallest entry in a range
given by a pair of iterators.
.V= operator<
is used to determine what is smallest.
If the range is empty,
return the end of the range.
If there are several smallest value,
return the one nearest the start of the range.
.SCORE-HERE 2
.DS
.ft CB
using Itor = vector<string>::const_iterator;
Itor smallest (Itor begin, Itor end) {
.DE
.SP 1i
.LI
Write a
.V= copy
function.
It takes a pair of iterators delimiting a input range,
and an object with a
.V= push_back
function.
It copies values from the input range and pushes each item thus
found onto the back of the output object.
.SCORE-HERE 3
.DS
.ft CB
template <typename Iterator, typename Container>
void copy (Iterator begin, Iterator end, Container& cont) {
.DE
.SP 1i
.LI
Using the colon (foreach) form of a
.V= for- loop,
print out the key and value pairs of a map,
one key/value pair per line.
.SCORE-HERE 2
.DS
.ft CB
map<string,int> si_map;
.SP
for (\h'2i': si_map) {
.DE
.SP .8i
.LI
Write a loop which loads a map from
.V= argv ,
using all of the arguments except the name of the program,
such that for all
.V= i ,
.V= argv[i]
is a key with the value
.V= i .
.SCORE-HERE 2
.DS
.ft CB
int main (int argc, char** argv) {
   map<string,int> si_map;
.DE
.SP 10i
.LI
Write a function 
.V= trim
which takes a 
.V= vector<char>
and removes all high-order zeros from the end of the vector.
That is,
it pops zeros from the end of the vector until the last
element of the vector is non-zero,
or the vector is empty.
Note that the value 0 is being popped, not
.V= '0' .
.SCORE-HERE 2
.DS
.ft CB
void trim (vector<char> vec) {
.DE
.SP .9i
.LI
Write a function
.V= split ,
which takes a vector as an argument and splits the vector
into two alternating output vectors with the even-numbered
elements in the first vector and the odd-numbered elements in
the second vector.
For example, 
.V= "split ({1,3,5,7,9,11,15,20,30,55})"
will return 
.V= "{1,5,9,15,30}"
as the first of the pair and
.V= "{3,7,11,20,55}"
as the second pair.
In other words there are two resulting vectors,
each containing alternating elements from the input vector.
.SCORE-HERE 4
.DS
.ft CB
using intvec = vector<int>;
using vecpair = pair<intvec,intvec>;
vecpair split (const intvec& vec) {
.DE
.SP 1.9i
.LI
Assuming the declarations presented here,
write a function
.V= execute
which takes an input line string\(::
.SCORE-HERE 4
.ALX i () "" 0
.LI
Using
.V= split ,
splits it into a vector of words,
assuming that
.V= split
splits on white space.
.LI
The first word is the function name,
which is found in a map.
.LI
The function is then called with a pair of iterators,
the first of which points at the second word in the vector,
and the second of which is the end of the vector.
.LI
Throw the exception
.V= bad_command
either if there are no words on the command line or
if the command is not found in the map.
.LE
.DS
.ft CB
using itor = vector<string>::const_iterator;
using function = void (*) (itor begin, itor end);
class bad_command: public exception {};
vector<string> split (const string&);
unordered_map<string,function> fnmap;
void execute (const string& command) {
.DE
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
The area of memory used for dynamic memory allocation is the\(::
.CHOOSE4V function\~call\~stack heap static\~data text\~area
.CHOOSE-END
.CHOOSE-BEGIN
The copy constructor for class
.V= foo ,
defined in a header file,
will look like\(::
.CHOOSE4V "foo (const foo&&);" "foo (const foo&);" "foo (foo&&);" \
"foo (foo&);"
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following declarations will produce a warning\(??
.CHOOSE
.V= "int a (3.6);"
// Note\(::
parentheses.
.CHOOSE
.V= "int b = 3.6;"
.CHOOSE
.V= "int c {3.6};"
// Note\(::
braces.
.CHOOSE
.V= "int d {};"
// Note\(::
braces.
.CHOOSE-END
.CHOOSE-BEGIN
In the following statements,
what is the type of
.V= n \(??
.VTCODE* 0 "vector<int> vi;
.VTCODE* 0 "auto n = vi.begin();
.CHOOSE4V vector::iterator vector::iterator<int> \
vector<int>::iterator vector<int>::reverse_iterator
.CHOOSE-END
.CHOOSE-BEGIN
An ancestor to C++ which used classes was\(::
.CHOOSE4 Algol Fortran Lisp Simula
.CHOOSE-END
.CHOOSE-BEGIN
Which one of these may
.E= not
be used as an operator in C++\(??
.CHOOSE4V operator() operator-- operator<> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
To prevent the compiler from synthesizing the constructor with
no arguments for class
.V= foo ,
use the definition\(::
.CHOOSE4V "foo() = default;" "foo() = delete;" "foo() override;" \
"virtual foo();"
.CHOOSE-END
.CHOOSE-BEGIN
What class performs memory management by using reference counting\(??
.CHOOSE
.V= auto_ptr<T>
.CHOOSE
.V= shared_ptr<T>
.CHOOSE
.V= unique_ptr<T>
.CHOOSE
None of the above.
Memory management is done by garbage collection.
.CHOOSE-END
.CHOOSE-BEGIN
Storage menagement by reference counting fails on what kind
of data structure\(??
.CHOOSE
binary tree
.CHOOSE
cyclic graph
.CHOOSE
hash table
.CHOOSE
vectors and arrays
.CHOOSE-END
.CHOOSE-BEGIN
In the following,
what statement is executed immediately after
.V= continue \(??
.VTCODE* 0 "for (i = 0; i < n; ++i) {"
.VTCODE* 0 "   f(); continue; g();"
.VTCODE* 0 "} h();
.CHOOSE4V ++i g() h() i<n
.CHOOSE-END
.CHOOSE-BEGIN
The
.V= operator=
assignment operator should always return its object by reference
using the code\(::
.CHOOSE4V return\~*auto; return\~*self; return\~*that; return\~*this;
.CHOOSE-END
.CHOOSE-BEGIN
The keyword
.V= explicit \(::
.CHOOSE
Prevents default members, such as the default copy constructor, from
being automatically provided.
.CHOOSE
Prevents implicit access to the standard input, output, and
error streams.
.CHOOSE
Prevents local variables from being destroyed when they go out of scope.
.CHOOSE
Prevents one-argument constructors from behaving as automatic type
conversions.
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
Which container guarantees that all elements are stored in
a contiguous block of memory\(??
.CHOOSE4V deque list map vector
.CHOOSE-END
.CHOOSE-BEGIN
Which expression is equivalent to
.V= p+i ,
given that
.V= p
is a pointer and
.V= i
is
.V= ssize_t \(??
.CHOOSE4V !p[i] &p[i] *p[i] \[ti]p[i]
.CHOOSE-END
.CHOOSE-BEGIN
Which operator uses lazy evaluation\(??
.CHOOSE4V ++ << == ||
.CHOOSE-END
.CHOOSE-BEGIN
What is the general efficiency of
.V= vector::push_back \(??
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
If
.V= v.size()\~==\~n ,
then
.V= v.end()
usually means\(::
.CHOOSE4V &v[0] &v[n+1] &v[n-1] &v[n]
.CHOOSE-END
.CHOOSE-BEGIN
What statement should free memory that has been
allocated with\(::
.VTCODE* 0 "foo* p = new foo[n];"
.CHOOSE4V "delete p;" "delete* p;" "delete[] p;" "foo::\[ti]foo (p);"
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= m
is a
.V= map ,
then inside the loop
.V= for(auto\~i:m)
we refer to the value associated with a given key by\(::
.CHOOSE4V i->first i->second i.first i.second
.CHOOSE-END
.CHOOSE-BEGIN
What statement will print one of the strings in a vector,
given the following declarations\(??
.VTCODE* 0 "vector<string> v;"
.VTCODE* 0 "auto i = vec.cbegin();"
.CHOOSE4V cout\~<<\~&i; cout\~<<\~**i; cout\~<<\~*i; cout\~<<\~i;
.CHOOSE-END
.CHOOSE-BEGIN
An
.V= unordered_map
is a\(::
.CHOOSE
balanced binary search tree
.CHOOSE
bidirectional linked list
.CHOOSE
hash table
.CHOOSE
lexicographically sorted array
.CHOOSE-END
.CHOOSE-BEGIN
What declaration would normally be expected to allow printing
values of class
.V= foo\(??
.CHOOSE
.V= "ostream& operator<<"
.br
.V= "\0\0\0(const ostream&, const foo&);"
.CHOOSE
.V= "ostream& operator<<"
.br
.V= "\0\0\0(const ostream&, foo&);"
.CHOOSE
.V= "ostream& operator<<"
.br
.V= "\0\0\0(ostream&, const foo&);"
.CHOOSE
.V= "ostream& operator<<"
.br
.V= "\0\0\0(ostream&, foo&);"
.CHOOSE-END
.CHOOSE-BEGIN
The copy constructor and operator=
will have to be explicitly written if a class contains what
kind of field\(??
.CHOOSE4 copiable\~object pointer primitive reference
.CHOOSE-END
.CHOOSE-BEGIN
Which definition defines the
.E= prefix
.V= operator++
(i.e., 
.V= ++x )
when it is a member (not friend) of a class\(??
.CHOOSE4V "foo operator++ (foo&, int);" "foo operator++ (int);" \
"foo& operator++ ();" "foo& operator++ (foo&);"
.CHOOSE-END
.LE
.FINISH
