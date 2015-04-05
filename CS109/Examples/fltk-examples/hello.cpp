// $Id: hello.cpp,v 1.1 2014-04-14 17:33:51-07 - - $

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>

int main(int argc, char **argv) {
   Fl_Window *window = new Fl_Window(300,180);
   Fl_Box *box = new Fl_Box(20,40,260,100,"Hello, World!");
   box->box(FL_UP_BOX);
   box->labelsize(36);
   box->labelfont(FL_BOLD+FL_ITALIC);
   box->labeltype(FL_SHADOW_LABEL);
   window->end();
   window->show(argc, argv);
   return Fl::run();
 }

