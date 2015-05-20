.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Spring\~2014 Test\~#2
.RCS "$Id: cmps109-2014q2-exam2.mm,v 1.24 2014-05-13 19:17:22-07 - - $"
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
.ALX 1
.LI
Code the function
.V= merge .
It takes a pair of iterators bounding one sorted input range,
and another pair of iterators bounding another sorted input range.
It has an iterator pointing at an output range,
which is assumed to be large enough.
It also takes a comparison function.
It copies elements from the input containers into the output
container so that it is sorted.
Example\(::
.VTCODE* 1 "merge (a.begin(), a.end(), b.begin(), b.end(), \
c.begin(), less<int>());"
will merge
.V= vector<int>a
and
.V= vector<int>b
into 
.V= vector<int>c
using
.V= less<int> .
.SCORE-HERE 4
.DS
.ft CB
template <typename iter, typename oiter, typename Less>
void merge (iter b1, iter e1, iter b2, iter e2, oiter ob, Less less) { 
.DE
.SP 1.5i
.LI
Define a complex number as a
.V= struct
so that all members are public.
It contains the following\(::
.ALX i () "" 0
.LI
Two
.V= double
fields,
.V= real
and
.V= imag ,
whose default values are explicitly set to 0.0.
.SCORE-HERE 1
.LI
A constructor which automatically converts a 
.V= double
to a complex number with a 0.0 imaginary part.
.SCORE-HERE 1
.LI
A constructor which accepts two
.V= double s .
.SCORE-HERE 1
.LI
The member function binary
.V= operator+ .
.SCORE-HERE 1
.LI
The member function binary
.V= operator+= .
.SCORE-HERE 1
.LI
The non-member function
.V= operator<< ,
which will write out a number, as in, for example,
.V= (3.8,4.2i) ,
i.e., both parts of the number in parentheses as shown here.
.SCORE-HERE 1
.LE
Code all functions as inline functions as they might appear in
a header file.
.SP 10i
.LI
Write a function
.V= execute
which will take a map argument and a string argument,
and look up the function in the map.
If the function is found, call it.
If not, print an error message.
.SCORE-HERE 2
.DS
.ft CB
typedef map<string, void(*)()> funmap;
void execute (const funmap& map, const string& key) {
.DE
.SP .85i
.LI
Write the function 
.V= accumulate
which takes a pair of iterators,
an identity element,
and a function,
and uses the function to accumulate a result.
Example\(::
.VTCODE* 1 "int s = accumulate (v.begin(), v.end(), 0, add);"
.VTCODE* 1 "int p = accumulate (v.begin(), v.end(), 1, mul);"
will find the sum and product of all elements of 
.V= v .
.SCORE-HERE 2
.DS
.ft CB
template <typename T, typename itor>
T accumulate (itor begin, itor end, T identity, T(*f)(T,T)) {
.DE
.SP .85i
.LI
Write a function which accepts an
.V= ostream
and a pair of iterators and prints out each element specified
by the range,
with a space between each element, 
but not before the first or after the last.
.SCORE-HERE 2
.DS
.ft CB
template <typename iterator>
void print (ostream& out, iterator begin, iterator end) {
.DE
.SP .85i
.LI
Write a function called
.V= filter
that takes a 
.V= vector<string>
as an argument and returns another vector containing only
those elements for which the predicate is true.
.SCORE-HERE 2
.DS
.ft CB
typedef bool (*predicate) (const string&);
vector<string> filter (const vector<string>& v, predicate p) {
.DE
.SP .85i
.LI
Given the beginning of a program as shown here,
write code to declare
.V= vector<string>\~ args
which is initialized to the elements of
.V= argv
from 1 to
.V= argc\~-\~1 ,
i.e.,
all of the command line arguments other than the program name.
.SCORE-HERE 2
.DS
.ft CB
int main (int argc, char** argv) {
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
Which of the following will permit the fastest search for a key\(??
.CHOOSE4V list map unordered_map vector
.CHOOSE-END
.CHOOSE-BEGIN
The class
.V= shared_ptr
makes use of what method of memory management\(??
.CHOOSE
Copying collection with semispaces.
.CHOOSE
Dangling pointers.
.CHOOSE
Mark and sweep garbage collection.
.CHOOSE
Reference counting.
.CHOOSE-END
.CHOOSE-BEGIN
In an object-oriented hierarchy,
how is a function marked in such a way as to require
that it must be overridden in a derived class\(??
.CHOOSE4V =\~0 =\~abstract =\~delete =\~virtual
.CHOOSE-END
.CHOOSE-BEGIN
What kind of cast can be used to move the bits in a pointer
to the bits in a
.V= unsigned\~long \(??
.CHOOSE4V const_cast dynamic_cast reinterpret_cast static_cast
.CHOOSE-END
.CHOOSE-BEGIN
What is the type of the expression
.V= sizeof(vector<int>) \(??
.CHOOSE4V float int int64_t size_t
.CHOOSE-END
.CHOOSE-BEGIN
In the absence of the keywords
.V= private ,
.V= protected ,
or
.V= public ,
members of a 
.V= class
are __(x)__,
and members of a
.V= struct
are __(y)__.
.CHOOSE
(x) = private, (y) = private
.CHOOSE
(x) = private, (y) = public
.CHOOSE
(x) = public, (y) = private
.CHOOSE
(x) = public, (y) = public
.CHOOSE-END
.CHOOSE-BEGIN
Which data structure is specified as using a contiguous block
of heap memory\(??
.CHOOSE4V deque list map vector
.CHOOSE-END
.CHOOSE-BEGIN
For
.V= vector<int>\~v \(::
.CHOOSE4V "v.size()==v.end()+v.begin()" \
"v.size()==v.end()-v.begin()+1" \
"v.size()==v.end()-v.begin()-1" \
"v.size()==v.end()-v.begin()"
.CHOOSE-END
.CHOOSE-BEGIN
Which concept is most closely related to object-oriented programming\(??
.CHOOSE4 conversion inheritance overloading templates
.CHOOSE-END
.CHOOSE-BEGIN
The idea of an iterator is based on a half-open interval
$ [ a , b ) $,
which refers to what set\(?? 
.CHOOSE 
$ roman "{" ~ x suchthat a < x < b ~ roman "}" $
.CHOOSE 
$ roman "{" ~ x suchthat a < x <= b ~ roman "}" $
.CHOOSE 
$ roman "{" ~ x suchthat a <= x < b ~ roman "}" $
.CHOOSE 
$ roman "{" ~ x suchthat a <= x <= b ~ roman "}" $
.CHOOSE-END
.CHOOSE-BEGIN
After searching a map with the following statement,
what statement can be used to print
the value associated with the key\(??
.VTCODE* 1 "auto& i = m.find (key);
.CHOOSE4V "cout << (*i)->second;" "cout << i->second;" \
"cout << i.second;" "cout << i;"
.CHOOSE-END
.CHOOSE-BEGIN
If a base class
.V= foo
is declared to have virtual functions
and is involved in inheritance,
what other member of the class must be virtual\(??
.CHOOSE4 "all other function members" copy\~constructor \
destructor \f[CB]operator<<\f[P]
.CHOOSE-END
.LE
.FINISH
