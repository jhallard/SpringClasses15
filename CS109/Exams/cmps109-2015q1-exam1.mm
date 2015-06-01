.so Tmac.mm-etc
.INITR* \n[.F]
.GETST* SCORE-TOTAL-END SCORE-TOTAL-END
.TITLE CMPS-109 "Advanced Programming" Winter\~2015 Test\~#1
.RCS "$Id: cmps109-2015q1-exam1.mm,v 1.49 2015-01-27 16:47:30-08 - - $"
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
Write a complete program.
Print the message
.=V `` "Hello, World!" ''
to
.V= cout
if no command line arguments are given,
and return an exit status of 0.
If arguments are given,
print the message
.=V `` "Usage: hello" ''
to
.V= cerr ,
and return an exit status of 1.
.SCORE-HERE 2
.SP 1.25i
.LI
Show what should be in the header file
.V= queue.h .
The elements of the queue are
.V= string s.
The representation of the queue uses the STL
data structure
.V= deque .
The operations available to the user of a queue are
.V= push_back ,
.V= pop_front ,
.V= front ,
and
.V= empty .
Also,
.V= operator<<
is a friend.
Types and references are to be consistent with the STL standards.
.SCORE-HERE 3
.SP 1.75i
.LI
Define
.V= operator<<
as mentioned above so that it prints out a queue
with the elements in sequence from front to back with a single
space between elements,
but no space in front of the first or after the last element.
.SCORE-HERE 2
.SP 1.25i
.LI
Assuming the 
.V= bigint
project dealt only with unsigned numbers,
but using the same representation,
finish coding the following function.
.SCORE-HERE 3
.DS
.ft CB
using bigint = vector<unsigned char>;
ostream& operator<< (ostream& out, const bigint& big) {
.DE
.SP 10i
.LI
Write the function
.V= filter .
It takes a pair of iterators into a vector and a predicate which
determines which of the elements are good.
It pushes all good elements onto the back of a list in the
same order they appear in the vector.
Ungood elements are ignored.
.SCORE-HERE 2
.DS
.ft CB
using iter = vector<string>::const_iterator;
using isgood = bool (*) (const string&);
list<string> filter (iter begin, iter end, isgood p) {
.DE
.SP 1i
.LI
Inheritance.
.ALX a () "" 0
.LI
Define a class
.V= base
with an abstract virtual function called
.V= value
that returns a
.V= size_t .
.SCORE-HERE 1
.LI
Define a class
.V= zero ,
derived from
.V= base ,
which overrides that virtual function,
so that it always returns the value 0.
.SCORE-HERE 1
.LI
Define a class
.V= str ,
derived from
.V= base ,
with a private string field and whose
.V= value
function returns the 
.V= size
of the string.
Do not show any members except those explicitly mentioned here.
.SCORE-HERE 2
.LE
.SP 2.25i
.LI
Define the function
.V= reverse
which reverses elements in a linear data structure.
Assume the template argument
.V= Iter
is a bidirectional iterator, i.e., one for which both
.V= operator++
and
.V= operator--
are provided.
.SCORE-HERE 2
.DS
.ft CB
template <typename Iter>
void reverse (Iter begin, Iter end) {
.DE
.SP 1.5i
.LI
Define the function 
.V= canonicalize
which takes a vector of digits, as in the assignment,
and removes all high-order zeros.
If all digits are zeros, the vector should be emptied.
.SCORE-HERE 2
.DS
.ft CB
using bigint = vector<unsigned char>;
void canonicalize (bigint& big) {
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
Which of the following programming errors will definitely
crash a program\(??
.CHOOSE
allowing memory leak
.CHOOSE
an out-of-bounds subscript to a vector
.CHOOSE
dereferencing a null pointer
.CHOOSE
using uninitialized variables
.CHOOSE-END
.CHOOSE-BEGIN
Given
.V= "string s;"
.V= "string t;"
which will compare two strings lexicographically\(??
.CHOOSE4V "&s < &t" "*s < *t" "s < t" "strcmp (s, t) < 0"
.CHOOSE-END
.CHOOSE-BEGIN
What is used to initialize a vector from the command line arguments,
but not the program name\(??
.CHOOSE
.V= "vector<string>"
.br
.V= "vs (&argv[0], argv[argc - 1]);"
.CHOOSE
.V= "vector<string>"
.br
.V= "vs (&argv[0], argv[argc]);"
.CHOOSE
.V= "vector<string>"
.br
.V= "vs (&argv[1], argv[argc - 1]);"
.CHOOSE
.V= "vector<string>"
.br
.V= "vs (&argv[1], argv[argc]);"
.CHOOSE-END
.CHOOSE-BEGIN
What will define
.V= vs
as a typename meaning the same as
.V= vector<string> \(??
.CHOOSE4V "typedef vector<string> = vs;" \
"typedef vs = vector<string>;" \
"using vector<string> = vs;" \
"using vs = vector<string>;"
.CHOOSE-END
.CHOOSE-BEGIN
In order to avoid explicitly qualifying library entities,
what statement should follow the usual includes\(??
.CHOOSE4V "import namespace standard;" "include namespace std;" \
"using namespace standard;" "using namespace std;"
.CHOOSE-END
.CHOOSE-BEGIN
After the declaration
.V= "int& p = i;"
which statement will change the value of
.V= i \(??
.CHOOSE4V "&p = i;" "*p = i;" "p = &i;" "p = i;"
.CHOOSE-END
.CHOOSE-BEGIN
What is the preferred way to refer to a pointer that does not point
at any object\(??
.CHOOSE4V 0 NULL null nullptr
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following STL classes
manages memory via reference counting\(??
.CHOOSE4V auto_ptr shared_ptr smart_ptr unique_ptr
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following forms of polymorphism should be used in C++
to replace
.V= union
in C\(??
.CHOOSE4 conversion inheritance overloading templates
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following operators can almost never by a member
function\(??
.CHOOSE4V operator++ operator-> operator<< operator==
.CHOOSE-END
.CHOOSE-BEGIN
Which of the following containers has the least heap space overhead\(??
.CHOOSE4V deque list map vector
.CHOOSE-END
.CHOOSE-BEGIN
Which data structure is most likely as an implementation of the STL
.V= map \(??
.CHOOSE4 "array of pointers" "double-ended queue" "hash table" \
"red-black tree"
.CHOOSE-END
.LE
.FINISH
