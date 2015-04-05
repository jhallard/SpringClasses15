// $Id: button2.cpp,v 1.2 2014-04-18 15:43:32-07 - - $

#include <cassert>
#include <cxxabi.h>
#include <iostream>
#include <typeinfo>
using namespace std;

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>

string type_of (const type_info &info) {
   int status;
   char *unmangled = abi::__cxa_demangle ( info.name(), 0, 0, &status);
   string result {unmangled};
   free (unmangled);
   return result;
}

class button_window: public Fl_Window {
   private:
      static size_t click_count;
      static void click (Fl_Widget*, void* ptr) {
         auto self = reinterpret_cast<button_window*> (ptr);
         assert (typeid (*self) == typeid (button_window));
         cerr << "self(" << type_of (typeid (*self)) << ")="
              << self << endl;
         cerr << __func__ << ": " << ++click_count << endl;
      }
      static void quit (Fl_Widget*, void*) {
         cerr << __func__ << ": quitting." << endl;
         exit (1);
      }
   public:
      button_window (int width, int height, const string& wname):
            Fl_Window (width, height, wname.c_str()) {
         auto button = new Fl_Button (10, 10, 100, 25, "Click me");
         button->callback (click, static_cast<void*> (this));
         callback (quit, static_cast<void*> (this));
         show();
      }
};
size_t button_window::click_count = 0;

int main() {
   button_window win (400, 200, "Button window");
   return Fl::run();
}

