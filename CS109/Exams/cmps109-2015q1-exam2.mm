.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Winter\~2015 Test\~#2
.RCS "$Id: cmps109-2015q1-exam2.mm,v 1.47 2015-02-20 17:15:19-08 - - $"
.DS
.PS
examboxes(3)
.PE
.DE
.P
.ft BI
Code only in C++11.
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
.ALX 1 . 3
.LI
Rewrite the following statement by using the two-semicolon version
of the
.V= for -loop,
i.e., by using iterators explicitly\(::
\0\0\0\0
.BOX "\f[CB]\0for (auto i&: c) f(i);\0\f[P]"
\0\0\0\0
.SCORE-HERE 1
.SP .5i
.LI
Define the template
.V= operator<<
whose second argument is a constant reference to a
.V= pair .
It has two template arguments which give the type of the
.V= first
and
.V= second
fields.
It prints out a left brace
.=V ( { ),
then the first of the pair,
then a comma
.=V ( , ),
then the second of the pair,
then a right brace
.=V ( } ).
Example\(::
a
.V= pair<int,int> 
would look like
.V= {3,4} .
.SCORE-HERE 2
.DS
.ft CB
template <typename First, typename Second>
.SP .85i
.DE
.LI
A hash map full of math functions and evaluation.
.ALX a () "" 0
.LI
Write two
.V= using
statements\(::
Define
.V= mathfn
as a pointer to a function taking a 
.V= double
argument and returning a
.V= double
result.
Define 
.V= fnmap
as an 
.V= unordered_map
whose keys are
.V= string s
and whose values are
.V= mathfn s.
.SCORE-HERE 1
.SP .3i
.LI
Define the function
.V= evalfn ,
which returns a
.V= double
result.
Its arguments are a
.V= fnmap ,
a
.V= string 
representing a function name, and a
.V= double
value.
The first two arguments are passed by constant reference.
It looks up the function by name in the map.
If found, it applies the function to the double argument and
returns the result.
If not found, it returns
.V= numeric_limits<double>::quiet_NaN() .
.SCORE-HERE 2
.LE
.SP .85i
.LI
Define the function
.V= lenless
so that the following statement\(::
.VTCODE* 1 "sort (args.begin(), args.end(), lenless);"
will sort
.V= "vector<string> args"
in such a way that shorter strings come before longer strings
(use
.V= size() ).
Strings of the same length are sorted lexicographically.
.SCORE-HERE 2
.SP .85i
.LI
Define the function
.V= find
which takes a pair of iterators and a key,
and performs a linear search for the first item in the iterator
range that is equal 
to the key.
.SCORE-HERE 2
.VTCODE* 0 "template <typename Itor, typename Key>"
.VTCODE* 0 "Itor find (Itor begin, Itor end, Key key) {"
.SP 10i
.LI
Given a pair of forward iterators specifying one range and another
pair specifying a second range,
.V= push_back
each pair onto a container.
For example, if one input has
.V= {1,2}
and the other has
.V= {'a','b'} ,
then the pairs to be pushed would be
.V= {{1,'a'},{2,'b'}} .
Stop pushing pairs when one or the other ranges is exhausted.
After pushing pairs, if both ranges are not exhausted, throw a
.V= length_error .
The template function
.V= make_pair
can create a pair object.
.SCORE-HERE 3
.DS
.ft CB
template <typename Itor1, typename Itor2, typename Container>
void zip (Itor1 b1, Itor1 e1, Itor2 b2, Itor2 e2, Container& out) {
.SP 1i
.DE
.LI
Define the function
.V= monotonic
which returns true if its elements are monotonically increasing
according to the binary functional parameter.
Its arguments are a pair of iterators and a binary function.
For example, 
.VTCODE* 1 "monotonic (v.begin(), v.end(), less<int>())"
will return true if the range is increasing.
It would return true for a monotonically decreasing function if
passed
.V= greater<int>
instead.
Monotonically increasing means that each element is larger than
the one before it.
An empty sequence or a sequence of one element is always monotonically
increasing.
.SCORE-HERE 3
.DS
.ft CB
template <typename Itor, typename Function>
bool monotonic (Itor begin, Itor end, Function fn) {
.DE
.SP 1i
.LI
Define the class
.V= ivec::iterator
as outlined here\(::
.ALX a () "" 0
.LI
Code all members of 
.V= iterator 
inline,
and code only those functions needed by the following statement:
.VTCODE* 1 \
"for (auto i = vec.begin(); i != vec.end(); ++i) cout << *i << endl;"
and also the constructor neede by
.V= begin
and
.V= end .
.SCORE-HERE 3
.LI
Also show the code for the functions
.V= ivec::begin()
and
.V= ivec::end() .
.SCORE-HERE 1
.DS
.ft CB
struct ivec {
   size_t size;
   int *data;
   struct iterator{
      int *curr;
      // Code ivec::iterator ctor and members here.
.SP 1.5i
   };
   // Code ivec::begin and ivec::end here.
.DE
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
.nr MULTCHOICE_MAX 12
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
What is the signature of the implicitly generated
move assignment operator as it would appear inside class
.V= foo \(??
.CHOOSE4V "foo operator= (const foo&&);" "foo operator= (foo&&);" \
"foo& operator= (const foo&&);" "foo& operator= (foo&&);"
.CHOOSE-END
.CHOOSE-BEGIN
What kind of a cast would be used to make a
.V= size_t
from a pointer\(??
.CHOOSE4V const_cast dynamic_cast reinterpret_cast static_cast
.CHOOSE-END
.CHOOSE-BEGIN
Which class allows $O ( 1 )$ insertions at both ends of the sequence
of elements and also allows $O ( 1 )$ access to any arbitrary element
given its index\(??
.CHOOSE4V std::deque std::list std::stack std::vector
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= vs
is a 
.V= vector<string> ,
what expression can be used to print out its first element\(??
.CHOOSE4V cout<<**vs.begin() cout<<*vs.begin() cout<<vs.*begin() \
cout<<vs.begin()
.CHOOSE-END
.CHOOSE-BEGIN
Given the following declarations,
which assignments are neither errors nor will cause slicing\(??
.VTCODE* 0 "class foo {};"
.VTCODE* 0 "class bar: public foo {};"
.VTCODE* 0 "foo *f; bar *b;"
.CHOOSE4V "*b = *f;" "*f = *b;" "b = f;" "f = b;"
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= i
and
.V= j
are iterators and
.V= n
is an 
.V= int ,
which of the following is possible for a direct access iterator
but not for a forward iterator\(??
.CHOOSE4V *i ++i i!=j i[n]
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following are C++ operators that can be declared with any
number of arguments\(??
.CHOOSE4V operator() operator<> operator[] operator{}
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following kinds of data members will make the implicitly
generated
.V= operator=
inappropriate\(??
.CHOOSE4V pointer primitive reference string
.CHOOSE-END
.CHOOSE-BEGIN
The constructors for an abstract class should usually be classified
as\(::
.CHOOSE4V private protected public friend
.CHOOSE-END
.CHOOSE-BEGIN
Unless otherwise specified,
members of a class are [x] and members of a
struct are [y].
.CHOOSE
[x] = private, [y] = private.
.CHOOSE
[x] = private, [y] = public.
.CHOOSE
[x] = public, [y] = private.
.CHOOSE
[x] = public, [y] = public.
.CHOOSE-END
.CHOOSE-BEGIN
In a
.V= Makefile ,
what variable should fill in the blank\(??
.VTCODE* 0 "%.o : %.cpp"
.VTCODE* 0 "\0\0\0\0\0\0\0\0\[Do]{COMPILECPP} -c \l'10p'
.CHOOSE4V \[Do]< \[Do]? \[Do]@ \[Do]_
.CHOOSE-END
.CHOOSE-BEGIN
What is the correct syntax to define an abstract virtual function\(??
.CHOOSE4V "virtual void show() = 0;" "virtual void show() = delete;" \
"virtual void show() = abstract;" "virtual void show() = override;"
.CHOOSE-END
.LE
.FINISH
