// $Id: interp.cpp,v 1.18 2015-02-19 16:50:37-08 - - $

#include <memory>
#include <string>
#include <vector>
using namespace std;

#include <GL/freeglut.h>

#include "debug.h"
#include "interp.h"
#include "shape.h"
#include "util.h"

unordered_map<string,interpreter::interpreterfn>
interpreter::interp_map {
   {"define" , &interpreter::do_define },
   {"draw"   , &interpreter::do_draw   },
};

unordered_map<string,interpreter::factoryfn>
interpreter::factory_map {
   {"text"     , &interpreter::make_text     },
   {"ellipse"  , &interpreter::make_ellipse  },
   {"circle"   , &interpreter::make_circle   },
   {"polygon"  , &interpreter::make_polygon  },
   {"rectangle", &interpreter::make_rectangle},
   {"square"   , &interpreter::make_square   },
   {"diamond"  , &interpreter::make_diamond  },
   {"triangle"  , &interpreter::make_triangle },
   {"isosceles"  , &interpreter::make_isosceles},
   {"equilateral"  , &interpreter::make_equilateral},

};

interpreter::shape_map interpreter::objmap;

interpreter::~interpreter() {
   for (const auto& itor: objmap) {
      cout << "objmap[" << itor.first << "] = "
           << *itor.second << endl;
   }
}

void interpreter::interpret (const parameters& params) {
   DEBUGF ('i', params);
   param begin = params.cbegin();
   string command = *begin;
   auto itor = interp_map.find (command);
   if (itor == interp_map.end()) throw runtime_error ("syntax error");
   interpreterfn func = itor->second;
   func (++begin, params.cend());
}

void interpreter::do_define (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string name = *begin;
   objmap.emplace (name, make_shape (++begin, end));
}


void interpreter::do_draw (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if (end - begin != 4) throw runtime_error ("syntax error");
   string name = begin[1];
   shape_map::const_iterator itor = objmap.find (name);
   if (itor == objmap.end()) {
      throw runtime_error (name + ": no such shape");
   }
   vertex where {from_string<GLfloat> (begin[2]),
                 from_string<GLfloat> (begin[3])};
   rgbcolor color {begin[0]};
   object new_o(itor->second, where, color);
   window::push_back(new_o);
   // itor->second->draw (where, color);
}

shape_ptr interpreter::make_shape (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   string type = *begin++;
   auto itor = factory_map.find(type);
   if (itor == factory_map.end()) {
      throw runtime_error (type + ": no such shape");
   }
   factoryfn func = itor->second;
   return func (begin, end);
}

shape_ptr interpreter::make_text (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   if(begin == end) {
      throw runtime_error("Text needs font and string arguments");
   }

   string fontcode = *begin;
   ++begin;
   string cat = "";
   for(auto it = begin; it != end; ++it) {
      cat += *it;
      cat += " ";
   }
   if(cat.length())  {
      return make_shared<text> (fontcode, 
             cat.substr(0, cat.length()-1));
   }
   else {
      return make_shared<text> (fontcode, cat);
   }
}

shape_ptr interpreter::make_ellipse (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   float val = atof(begin->c_str());
   ++begin;
   float val2 = atof(begin->c_str());
   return make_shared<ellipse> (GLfloat(val), GLfloat(val2));
}

shape_ptr interpreter::make_circle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   return make_shared<circle> (GLfloat(atof(begin->c_str())));
}

shape_ptr interpreter::make_polygon (param begin, param end) {
   DEBUGF ('f', range (begin, end));

   vertex_list list;
   auto it = begin;
   while(it != end) {
      float val = atof(it->c_str());
      ++it;
      float val2 = atof(it->c_str());
      ++it;
      list.push_back(vertex(val, val2));
   }
   return make_shared<polygon> (list);
}

shape_ptr interpreter::make_rectangle (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   float val = atof(begin->c_str());
   ++begin;
   float val2 = atof(begin->c_str());
   return make_shared<rectangle> (GLfloat(val), GLfloat(val2));
}

shape_ptr interpreter::make_square (param begin, param end) {
   DEBUGF ('f', range (begin, end));
   float val = atof(begin->c_str());
   return make_shared<square> (GLfloat(val));
}

shape_ptr interpreter::make_diamond (param begin, param end) {
   DEBUGF('f', range(begin, end));
   float val = atof(begin->c_str());
   ++begin;
   float val2 = atof(begin->c_str());
   return make_shared<diamond> (GLfloat(val), GLfloat(val2));
} 

shape_ptr interpreter::make_triangle (param begin, param end) {
   DEBUGF('f', range(begin, end));
   vertex_list list;
   auto it = begin;
   while(it != end) {
      float val = atof(it->c_str());
      ++it;
      float val2 = atof(it->c_str());
      ++it;
      list.push_back(vertex(val, val2));
   }
   if(list.size() != 3) { 
      throw runtime_error("Triangle needs three arguments");
   }
   return make_shared<triangle> (list[0], list[1], list[2]);
} 

shape_ptr interpreter::make_isosceles (param begin, param end) {
   DEBUGF('f', range(begin, end));
   float val = atof(begin->c_str());
   ++begin;
   float val2 = atof(begin->c_str());
   return make_shared<isosceles> (GLfloat(val), GLfloat(val2));
} 

shape_ptr interpreter::make_equilateral (param begin, param end) {
   DEBUGF('f', range(begin, end));
   float val = atof(begin->c_str());
   return make_shared<equilateral> (GLfloat(val));
}
