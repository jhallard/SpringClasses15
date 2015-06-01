// $Id: shape.cpp,v 1.7 2014-05-08 18:32:56-07 - - $

#include <typeinfo>
#include <unordered_map>
using namespace std;

#include "shape.h"
#include "util.h"

static unordered_map<void*,string> fontname {
   {GLUT_BITMAP_8_BY_13       , "Fixed-8x13"    },
   {GLUT_BITMAP_9_BY_15       , "Fixed-9x15"    },
   {GLUT_BITMAP_HELVETICA_10  , "Helvetica-10"  },
   {GLUT_BITMAP_HELVETICA_12  , "Helvetica-12"  },
   {GLUT_BITMAP_HELVETICA_18  , "Helvetica-18"  },
   {GLUT_BITMAP_TIMES_ROMAN_10, "Times-Roman-10"},
   {GLUT_BITMAP_TIMES_ROMAN_24, "Times-Roman-24"},
};

static unordered_map<string,void*> fontcode {
   {"Fixed-8x13"    , GLUT_BITMAP_8_BY_13       },
   {"Fixed-9x15"    , GLUT_BITMAP_9_BY_15       },
   {"Helvetica-10"  , GLUT_BITMAP_HELVETICA_10  },
   {"Helvetica-12"  , GLUT_BITMAP_HELVETICA_12  },
   {"Helvetica-18"  , GLUT_BITMAP_HELVETICA_18  },
   {"Times-Roman-10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"Times-Roman-24", GLUT_BITMAP_TIMES_ROMAN_24},
};

ostream& operator<< (ostream& out, const vertex& where) {
   out << "(" << where.xpos << "," << where.ypos << ")";
   return out;
}


vertex_list normalize_polygon(vertex_list v_list) {

   float avx = 0.0, avy = 0.0;
   for(auto v : v_list) {
      avx += v.xpos;
      avy += v.ypos;
   }

   avx = avx/((double)v_list.size());
   avy = avy/((double)v_list.size());

   vertex_list ret;
   for( auto v : v_list) {
      ret.push_back({v.xpos-avx, v.ypos-avy});
   }

   return ret;
}

shape::shape() {
   DEBUGF ('c', this);
}

text::text (void* glut_bitmap_font, const string& textdata):
      glut_bitmap_font(glut_bitmap_font), textdata(textdata) {
   DEBUGF ('c', this);
}

text::text(const string & font, const string &textdata) {
   auto itor = fontcode.find(font);
   
   if(itor == fontcode.end()) {
      throw runtime_error("Invalid font code : " + font);
   }
   
   glut_bitmap_font = itor->second;
   this->textdata = textdata;
}

ellipse::ellipse (GLfloat width, GLfloat height):
dimension ({width, height}) {
   DEBUGF ('c', this);
}

circle::circle (GLfloat diameter): ellipse (diameter, diameter) {
   DEBUGF ('c', this);
}


polygon::polygon (const vertex_list& vertices): vertices(
   normalize_polygon(vertices) ) {
   DEBUGF ('c', this);
}

rectangle::rectangle (GLfloat width, GLfloat height): polygon({
            {-width/2.0, -height/2.0}, {-width/2.0, height/2.0},
            {width/2.0, height/2.0}, {width/2.0, -height/2.0} }) 
{
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

square::square (GLfloat width): rectangle (width, width) {
   DEBUGF ('c', this);
}

diamond::diamond (GLfloat width, GLfloat height) : polygon(
                  {{-width/2.0, 0.0}, {0.0, height/2.0},
                  {width/2.0, 0.0}, {0.0, -height/2.0}}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

triangle::triangle (vertex v1, vertex v2, vertex v3) : 
                                 polygon({v1, v2, v3}) {
   DEBUGF ('c', this << "(" << v1 << "," << v2 << "," << v3 << ")");
}

isosceles::isosceles (GLfloat width, GLfloat height) : triangle(
   {0.0, height}, {-width/2.0, 0.0}, {width/2.0, 0.0}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}

equilateral::equilateral (GLfloat side) : triangle(
   {0.0, 0.8660*side}, {-side/2.0, 0.0}, {side/2.0, 0.0} ) {
   DEBUGF ('c', this << "(" << side <<  ")");
}

right_triangle::right_triangle (GLfloat width, GLfloat height) :
 triangle({0.0, 0.0}, {0.0, height}, {width, 0.0}) {
   DEBUGF ('c', this << "(" << width << "," << height << ")");
}


void text::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
      rgbcolor new_c(color);
      glColor3ubv (new_c.ubvec);
      glRasterPos2i (center.xpos, center.ypos);
      glutBitmapString (glut_bitmap_font, (GLubyte*) textdata.c_str());
}

void text::border(vertex center, float width, rgbcolor color) const {
   DEBUGF ('d', this << "(" << width << "," << color << ")");
   // does nothing on purpose

}

void ellipse::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");
   rgbcolor new_c(color);
   glBegin (GL_POLYGON);
   glEnable (GL_LINE_SMOOTH);
   glColor3ubv (new_c.ubvec3());
   float x,y;
   float t;
   for(t = 0.0; t <= 360; t +=0.02)
   {
      x = center.xpos + dimension.xpos*sin(t);
      y = center.ypos + dimension.ypos*cos(t);
      glVertex2f(x,y);
    }
    glEnd();
}

void ellipse::border(vertex center, float width, rgbcolor color) const {
   DEBUGF ('d', this << "(" << width << "," << color << ")");
   rgbcolor new_c(color);
   glLineWidth(width); 
   glEnable (GL_LINE_SMOOTH);
   glColor3ubv (new_c.ubvec3());
   glBegin (GL_LINES);
   float x,y;
   float t;
   for(t = 0.0; t <= 360; t +=0.02)
   {
      x = center.xpos + dimension.xpos*sin(t);
      y = center.ypos + dimension.ypos*cos(t);
      glVertex2f(x,y);
    }
    glEnd();
}

void polygon::draw (const vertex& center, const rgbcolor& color) const {
   DEBUGF ('d', this << "(" << center << "," << color << ")");

   glBegin (GL_POLYGON);
   rgbcolor new_c(color);
   glColor3ubv (new_c.ubvec3());

   for(auto vert : vertices) {
      glVertex2f (vert.xpos+center.xpos,
            vert.ypos+center.ypos);
   }
   glEnd();
}

void polygon::border(vertex center, float width, rgbcolor color) const {
   glLineWidth(width); 
   rgbcolor new_c(color);
   glColor3ubv(new_c.ubvec3());
   glBegin(GL_LINES);
   for(int i = 0; i < vertices.size()-1; ++i) {
      glVertex2f (vertices[i].xpos+center.xpos,
            vertices[i].ypos+center.ypos);
      glVertex2f (vertices[i+1].xpos+center.xpos,
            vertices[i+1].ypos+center.ypos);
   }
   glVertex2f(vertices.back().xpos+center.xpos, 
      vertices.back().ypos+center.ypos);
   glVertex2f(vertices[0].xpos+center.xpos, 
      vertices[0].ypos+center.ypos);
   glEnd();
}

void shape::show (ostream& out) const {
   out << this << "->" << demangle (*this) << ": ";
}

void text::show (ostream& out) const {
   shape::show (out);
   out << glut_bitmap_font << "(" << fontname[glut_bitmap_font]
       << ") \"" << textdata << "\"";
}

void ellipse::show (ostream& out) const {
   shape::show (out);
   out << "{" << dimension << "}";
}

void polygon::show (ostream& out) const {
   shape::show (out);
   out << "{" << vertices << "}";
}

ostream& operator<< (ostream& out, const shape& obj) {
   obj.show (out);
   return out;
}

