.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-109 Spring\~2015 Program\~2 "Overloading and operators"
.RCS "$Id: asg2-dc-bigint.mm,v 1.76 2015-04-14 12:25:47-07 - - $"
.PWD
.URL
.EQ
delim $$
define uvec  |{ bold u }|
define vvec  |{ bold v }|
define pvec  |{ bold p }|
tdefine rem     |{type binary "\f[CR]%\f[P]"}|
.EN
.H 1 "Overview"
This assignment will involve overloading basic integer operators
to perform arbitrary precision integer arithmetic in the style of
.V= dc (1).
Your class
.V= bigint
will intermix arbitrarily with simple integer arithmetic.
.P
To begin read the 
.V= man (1)
page for the command
.V= dc (1)\(::
.VCODE* 1 "man -s 1 dc" 
A copy of that page is also in this directory.
Your program will use the standard 
.V= dc
as a reference  implemention and must produce exactly
the same output for the commands you have to implement\(::
.VCODE* 1 "+\0 -\0 *\0 /\0 %\0 \[ha]\0 c\0 d\0 f\0 p\0 q\0"
.P
Also look in the subdirectory
.V= misc/
for some examples and in
.V= output/
for the result of running the test data using
.V= dc .
.H 1 "Implementation strategy"
As before, you have been given starter code.
.ALX a ()
.LI
.V= Makefile ,
.V= trace ,
and
.V= util
are similar to the previous program.
If you find you need a function which does not properly belong to
a given module, you may add it to
.V= util .
.LI
The module 
.V= scanner
reads in tokens, namely a
.V= NUMBER ,
an
.V= OPERATOR ,
or
.V= SCANEOF .
Each token returns a
.V= token_t ,
which indicates what kind of token it is
(the
.V= "terminal_symbol symbol" ),
and the
.V= "string lexinfo"
associated
with the token.
Only in the case of a number is there more than one character.
Note that on input, an underscore
.=V ( _ )
indicates a negative number.
The minus sign
.=V ( - )
is reserved only as a binary operator.
The scanner also has defined a couple of
.V= operator<<
for printing out scanner results in
.V= TRACE
mode.
.LI
The main program
.V= main.cpp ,
has been implemented for you.
For the six binary arithmetic functions,
the right operand is popped from the stack,
then the left operand,
then the result is pushed onto the stack.
.LI
The module
.V= iterstack
can not just be the STL
.V= stack ,
since we want to iterate from top to bottom,
and the STL
.V= stack
does not have an iterator.
A stack depends on the operations
.V= back() ,
.V= push_back() ,
and
.V= pop_back()
in the underlying container.
We could use a
.V= vector ,
a
.V= deque ,
or just a 
.V= list ,
as long as the requisite operations are available.
.LE
.H 1 "Class \f[CB]bigint\f[P]"
Then we come to the most complex part of the assignment,
namely the class
.V= bigint .
Operators in this class are heavily overloaded.
.ALX a ()
.LI
most of the functions take a arguments of type
.V= "const bigint &" ,
i.e.,
a constant reference,
for the sake of efficiency.
But they have to return the result by value.
.LI
We want all of the operators to be able to take either a
.V= bigint
or a
.V= long
as either the left or right operand.
Because of this we make the arithmetic operators
.V= friend s
instead of members.
That will cause automatic conversion from a
.V= long
to a
.V= bigint
via the constructor that accepts a
.V= long
argument.
.LI
The
.V= operator<<
can't be a member since its left operand is an
.V= ostream ,
so we make it a
.V= friend ,
so that it can see the innards of a
.V= bigint .
Note now
.V= dc
prints really big numbers.
.LI
The
.V= pow
function exponentiates in
.if n { O ( log sub 2 n ) }
.if t $ O ( log sub 2 n ) $
and need not be changed.
It is not a member of
.V= bigint ,
but it behaves as a member,
since it uses only other functions.
.LI
The relational operators
.V= ==
and
.V= <
are coded individually as member functions.
The others, 
.V= != ,
.V= <= ,
.V= > ,
and
.V= >=
are defined in terms of the essential two.
.LI
The
.V= /
and
.V= %
functions call
.V= divide ,
which is private.
One can not produce a quotient without a remainder, 
and vice versa,
so it returns a pair which is both the quotient and remainder,
and the operator just discards the one that is not needed.
.LI
The given implementation works for small integers,
but overflows for large integers.
.H 1 "Representation of a bigint"
Now we turn to the representation of a 
.V= bigint ,
which will be represented by a boolean flag and a vector of integers.
.ALX a ()
.LI
Replace the declaration
.VCODE* 1 "long long_value;"
with
.VCODE* 1 "using digit_t = unsigned char;"
.VCODE* 1 "using bigvalue_t = vector<digit_t>;"
.VCODE* 1 "bool negative;"
.VCODE* 1 "bigvalue_t big_value;"
in 
.V= bigint.h .
.LI
In storing the long integer it is recommended that each digit in
the range 0 to 9 is kept in an element, 
although true
.V= dc (1)
stores two digits per byte.
But we are not concerned here with extreme efficiency.
Since the arithmetic operators add and subtract work from least
significant digit to most significant digit,
store the elements of the vector in the same order.
That means, for example, that the number $4629$ would be stored in
a vector $v$ as\(::
$v sub 3 = 4 $,
$v sub 2 = 6 $,
$v sub 1 = 2 $,
$v sub 0 = 9 $.
In other words,
if a digit's value is
$d times 10 sup k$,
then $v sub k = d$.
.LI
In order for the comparisons to work correctly,
always store numbers in a canonical form\(::
After computing a value from any one of the six arithmetic operators,
always trim the vector by removing all high-order zeros.
While 
.V= size()\~>\~0
and
.V= back()
returns zero,
.V= pop_back()
the high order digit.
Zero should be represented as a vector of zero length
and a positive sign.
.LI
The representation of a number will be as follows\(::
.V= negative
is a flag which indicates the sign of the number\(;;
.V= big_value 
contains the digits of the number.
.LI
Then use 
.V= grep
or your editor's search function to find all of the occurrences of
.V= long_value .
Each of these occurrences needs to be replaced.
Change all of the constructors so that instead of initializing
.V= long_value ,
they initialize the replacement value.
.LI
The scanner will produce numbers as
.V= string s,
so scan each string from the end of the string,
using a 
.V= const_reverse_iterator
(or other means)
from the end of the string (least significant digit)
to the beginning of the string (most significant digit)
using
.V= push_back
to append them to the vector.
.LE
.H 1 "Implementation of Operators"
.ALX a ()
.LI
Add two new private functions
.V= do_bigadd
and
.V= do_bigsub \(::
.VTCODE* 1 "bigvalue_t do_bigadd (const bigvalue_t&, const bigvalue_t&);
.VTCODE* 1 "bigvalue_t do_bigsub (const bigvalue_t&, const bigvalue_t&);
.LI
Change
.V= operator+
so that it compares the two numbers it gets.
If the signs are the same,
it calls
.V= do_bigadd
to add the vectors and keeps the sign as the result.
If the signs are different,
call
.V= do_bigless
to determine which one is smaller,
and then call 
.V= do_bigsub
to subtract the larger minus the smaller.
Note that this is a different comparison function
which compares absolute values only.
Avoid duplicate code wherever possible.
.LI
The
.V= operator-
should perform similarly.
If the signs are different, it uses
.V= do_bigadd ,
but if the same, it uses
.V= do_bigsub .
.LI
To implement
.V= do_bigadd ,
create a new 
.V= bigvalue_t
and proceed from the low order end to the high order end,
adding digits pairwise.
If any sum is >=\~10,
take the remainder and add the carry to the next digit.
Use
.V= push_back
to append the new digits to the
.V= bigvalue_t .
When you run out of digits in the shorter number,
continue, matching the longer vector with zeros,
until it is done.
Make sure the sign of 0 is positive.
.LI
To implement
.V= do_bigsub ,
also create a new empty vector, starting from the low order end
and continuing until the high end.
In this case, if the left number is smaller than the right number,
the subtraction will be less than zero.
In that case, add 10, and set the borrow to the next number to \-1.
You are, of course, guaranteed here, that the left number is
at least as large as the right number.
After the algorithm is done,
.V= pop_back
all high order zeros from the vector before returning it.
Make sure the sign of 0 is positive.
.LI
You will need to implement
.V= do_bigless ,
which will compare the absolute values of the vectors
to determine which is smaller\(::
.VTCODE* 1 "bool do_bigless (const bigvalue_t&, const bigvalue_t&);
.LI
To implement
.V= operator== ,
check to see if the signs are the same and the lengths of
the vectors are the same.
If not, return false.
Otherwise run down both vectors and return false as soon a difference
is found.
Otherwise return true.
.LI
To implement
.V= operator< ,
remember that a negative number is less than a positive number.
If the signs are the same,
for positive numbers, the shorter one is less,
and for negative nubmers, the longer one is less.
If the signs and lengths are the same,
run down the parallel vectors from the high order end to the low
order end.
When a difference is found, return true or false, as appropriate.
If no difference is found, return false.
.LI
Implement function
.V= do_bigmul ,
which is called from
.V= operator* .
.V= Operator*
uses the rule of signs to determine the sign of the result,
and calls
.V= do_bigmul
to compute the product vector.
.LI
Multiplication in
.V= do_bigmul
proceeds by allocating a new vector
whose size is 
equal to the sum of the sizes of the other two operands.
If $uvec$ is a vector of size $m$
and $vvec$ is a vector of size $n$,
then in $ O ( m n ) $ speed,
perform an outer loop over one argument and an inner loop over
the other argument, adding the new partial products to the product 
$pvec$ as you would by hand.
The algorithm can be described mathematically as follows\(::
.DS I
.br 
$ pvec <- PHI $
$ for ~ i elem [ 0 , m ) ~ : $ 
$ TAB c <- 0 $
$ TAB for ~ j elem [ 0 , n ) ~ : $ 
$ TAB TAB d <- pvec sub { i + j } + uvec sub i vvec sub j + c $ 
$ TAB TAB pvec sub { i + j } <- d rem 10 $
$ TAB TAB c <- left floor d div 10 right floor $ 
$ TAB pvec sub { i + n } <- c $
.br 
.DE 
Note that the interval $ [ a , b ) $ refers to the set
$ roman "{" x | a <= x < b roman "}" $,
i.e., to a half-open interval including $a$ but excluding $b$.
In the same way,
a pair of iterators in C++ bound an interval.
.LI
Long division is complicated if done correctly.
See a paper by P. Brinch Hansen,
``Multiple-length division revisited\(::
A tour of the minefield'',
.I "Software \[em] Practice and Experience 24",
(June 1994), 579\[en]601.
Algorithms 1 to 12 are on pages 13\[en]23,
Note that in Pascal,
array bounds are part of the type,
which is not true for
.V= vector s
in C++.
.VTCODE* 0 multiple-length-division.pdf
.VTCODE* 0 http://brinch-hansen.net/papers/1994b.pdf
.VTCODE* 0 \
http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.14.5815
.LI
The function
.V= divide
as implemented uses the ancient Egyptian division algorithm,
which is slower than Hansen's Pascal program,
but is easier to understand.
Replace the
.V= long
values in it by 
.V= vector<digit_t> .
The logic is shown also in
.=V [ misc/divisioncpp.cpp ].
The algorithm is rather slow,
but the big-$O$ analysis is reasonable.
.LI
Modify
.V= operator<< ,
first just to print out the number all in one line.
You will need this to debug your program.
When you are finished,
make it print numbers in the same way as
.V= dc (1)
does.
.LI
The
.V= pow
function is not a member and uses other operations to raise
a number to a power.
If the exponent does not fit into a single
.V= long
print an error message,
otherwise do the computation.
.LE
.H 1 "Memory leak"
Make sure that you test your program completely so that it does not
crash on a Segmentation Fault or any other unexpected error.
Since you are not using pointers,
and all values are inline,
there should be no memory leak.
Use
.V= valgrind
to check for and eliminate uninitialized variables and memory leak.
.H 1 "What to submit"
Submit source files and only source files\(::
.V= Makefile ,
.V= README ,
and all of the header and implementation files necessary to build
the target executable.
If
.V= gmake
does not build
.V= ydc 
your program can not be tested and you lose 1/2 of the points for
the assignment.
Use
.V= checksource
on  your code.
.P
If you are doing pair programming,
follow the additional instructions in
.V= Syllabus/pair-programming/ 
and also submit
.V= PARTNER .
.FINISH
