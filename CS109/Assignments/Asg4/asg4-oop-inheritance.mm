.so Tmac.mm-etc
.if t .Newcentury-fonts
.INITR* \n[.F]
.SIZE 12 14
.TITLE CMPS-109 Spring\~2015 Program\~4 "OOP and Inheritance"
.RCS "$Id: asg4-oop-inheritance.mm,v 1.77 2015-05-11 14:45:03-07 - - $"
.PWD
.URL
.EQ
delim $$
.EN
.de COMMAND 
.   ds commandstr \f[CB]\\$1
.   while \\n[.$]>1 \{ .\"
.      shift   
.      if '\\$1'?' .as commandstr \0\fR[\fI\\$2\fR]\f[CB]
.      if '\\$1'I' .as commandstr \0\fI\\$2\f[CB]
.      if '\\$1'R' .as commandstr \0\fR\\$2\f[CB]
.      if '\\$1'V' .as commandstr \0\\$2
.      shift   
.   \}
.   LI "\\*[commandstr]\f[R]"
..
.H 1 "Overview"
In this assignment you will implement a simple graphics package
using the OpenGL graphics library.
Using inheritance, 
geometric objects will be displayed in a window.
The lab workstations all run X11 so there is no problem there.
When you log into the server remotely, be sure to specify the
.V= -X
option, as in\(::
.VTCODE* 1 "ssh -X \fIusername\fP@unix.ucsc.edu"
Before you log into the server make sure you have an X11 client
running on your own workstation.
.H 1 "Program Specification"
The program is presented in the form of a Unix 
.V= man (1)
page.
.SH=BVL
.MANPAGE=LI "NAME"
gdraw
\[em]
drawing program displaying objects in a window
.MANPAGE=LI "SYNOPSIS"
.V= gdraw
.RI \|[
.IR options ]
.RI [ filename ]
.MANPAGE=LI "OPTIONS"
All options are recognized by
.V= getopt (3).
.VL \n[Pi]
.MANOPT=LI -@ flags
The flags specified are passed to the debugging macro.
Debug output is printed to the standard error.
.MANOPT=LI -w width
The initial width of the window.
Default\(::
640.
.MANOPT=LI -h height
The initial height of the window.
Default\(::
480.
.\".MANOPT=LI -u unit
.\"The number of pixels included in one unit of distance.
.\"Default\(:: 1.
.\"Example\(::
.\"If the unit is specified as 100,
.\"then a length of 1 unit is 100 pixels.
.\".MANOPT=LI -x co\[:o]rdinate
.\"The $x$ position in pixels of the coordinate $ ( 0 , 0 ) $.
.\"Default\(::
.\"0.
.\"The $x$-axis always increases to the right.
.\".MANOPT=LI -y coordinate
.\"The $y$ position in pixels of the coordinate $ ( 0 , 0 ) $.
.\"Default\(::
.\"0.
.\"The $y$-acis always increases upward.
.LE
.MANPAGE=LI "OPERANDS"
Commands are read from the file whose name is given as an operand.
If no filename is given, commands are read from the standard input.
.MANPAGE=LI "COMMANDS"
When the program begins, a window is created for displaying
information, which consists of text and geometric objects of
various kinds.
The project proceeds in two parts\(::
.ALX a ()
.LI
Shapes are defined in terms of their sizes (length, width,
or vertices).
.LI
Objects are drawn in the window by drawing commands,
after which they may be altered by keyboard commands.
.LE
.P
Sizes, lengths, widths, and coordinates are all floating point numbers,
and measure pixels.
.P
Colors may be specified by name using one of the names in
the file
.V= rgb.txt ,
or by their hexadecimal values in the form
.VI 0xRRGGBB ,
where
.V= RR ,
.V= GG ,
and
.V= BB
are the red, green, and blue components each specified as
two hexadecimal digits in the range
.V= 00
to
.V= FF .
.P
The
.V= define
command makes a record of the definition of an shape and makes
it available later for a draw command.
The
.V= draw
command
creates an object in the screen's object list,
to be displayed when the program starts.
.P
The following commands are recognized.
Each command is on a line by itself and terminates with the
newline character.
If the last character on a line is a backslash
.=V ( \[rs] ),
the command is continued onto the next line.
.BVL \n[Pi]
.COMMAND # R \|.\|.\|.
A comment line is ignored,
as are empty lines and lines consisting only of white space.
.COMMAND define I name V text I font I words\|.\|.\|.
A text object is created by concatenating all of the words together,
each separated from the next by spaces.
The font is any of the seven GLUT bitmap fonts\(::
.ALX \[bu] 0 "" 0 0
.LI
.V= Fixed-8x13
.LI
.V= Fixed-9x15
.LI
.V= Helvetica-10
.LI
.V= Helvetica-12
.LI
.V= Helvetica-18
.LI
.V= Times-Roman-10
.LI
.V= Times-Roman-24
.LE
.COMMAND define I name V ellipse I width I height
An ellipse is specified with the major and minor diameters specified.
When drawn, the drawing coordinate is the center.
.COMMAND define I name V circle I diameter
A circle is just an ellipse whose length and width are equal.
.COMMAND define I name V polygon I x0 I y0 I x1 I y1 \
I x2 I y2 R \|.\|.\|.\|
A polygon is specified with the number of vertices being equal to
the number of $ ( x , y ) $ coordinates given.
The polygon must be convex (each interior angle less than 180 degrees).
The convexity is not verified by the program,
so the appearance of a non-convex polygon is undefined.
The center of the polygon is at $ ( x bar , y bar ) $, i.e.,
at the average of all the $x$ coordinates and the average of
the $y$ coordinates.
After computing the average,
it is subtracted from each of the vertices to normalize them.
For example, if the vertices are
specified as shown in the left side of the diagram,
they are normalized to that shown on the right side,
so that $ ( x bar , y bar ) $ changes from $ ( .5 , .5 ) $ to
$ ( 0 , 0 ) $.
.nr Si 2*\n[Pi]
.DS I
.TS
tab(|); c cw(1i) c.
T{
.PS 1i
"$ ( 0 , 0 ) $" at 0,-.1
"$ ( 1 , 0 ) $" at 1,-.1
"$ ( 1 , 1 ) $" at 1,1.1
"$ ( 0 , 1 ) $" at 0,1.1
line from 0,0 to 1,0 then to 1,1 then to 0,1 then to 0,0
"$ ( .5 , .5 ) $" at .5,.5
.PE
T}||T{
.PS 1i
"$ ( -.5 , -.5 $)" at 0,-.1
"$ ( +.5 , -.5 $)" at 1,-.1
"$ ( +.5 , +.5 $)" at 1,1.1
"$ ( -.5 , +.5 $)" at 0,1.1
line from 0,0 to 1,0 then to 1,1 then to 0,1 then to 0,0
"$ ( 0 , 0 ) $" at .5,.5
.PE
T}
.TE
.DE
.COMMAND define I name V rectangle I width I height
A rectangle with the given width and height is defined with
strictly horizontal and vertical lines with the given thickness.
When drawn, the drawing coordinates will be the center.
.COMMAND define I name V square I width
A square is a rectangle with equal width and height.
.COMMAND define I name V diamond I width I height
A diamond's width is from the leftmost to rightmost point and its
height is from topmost to bottommost height.
The draw command specifies its center.
.COMMAND define I name V triangle I x0 I y0 I x1 I y1 I x2 I y2
A triangle is just another name for a polygon.
.COMMAND define I name V right_triangle I width I height
Define a right triangle with width the horizontal bar
extending to the right and height
the vertical bar.
.COMMAND define I name V isosceles I width I height
The width specifies the width of the base,
and the height specifies the perpendicular distance from the
base to the apex.
.COMMAND define I name V equilateral I width
Makes an isosceles triangle that is also equilateral.
.COMMAND border I color I thickness
Specifies the thickness in pixels of the border surrounding the selected
object, and its color.
Defaults\(::
red, 4.
.COMMAND moveby I pixels
The move parameter indicates how many pixels an object moves when
directed by one keystroke.
Default\(::
4.
.COMMAND draw I color I name I xcenter I ycenter
Draws an object with the center at $ ( x , y ) $ using the color
specified.
.LE
.MANPAGE=LI "KEYBOARD INPUT"
Once the input file is finished,
the keyboard is used to command the movements of the objects.
The following keystrokes control the program\(::
.nr Si \n[Pi]
.DS I
.TS
tab(|); lfCB l.
q|Quit (exit the program).
h|Move the selected object left.
j|Move the selected object down.
k|Move the selected object up.
l|Move the selected object right.
n|Set the selection to the next object.
p|Set the selection to the previous object.
0\fR ... \f[CB]9|Set the selection to objects 0 through 9, respectively.
.TE
.DE
An object is always displayed using the coordinates of the center.
If an object is moved off the window, it appears at the other
end of the window.
That is, if the $x$ or $y$ coordinate exceeds the width (height)
of the windor, it is set to 0.
If it becomes negative, it is set to the width (height).
The selected object is always surrounded by a border to make
it visible.
For objects 0 through 9,
the object's number is displayed in the center of the object.
.MANPAGE=LI "EXIT STATUS"
.VL \n[Pi]
.LI 0
No errors were detected.
.LI 1
Errors were detected and messages printed to the standard error.
.LE
.LE
.H 1 "Code"
OpenGL and GLUT will be used to display the window.
See the short example programs in the
.V= misc/
subdirectory.
Starter code is in the
.V= code/
subdirectory.
For documentation, Google using the terms ``OpenGL'' and/or ``GLUT''
and the name of the function, 
then look for results naming the web pages in
.VTCODE* 1 www.opengl.org/documentation
Following are some functions you might need\(::
.VTCODE* 1 glBegin
.VTCODE* 1 glClear
.VTCODE* 1 glClearColor
.VTCODE* 1 glColor3ub
.VTCODE* 1 glColor3ubv
.VTCODE* 1 glEnable
.VTCODE* 1 glEnd
.VTCODE* 1 glFlush
.VTCODE* 1 glHint
.VTCODE* 1 glLineWidth
.VTCODE* 1 glLoadIdentity
.VTCODE* 1 glMatrixMode
.VTCODE* 1 glOrtho
.VTCODE* 1 glPointSize
.VTCODE* 1 glPopMatrix
.VTCODE* 1 glPushMatrix
.VTCODE* 1 glRasterPos2f
.VTCODE* 1 glRasterPos2i
.VTCODE* 1 glRotatef
.VTCODE* 1 glTranslatef
.VTCODE* 1 glVertex2f
.VTCODE* 1 glViewport
.VTCODE* 1 gluOrtho2D
.VTCODE* 1 glutAddMenuEntry
.VTCODE* 1 glutAddSubMenu
.VTCODE* 1 glutAttachMenu
.VTCODE* 1 glutBitmapCharacter
.VTCODE* 1 glutBitmapHeight
.VTCODE* 1 glutBitmapLength
.VTCODE* 1 glutBitmapString
.VTCODE* 1 glutCloseFunc
.VTCODE* 1 glutCreateMenu
.VTCODE* 1 glutCreateWindow
.VTCODE* 1 glutDisplayFunc
.VTCODE* 1 glutEntryFunc
.VTCODE* 1 glutInit
.VTCODE* 1 glutInitDisplayMode
.VTCODE* 1 glutInitWindowPosition
.VTCODE* 1 glutInitWindowSize
.VTCODE* 1 glutKeyboardFunc
.VTCODE* 1 glutKeyboardUpFunc
.VTCODE* 1 glutMainLoop
.VTCODE* 1 glutMotionFunc
.VTCODE* 1 glutMouseFunc
.VTCODE* 1 glutPassiveMotionFunc
.VTCODE* 1 glutPostRedisplay
.VTCODE* 1 glutReshapeFunc
.VTCODE* 1 glutSetIconTitle
.VTCODE* 1 glutSetWindowTitle
.VTCODE* 1 glutSpecialFunc
.VTCODE* 1 glutSpecialUpFunc
.VTCODE* 1 glutSwapBuffers
.VTCODE* 1 glutTimerFunc
.VTCODE* 1 glutWireTeapot
.H 1 "What to Submit"
Submit all C++ source files and the
.V= Makefile .
If you are doing pair programming, also submit the
.V= PARTNER
file.
.FINISH
