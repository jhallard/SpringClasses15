// $Id: unicode.cpp,v 1.1 2014-04-18 15:43:32-07 - - $

#include <cassert>
#include <cxxabi.h>
#include <iostream>
#include <typeinfo>
#include <clocale>
using namespace std;

#include <FL/Fl.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Window.H>
#include <FL/fl_utf8.h>

struct buttons: public Fl_Window {
   buttons (int width, int height, const string& wname): 
            Fl_Window (width, height, wname.c_str()) {
      char buf[5];
      int n = fl_utf8encode (0x03C0, buf);
      buf[n] = 0;
      for (int i = 0; i < n; ++i) {
         cerr << " " << hex << (0xFF & (unsigned)(buf[i]));
      }
      cerr << "(" << buf << ")" << endl;
      auto button = new Fl_Button (16, 16, 32, 32, buf);
      show();
   }
};

int main() {
   cout << "locale: " << setlocale (LC_ALL, "en_US.UTF-8") << endl;
   buttons win (400, 200, "Buttons");
   return Fl::run();
}
