.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Spring\~2015 Test\~#1
.RCS "$Id: cmps109-2015q2-exam1.mm,v 1.42 2015-04-21 15:15:09-07 - - $"
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
Given
.V= "vector<string> v;" 
\[em]
You may use
.V= auto .
.ALX a () "" 0
.LI
Using the colon (foreach) form of the for loop,
write out each element of the vector, one item per line.
.SCORE-HERE 1
.SP .7i
.LI
Using iterators explicitly, using the two-semicolon form of the
for loop,
write out each element of the vector, one item per line.
.SCORE-HERE 1
.SP .7i
.LE
.LI
Finish the function 
.V= sum ,
which sums all of the elements in the range given by a pair of
forward iterators.
Assume the iterators point at 
.V= double s.
.SCORE-HERE 2
.DS
.ft CB
template <typename Iterator>
double sum (Iterator begin, Iterator end) {
.DE
.SP .7i
.LI 
Define an 
.V= operator<<
so that the statements on the left will print out the word
.V= false
or  
.V= true ,
as appropriate.
Assume the library does
.E= not 
have an operator which will do this.
.SCORE-HERE 2
.DS
.TS
tab(|); lfCB |lfCB.
// Sample code|// Operator definition
bool b; 
cout << " b = " << b << endl;
.SP .5i
.TE
.DE
.LI
Write a
.V= using 
statement which defines a data type called
.V= mathfn ,
which is a pointer to a function whose argument is a
.V= double
by value,
and which returns a result of type
.V= double.
Write a declaration for an
.V= unordered_map
named
.V= functions
whose 
.V= key_type s
are
.V= string s
and whose
.V= mapped_type s
are 
.V= mathfn s.
.SCORE-HERE 2
.SP .75i
.LI
Write a loop (not a complete function or program)
which will read 
.V= double s
from 
.V= cin
until end of file and put them in a
.V= vector
in the same order that they appeared on an input file.
Hint\(::
.V= cin>>d
will read a
.V= double 
into the variable
.V= d
and return true if it succeeded and false if not.
.SCORE-HERE 2
.DS
.ft CB
vector<double> v;
double d;
.DE
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
Define the ctor inline in the header. 
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
Complete
.V= operator<
for a name.
One name is less than the other if the last name
is less than the other's last name.
If the last names are equal,
first names are compared.
Your implementation may only use
.V= string::operator< 
as the only comparison operator.
.SCORE-HERE 2
.DS
.ft CB
struct name {
   string last;
   string first;
   bool operator< (const name& that) {
.DE
.SP .5i
.LI
Finish the definitions of the members of
.V= vec
and
.V= vec::iterator
as appropriate, making them all inline.
The following code must work given your code\(::
.VTCODE 1 "vec<int,10> v;"
.V= "for (auto i = v.begin(); i != v.end(); ++i) f(*i);"
.br
Assume that
.V= f
and any initializations have been done elsewhere.
This is not a complete implementation.
In order to be useable (outside the scope of this test),
many more functions would have to be added.
.ALX a () "" 0
.LI
Code the inline operators unary
.V= operator* ,
prefix unary
.V= operator++ ,
and binary
.V= operator!=
for the iterator.
Also code the iterator constructor which takes a
.V= T*
as an argument.
.SCORE-HERE 4
.LI
Code the
.V= vec
functions
.V= begin
and
.V= end .
.SCORE-HERE 1
.LE
.DS
.ft CB
template <typename T, size_t N>
struct vec {
   private: T data[N];
   public:
      class iterator {
         private: T* curr;
         public:
            // Code the ctor and operators *, ++, != here.
.SP .8i
      };
      // Code begin and end here.
.SP .2i
};
.DE
.LI
Write a function
.V= smallest
which returns an iterator pointing at the smallest element
of a range given by a pair of iterators.
Assume the elements have
.V= operator<
defined.
If there is more than one ``smallest'' element,
return the first one.
Return what would normally be expected if the range is empty.
.SCORE-HERE 2
.DS
.ft CB
template <typename Iterator>
Iterator smallest (Iterator begin, Iterator end) {
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
The last line of
.V= operator=
should be\(::
.CHOOSE4V return\~*auto; return\~*this; return\~nullptr; return\~this;
.CHOOSE-END
.CHOOSE-BEGIN
Which C++11 standard library class uses
reference counting to manage memory\(??
.CHOOSE4V T* auto_ptr<T> shared_ptr<T> unique_ptr<T>
.CHOOSE-END
.CHOOSE-BEGIN
For a raw vector
.V= int\~a[10]; ,
what is the equivalent to
.V= a.end() ,
if
.V= int[]
were a class\(??
.CHOOSE4V &a[0] &a[10] &a[11] &a[9]
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following does not need to move objects in the container
when adding an arbitrary number of new elements,
but still can access individual elements in $O ( 1 ) $ time\(??
.CHOOSE4V deque list map vector
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following containers uses a balanced binary search tree\(??
.CHOOSE4V deque forward_list map unordered_map
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= "string s;"
and
.V= "string t;"
which will compare their addresses, not values\(??
.CHOOSE4V "&&s == &&t" "&s == &t" "*s == *t" "s == t"
.CHOOSE-END
.CHOOSE-BEGIN
Inside class
.V= foo ,
a move constructor's prototype is\(::
.CHOOSE4V "foo (const foo&&);" "foo (const foo&);" "foo (foo&&);" \
"foo (foo&);"
.CHOOSE-END
.CHOOSE-BEGIN
What declares the postfix
.V= operator++
as a non-member of class
.V= foo \(??
.CHOOSE4V "foo operator++ ();" "foo operator++ (foo&);" \
"foo operator++ (foo&, int);" "foo operator++ (int);"
.CHOOSE-END
.CHOOSE-BEGIN
After the library includes in a C++ program,
what statement is usually used\(??
.CHOOSE4V "#include <namespace/std>" "explicit namespace std;" \
"import namespace std;" "using namespace std;"
.CHOOSE-END
.CHOOSE-BEGIN
A constructor may be used implicitly as an automatic conversion
operator.
To prevent this, what keyword is used\(??
.CHOOSE4V default delete explicit implicit
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
Which of the following operators is most usually declared
as a friend, not as a member\(??
.CHOOSE4V operator+ operator+= operator< operator<<
.CHOOSE-END
.LE
.if dPSPIC \{
.PSPIC -I -.35i jpgs/code_quality.ps 4.1i
.\}
.FINISH
