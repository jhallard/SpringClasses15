// $Id: button.cpp,v 1.2 2014-04-18 15:43:32-07 - - $

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <iostream>
#include <libgen.h>
using namespace std;

int clicks = 0;

#define SHOW cout << __func__ << "[" << __LINE__ << "]: " \
                  << clicks << " clicks." << endl;

void click (Fl_Widget*, void*) {
   ++clicks;
   SHOW;
}

void quit (Fl_Widget*, void*) {
   SHOW;
   cout << "Quitting." << endl;
   exit (1);
}

int main (int argc, char** argv) {
   (void) argc;
   Fl_Window window (200, 100, basename (argv[0]));
   Fl_Button button (50, 25, 100, 50, "Click me.");
   button.callback (click, nullptr);
   window.show();
   window.callback (quit);
   return Fl::run();
}

