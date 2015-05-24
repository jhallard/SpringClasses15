// $Id: showtext.cpp,v 1.29 2015-02-19 19:39:51-08 - - $

// Display text using OpenGL.
// Text is from argv.

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

#include <GL/freeglut.h>
#include <libgen.h>
#include <unistd.h>

unordered_map<string,void*> font_map {
   {"f13", GLUT_BITMAP_8_BY_13       },
   {"f15", GLUT_BITMAP_9_BY_15       },
   {"h10", GLUT_BITMAP_HELVETICA_10  },
   {"h12", GLUT_BITMAP_HELVETICA_12  },
   {"h18", GLUT_BITMAP_HELVETICA_18  },
   {"t10", GLUT_BITMAP_TIMES_ROMAN_10},
   {"t24", GLUT_BITMAP_TIMES_ROMAN_24},
};

char* progname = nullptr;
const GLubyte GREEN[] = {0, 255, 0};
struct {
   int width {640};
   int height {128};
   void* font = GLUT_BITMAP_TIMES_ROMAN_24;
   string text = "NO TEXT";
} window;

void init_message (int argc, char**argv) {
   for (;;) {
      int opt = getopt (argc, argv, "f:h:t:");
      if (opt == EOF) break;
      string font_code = static_cast<char> (opt) + string (optarg);
      cout << progname << ": font = " << font_code << endl;
      const auto& entry = font_map.find (font_code);
      if (entry != font_map.end()) window.font = entry->second;
   }
   if (optind == argc) return;
   window.text = argv[optind];
   for (char** arg = &argv[optind + 1]; arg < &argv[argc]; ++arg) {
      (window.text += " ") += *arg;
   }
   cout << progname << ": " << window.text << endl;
}


void display() {
   glClearColor (0.2, 0.2, 0.2, 1.0);
   glClear (GL_COLOR_BUFFER_BIT);
   auto text = reinterpret_cast<const GLubyte*> (window.text.c_str());
   size_t width = glutBitmapLength (window.font, text);
   size_t height = glutBitmapHeight (window.font);
   glColor3ubv (GREEN);
   float xpos = window.width / 2.0 - width / 2.0;
   float ypos = window.height / 2.0 - height / 2.0;
   glRasterPos2f (xpos, ypos);
   glutBitmapString (window.font, text);
   glutSwapBuffers();
}

void reshape (int width, int height) {
   window.width = width;
   window.height = height;
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D (0, window.width, 0, window.height);
   glMatrixMode (GL_MODELVIEW);
   glViewport (0, 0, window.width, window.height);
   glutPostRedisplay();
}

int main (int argc, char** argv) {
   progname = basename (argv[0]);
   glutInit (&argc, argv);
   glutInitWindowSize (window.width, window.height);
   glutCreateWindow (progname);
   glutDisplayFunc (display);
   glutReshapeFunc (reshape);
   init_message (argc, argv);
   glutMainLoop();
   return 0;
}

