// $Id: mouseover.cpp,v 1.5 2014-04-18 16:05:03-07 - - $

#include <FL/Fl.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <libgen.h>
#include <sstream>
using namespace std;

string execname;

class event: public Fl_Box {
   private:
      Fl_Window& win;
   public:
      event (int xpos, int ypos, int width, int height, Fl_Window&);
      int handle (int e);
};

event::event (int xpos, int ypos, int width, int height,
              Fl_Window& win):
              Fl_Box (FL_UP_BOX, xpos, ypos, width, height, ""),
              win (win) {
   labelfont (FL_BOLD);
   labelsize (24);
   labeltype (FL_SHADOW_LABEL);
   label ("Mouse Over");
   Fl::focus (this);
}

int event::handle (int e) {
   switch (e) {
      case FL_ENTER:
         color (FL_RED);
         labelcolor (FL_BLACK);
         damage (1);
         break;
      case FL_LEAVE:
         color (FL_GREEN);
         labelcolor (FL_GRAY);
         damage (1);
         break;
      case FL_KEYDOWN:
         {
         int key = Fl::event_key();
         ostringstream skey;
         isgraph (key) ? skey << (char) key : skey << key;
         string labeltext = execname + " [" + skey.str() + "]";
         win.label (labeltext.c_str());
         }
         break;
      default:
         return Fl_Box::handle (e);
   }
   return 1;
}

int main (int argc, char **argv) {
   (void) argc; // warning: unused parameter 'argc'
   execname = basename (argv[0]);
   Fl_Window window (300, 200, execname.c_str());
   window.color (FL_BLUE);
   event ewin (20, 20, 260, 160, window);
   ewin.show();
   window.end();
   window.show();
   return Fl::run();
}
