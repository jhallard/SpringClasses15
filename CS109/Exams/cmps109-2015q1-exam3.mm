.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Winter\~2015 Final\~Exam
.RCS "$Id: cmps109-2015q1-exam3.mm,v 1.90 2015-03-18 18:00:14-07 - - $"
.DS
.PS
examboxes(5)
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
define suchthat "{type relation |}"
.EN
.ALX 1 . 3
.LI
Write the prototypes as they would appear inside the class
.V= foo
declarations for the four implicitly generated members in C++98,
and for the two others that appeared only in C++11.
.SCORE-HERE 2
.DS
.TS
tab(|); |lew(214p)fCB |lefCB |.
_
T{
class foo { // both C++98 and C++11
public:
.SP 4v
};
T}|T{
class foo { // C++11 but not C++98
public:
.SP 4v
};
T}
_
.TE
.DE
.LI
Write the function
.V= blue_triangle ,
which has no parameters,
which will draw a blue triangle with vertices at
$ ( 0 , 0 ) $,
$ ( 4 , 0 ) $,
and
$ ( 4 , 4 ) $.
.SCORE-HERE 3
.SP 1.1i
.LI
Define the template function 
.V= copy .
It has two template arguments, both forward iterator types.
It has four function arguments\(::
begin and end iterators bounding an input sequence,
followed by begin and end iterators bounding an output sequence.
It copies the input sequence to the output sequence.
Assume that the output sequence is large enough.
.SCORE-HERE 2
.SP 1i
.LI
Write a function
.V= zipwith .
It has two template parameters\(::
an arbitrary element type,
and a binary function type.
It has three actual parameters\(::
two vectors of the element type,
passed in by constant reference,
and a pointer to a binary function.
Its result is a vector of the element type.
Elements of the argument types are combined pairwise with the
binary function to produce the output function.
Throw a 
.V= domain_error
if the vectors have different lengths.
For example,
.VTCODE* 1 "vector<int> v1{1,2,3}, v2{4,5,6}, v3;"
.VTCODE* 1 "v3 = zipwith (v1, v2, plus<int>());"
will set
.V= v3
to
.V= {5,7,9} .
.SCORE-HERE 3
.SP 10i
.LI
Define the template class
.V= queue
as it might appear in a header file.
All functions must be declared inline inside the class definition.
All of the implicitly generated members are acceptable and therefore
do not need to be declared.
It has a single private member of type
.V= deque ,
on which the queue is implemented.
Define the following public members with appropriate signatures\(::
.V= clear ,
.V= size ,
.V= empty ,
.V= push_back ,
.V= pop_front ,
and
.V= front .
Each of them simply uses the equivalent
.V= deque
operation.
.SCORE-HERE 4
.SP 2.5i
.LI
Define three classes\(::
.ALX a () "" 0
.LI
The base class is
.V= shape .
It has a single protected constructor of no arguments,
and two parameterless abstract functions
.V= circumference
and
.V= area
which return a
.V= double .
For the mathematically challenged, remember that
$ A = pi r sup 2 $
and
$ C = 2 pi r $.
The header
.V= <cmath>
defines the constant
.V= M_PI .
.SCORE-HERE 2
.SP 1.5i
.LI
Class
.V= circle
inherits from
.V= shape
and has a private field
.V= radius .
It has one constructor which takes a radius argument and
overrides 
.V= circumference
and
.V= area .
.SCORE-HERE 2
.SP 1.5i
.LI
Class
.V= square
inherits from
.V= shape
and has a private field
.V= length ,
which is the length of one edge.
It overrides
.V= circumference
and
.V= area .
.SCORE-HERE 2
.LE
.SP 10i
.LI
Write a function
.V= differentiate
which performs symbolic differentiation on a polynomial.
For example,
.nr old-Ds \n[Ds]
.nr Ds 0
.DS C
.EQ
d over dx  ~ a x sup 3 + b x sup 2 + c x + d
~ ~ ~ = ~ ~ ~ 3 a x sup 2 + 2 b x + c
.EN
.DE
.nr Ds \n[old-Ds]
In other words,
for each term in the sum of the form $ k x sup n $,
the resulting derivative term is $ k n x sup { n - 1 } $.
Represent the polynomial as
.V= "using polynomial = vector<double>;" ,
with the exponent as the subscript and the coefficient as the value.
So, for example,
$ v = 5 x sup 3 + 9 x sup 2 + 8 x + 10 $
and its derivative
$ d = 15 x sup 2 + 18 x + 8 $ are represented as
.V= "polynomial v {10, 8, 9, 5};"
and
.V= "polynomial d {8, 18, 15};" ,
respectively. 
.SCORE-HERE 3
.DS
.ft CB
polynomial differentiate (const polynomial& p) {
.DE
.SP 1.2i
.LI
Finish the function which will draw a blue circle with radius 1,
centered at co\[:o]rdinates $ ( 0 , 0 ) $.
using OpenGL.
When stepping around the circle it uses angle $ Delta = 2 pi / 32 $.
.SCORE-HERE 3
.DS
.ft CB
void draw_circle() {
   constexpr double delta = 2 * M_PI / 32;
   glBegin (GL_POLYGON);
.SP 1.2i
   glEnd();
}
.DE
.LI
Define a template function
.V= print ,
which takes a pair of iterators and an
.V= ostream
and prints all elements within the range, preceded by an open brace
.=V ( { )
and followed by a close brace
.=V ( } )
with each element separated by commas.
For example,
.V= "print (v.begin(), v.end(), cout);"
might print
.V= "{3,4,5}" .
.SCORE-HERE 2
.SP 1.1i
.LI
Given the structure shown here,
representing an expression tree where interior nodes are operators
and leaf nodes are variables,
finish the function 
.V= print
which will print out the entire tree in reverse Polish notation
(a postorder traversal).
.SCORE-HERE 2
.DS
.TS
tab(|); lfCB |lfCB.
T{
struct tree {
   virtual void print (ostream& out) = 0;
};
struct leaf: public tree {
   char var;
   virtual void print (ostream& out) override {
\0
\0
   }
};
T}|T{
struct interior: public tree {
   char oper;
   tree* left;
   tree* right;
   virtual void print (ostream& out) override {
\0
\0
\0
   }
};
T}
.TE
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
In the 
.V= listmap
project, if there are $n$ integers in a 
.V= listmap<int> ,
how many pointers in the data structure\(??
.CHOOSE
$n$
.CHOOSE
$n + 1$
.CHOOSE
$2 n$
.CHOOSE
$2 n + 1$
.CHOOSE-END
.CHOOSE-BEGIN
If a server is already running,
what system call is used by the client to gain access to
a server's socket\(??
.CHOOSE8V= accept (2) bind (2) connect (2) listen (2)
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following is an IPv4 internet address\(??
.CHOOSE4V 127.0.1 2607:f8b0:4010:801::1010 74.125.239.50 740.625.239.50
.CHOOSE-END
.CHOOSE-BEGIN
Using the OpenGL coordinate system from the project,
the point $( 0 , 0 )$ is shown at the center.
Where is the point $( +1 , +1 )$?
.CHOOSE4 upper\~left upper\~right lower\~right lower\~left
.if dPSPIC \{
.in 150p
.sp -6.8v
.PS .9i
A: "" at (-1,1)
B: "" at (1,1)
C: "" at (1,-1)
D: "" at (-1,-1)
line from A to B
line from B to C
line from C to D
line from D to A
"(A)" at (-.7,.75)
"(B)" at (.7,.75)
"(C)" at (.7,-.8)
"(D)" at (-.7,-.8)
"(0,0)" at (0,0)
.PE
.\}
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= operator[]
were implemented for
.V= std::list ,
what would be its speed\(??
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
If two or more threads access the same variable without
any locks, what happens\(??
.CHOOSE4 deadlock race\~condition runtime\~error segmentation\~fault
.CHOOSE-END
.CHOOSE-BEGIN
What is\(::
.V= "foo x();"
.CHOOSE
.V= x
is a
.V= foo
variable initialized by the empty initializer list.
.CHOOSE
.V= x
is a function with no arguments which returns a
.V= foo .
.CHOOSE
.V= x
is a variable of type
.V= foo
initialized by the default ctor.
.CHOOSE
.V= x
is a variable of type
.V= foo
initialized to 0 by default.
.CHOOSE-END
.CHOOSE-BEGIN
Which is a correct
.V= catch
statement\(??
.CHOOSE4V "catch (domain_error  error)" "catch (domain_error& error)" \
"catch (domain_error* error)" "catch (domain_error\[ti] error)"
.CHOOSE-END
.CHOOSE-BEGIN
Which is based on an array of pointers to fixed sized blocks,
where these blocks are never moved during expansion\(??
.CHOOSE4V deque list map vector
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= "vector<int> v;" ,
which will produce the address of the first element of 
.V= v \(??
.CHOOSE4V "int* a = &*v.begin();" "int* b = &v.begin();" \
"int* c = *&v.begin();" "int* d = *v.begin();"
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= "class foo { ~foo(); };" ,
what is the proper way to define the destructor outside the class\(??
.CHOOSE4V foo::!foo(){} foo::\[ti]foo(){} foo\[ti]::foo(){} \
\[ti]foo::foo(){}
.CHOOSE-END
.CHOOSE-BEGIN
A
.V= foo
is an arbitrarily large object,
and
.V= f
does not intend to modify it.
Which declaration is most correct\(??
.CHOOSE4V "void f (const foo);" "void f (foo&);" "void f (foo);" \
"void f (const foo&);"
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
For
.V= char**\~argv ,
what expression would be equivalent to
.V= argv.end() ,
if
.V= char**
were the name of a class\(??
.CHOOSE4V &argv[0] &argv[1] &argv[argc-1] &argv[argc]
.CHOOSE-END
.CHOOSE-BEGIN
After the following statement,
what is the correct way to free the memory pointed at by 
.V= p \(??
.VTCODE* 0 "foo *p = new foo[n];"
.CHOOSE4V delete*\~p; delete[]\~p; delete\[ti]\~p; delete\~p;
.CHOOSE-END
.CHOOSE-BEGIN
After the following system call,
how many useful bits of information are in the variable
.V= status \(??
.VTCODE* 0 "pid_t child = waitpid (-1,&status,WNOHANG);"
.CHOOSE4 \08 16 24 32
.CHOOSE-END
.CHOOSE-BEGIN
In order to prohibit a constructor from being used in an automatic
conversion,
what keyword is used\(??
.CHOOSE4V delete explicit override virtual
.CHOOSE-END
.CHOOSE-BEGIN
An attempt to define which of the following as a binary operator
will always result in a compile-time error\(??
.CHOOSE4V operator() operator* operator-> operator[]
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following works for a collection that supports only a
forward iterator\(??
If more than one is correct,
choose the most efficient.
.CHOOSE
.V= "for (auto i = c.begin();"
.br
.V= "     i != c.end(); ++i) f(*i);"
.CHOOSE
.V= "for (auto i = c.begin();"
.br
.V= "     i != c.end(); i++) f(*i);"
.CHOOSE
.V= "for (auto i = c.begin();"
.br
.V= "     i < c.end(); ++i) f(*i);"
.CHOOSE
.V= "for (auto i = c.begin();"
.br
.V= "     i < c.end(); i++) f(*i);"
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following is a class defined in C++98
which is deprecated in C++11,
for some arbitrary type
.V= T \(??
.CHOOSE4V T* auto_ptr<T> shared_ptr<T> unique_ptr<T>
.CHOOSE-END
.CHOOSE-BEGIN
What is the amortized time complexity of
.br
.V= map<int,int>::insert \(??
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( log n ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n log n ) $
.CHOOSE-END
.CHOOSE-BEGIN
What is the amortized time complexity of
.br
.V= unordered_map<int,int>::insert \(??
.CHOOSE
$ O ( 1 ) $
.CHOOSE
$ O ( log n ) $
.CHOOSE
$ O ( n ) $
.CHOOSE
$ O ( n log n ) $
.CHOOSE-END
.CHOOSE-BEGIN
An iterator is based on the half-open interval $ [ a , b ) $.
This is the set\(::
.CHOOSE
$ left { x suchthat a < x < b right } $
.CHOOSE
$ left { x suchthat a < x <= b right } $
.CHOOSE
$ left { x suchthat a <= x < b right } $
.CHOOSE
$ left { x suchthat a <= x <= b right } $
.CHOOSE-END
.CHOOSE-BEGIN
Templates in C++ implement what kind of polymorphism\(??
.CHOOSE4 ad\~hoc\~conversion ad\~hoc\~overloading universal\~inclusion \
universal\~parametric
.CHOOSE-END
.CHOOSE-BEGIN
Given the following declarations,
which statement will print a string\(??
.VTCODE* 0 "vector<string*> v;"
.VTCODE* 0 "auto& i = v.begin();"
.CHOOSE4V "cout << i;" "cout << *i;" "cout << **i;" "cout << ***i;"
.CHOOSE-END
.LE
.FINISH
