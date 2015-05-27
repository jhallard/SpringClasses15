// $Id: graphics.h,v 1.9 2014-05-15 16:42:55-07 - - $

#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__

#include <memory>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "rgbcolor.h"
#include "shape.h"

class object {
   private:
      shared_ptr<shape> pshape;
      vertex center;
      rgbcolor color;
      float move_by;
      rgbcolor border_color;
      float border_width;
   public:
      object(shared_ptr<shape> sh, vertex v, rgbcolor c) : center(v),
                color(c), move_by(4.0), border_color("red"),
                border_width(4.0) { 
         pshape = sh;
      } 

      // Default copiers, movers, dtor all OK.
      void draw() { pshape->draw (center, color); }

      void draw_border() { 
         pshape->border(center, border_width, border_color);
      }

      void move (GLfloat delta_x, GLfloat delta_y);

      void set_border(float width, rgbcolor color) {
         if(width > 0.0) {
            border_width = width;
         }
         border_color = color;
      }

      void set_move(float x) {
         move_by = x;
      }

      void move (const string & str) {
         if(str == "up") {
            center.ypos += move_by;
         }
         else if(str == "down") {
            center.ypos -= move_by;
         }
         else if(str == "left") {
            center.xpos -= move_by;
         }
         else if(str == "right") {
            center.xpos += move_by;
         }
         move(0, 0);
      }
};

class mouse {
      friend class window;
   private:
      int xpos {0};
      int ypos {0};
      int entered {GLUT_LEFT};
      int left_state {GLUT_UP};
      int middle_state {GLUT_UP};
      int right_state {GLUT_UP};
   private:
      void set (int x, int y) { xpos = x; ypos = y; }
      void state (int button, int state);
      void draw();
};


class window {
      friend class mouse;
   private:
      static int width;         // in pixels
      static int height;        // in pixels
      static vector<object> objects;
      static size_t selected_obj;
      static mouse mus;
   private:
      static void close();
      static void entry (int mouse_entered);
      static void display();
      static void reshape (int width, int height);
      static void keyboard (GLubyte key, int, int);
      static void special (int key, int, int);
      static void motion (int x, int y);
      static void passivemotion (int x, int y);
      static void mousefn (int button, int state, int x, int y);
   public:
      static void push_back (const object& obj) {
                  objects.push_back (obj); }
      static void setwidth (int width_) {width = width_;}
      static void setheight (int height_) {height = height_;}
      static void main();
      static object & get_selected() {
         return objects[selected_obj];
      }
      static object & get_back() {
         return objects.back();
      }
      static int num_objects() {
         return objects.size();
      }
      static int get_width() { return width; }
      static int get_height() { return height; }
};

#endif

