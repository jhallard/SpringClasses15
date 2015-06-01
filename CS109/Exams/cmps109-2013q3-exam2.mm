.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 Advanced\~Programming Summer\~2013 Test\~#2
.RCS "$Id: cmps109-2013q3-exam2.mm,v 1.30 2013-08-07 20:09:43-07 - - $"
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
If we are writing a mathematical calculator application
and want to store functions like
.V= sqrt ,
.V= sin ,
.V= cos ,
etc.
in a map,
write two
.V= typedef s\(::
Define
.V= mathfn
to be a pointer to any function with a 
.V= double
argument which returns a 
.V= double
result.
Define
.V= mathmap
to be a map whose keys are
.V= string s
and whose values are
.V= mathfn s.
.SCORE-HERE 1
.SP .5i
.LI
Write a function
.V= sum
that takes a
.V= vector<int>
and returns the sum of all the integers
in the vector.
.SCORE-HERE 1
.SP .75i
.LI
Assume we have the declaration
.V= "map<string,size_t> freq;"
which has words found in a document as keys and the counts
of the number of times each word appears.
Write a function which will print out the 100 most frequently-used
words in descending order of frequency.
If any words appear with the same frequency,
print them in lexicographical order.
This is done in several steps.
.ALX a ()
.LI
Write two 
.V= typedefs ,
defining a
.V= wordmap
as the type given above,
and a
.V= wordpair
as the type of the
.V= value_type
of that map.
.SCORE-HERE 1
.SP 0.4i
.LI
Write a function called
.V= precedes
which takes two 
.V= wordpair
values by constant reference and returns true if the first one
should precede the second.
If the counts are different, the larger count precedes.
If the counts are the same, the lexicographically least word
precedes.
.SCORE-HERE 2
.SP 0.75i
.LI
Write the function
.V= printmap ,
which returns
.V= void ,
whose argument is map of the type described above.
.ALX i () "" 0
.LI
Declare a vector capable of holding all map elements.
Use an iterator to copy all of the elements of the map into a
vector.
.SCORE-HERE 2
.LI
Sort the vector using the
.V= sort
function,
whose arguments are a beginning iterator,
an ending iterator,
and a function which returns true when its first argument should
precede its second.
Example\(::
.V= sort(b,e,f)
will sort the range
.V= [b,e)
using the function
.V= f
as a comparator.
.SCORE-HERE 1
.LI
Print out the first 100 elements of the vector,
or all the vector if there are fewer than 100 elements.
Each line of output is a field of width 10 with the count,
then a space, then the word.
The manipulator
.V= setw(10)
will set the next field to be printed using 10 characters.
Example\(::
.V= cout<<setw(10)<<n
works like
.V= printf(\[Dq]%10d\[Dq],n) .
.SCORE-HERE 2
.LE
.LE
.SP 10i
.LI
Define the class
.V= shape .
Define
.V= circle
and
.V= rectangle
which inherit from shape.
.E= "Code all methods inline."
.ALX a ()
.LI
Define the class
.V= shape ,
as a base class for the others,
giving its methods the appropriate protection classification,
and making them pure virtual as appropriate.
Make sure
.V= objects
can not be copied.
.E= "Code all methods inline."
.SCORE-HERE 2
.SP 1.5i
.LI
Define the class 
.V= circle ,
inheriting from
.V= shape .
It has a field
.V= radius .
Its explicit constructor takes one argument with a default value of 0.
It has a method
.V= area ,
which returns its area ,
and a method
.V= boundary ,
which returns its circumference.
The math library in C++ defines
.V= M_PI 
with the appropriate value.
Reminder (for those who failed algebra)\(::
$ A = pi r sup 2 $ and $ C = 2 pi r $.
.E= "Code all methods inline."
.SCORE-HERE 2
.SP 1.5i
.LI
Define the class
.V= rectangle ,
with fields
.V= width
and
.V= height .
Its explicit constructor takes two arguments,
width and height, in that order.
Both have default values of 0.
It also has the methods
.V= area 
and
.V= boundary.
.E= "Code all methods inline."
.SCORE-HERE 2
.SP 1.5i
.LE
.LI
Write a function to merge two vectors of integers into a single
vector of integers, which is then returned.
Assume both input vectors are sorted into increasing order
and make sure the output vector is sorted in the same way.
Use iterators.
Scan both vectors, copying elements to the output vector,
until all elements of one vector is exhausted.
Then write two loops following that which will copy the
remainder of the unscanned elements to the output vector.
.SCORE-HERE 4
.DS
.ft CB
vector<int> merge (const vector<int> v1, const vector<int> v2) {
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
Suppose we have the declarations
.VTCODE* 0 "vector<shared_ptr<string>> vec;"
.VTCODE* 0 "auto i = vec.cbegin();"
What statement will print a string in the vector\(??
.CHOOSE4V cout\~<<\~i; cout\~<<\~*i; cout\~<<\~**i; cout\~<<\~***i;
.CHOOSE-END
.CHOOSE-BEGIN
If we wish to put pointers to nodes in several containers,
where a node may be pointed at from several containers,
the safest way to do this is to use what kind of container elements\(??
.CHOOSE4V auto_ptr<node> node* shared_ptr<node> unique_ptr<node>
.CHOOSE-END
.CHOOSE-BEGIN
.ds foo \f[CB]foo\f[P]
A protected field of class \*[foo] in C++ may be used in\(::
.CHOOSE
class \*[foo] and all classes in the same name\%space as \*[foo].
.CHOOSE
class \*[foo] and all of its subclases.
.CHOOSE
class \*[foo] and all of its superclasses.
.CHOOSE
class \*[foo] and any class that names \*[foo] as a friend.
.CHOOSE-END
.CHOOSE-BEGIN
By default, members of a class are __(x)__,
and members of a struct are __(y)__.
.CHOOSE
(x) = private and (y) = private
.CHOOSE
(x) = private and (y) = public
.CHOOSE
(x) = public and (y) = private
.CHOOSE
(x) = public and (y) = public
.CHOOSE-END
.CHOOSE-BEGIN
What is the signature of a move constructor for class \*[foo]\(??
.CHOOSE4V "foo (const foo &&);" "foo (const foo &);" "foo (foo &&);" \
"foo (foo &);"
.CHOOSE-END
.CHOOSE-BEGIN
Given the following definitions,
which statement will compile without error,
and will not lose information\(??
.VTCODE* 0 "class B {};"
.VTCODE* 0 "class D: public B {};"
.VTCODE* 0 "B *b; D *d;"
.CHOOSE4V *b\~=\~*d; *d\~=\~*b; b\~=\~d; d\~=\~b;
.CHOOSE-END
.CHOOSE-BEGIN
What statement will create one vector with 10 elements in it\(??
.CHOOSE4V new\~vector->int\~(10) new\~vector::int\~[10] \
new\~vector<int>\~(10) new\~vector<int>\~[10]
.CHOOSE-END
.CHOOSE-BEGIN
If
.V= i
is an integer,
and
.V= p
is a pointer or direct-access iterator,
which of the following is illegal\(??
.CHOOSE4V i\~+\~i i\~+\~p p\~+\~i p\~+\~p
.CHOOSE-END
.CHOOSE-BEGIN
In a
.V= Makefile ,
what symbol is used to fill in the blank\(??
.VTCODE* 0 "%.o : %.cpp"
.VTCODE* 0 "        \[Do]{COMPILECPP} -c __"
.CHOOSE4V \[Do]\[Do] \[Do]< \[Do]? \[Do]@
.CHOOSE-END
.CHOOSE-BEGIN
If a class has any virtual functions,
then what else must be declared virtual\(??
.CHOOSE
all constructors
.CHOOSE
all non-constant fields
.CHOOSE
all other function members
.CHOOSE
the destructor
.CHOOSE-END
.CHOOSE-BEGIN
If we have a function
.V= "foo f()"
whose last statement returns a locally constructed
.V= foo
object,
and it is called from the statement
.V= "h = f()",
what member of 
.V= foo
is used at the return statement\(??
.CHOOSE4V "foo &operator= (const foo &);" "foo &operator= (foo &&);" \
"foo (const foo &);" "foo (foo &&);"
.CHOOSE-END
.CHOOSE-BEGIN
What do the following statements do\(??
.VTCODE* 0 "x = 3, 14; y = (3, 14);"
.CHOOSE4V "x = 14; y = 14;" "x = 14; y = 3;" "x = 3; y = 14;" \
"x = 3; y = 3;"
.CHOOSE-END
.LE
.FINISH
