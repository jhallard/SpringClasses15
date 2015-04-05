
FLTK = /afs/cats.ucsc.edu/courses/cmps109-wm/usr/fltk-1.3.2
GPP = g++ -g -O0 -Wall -Wextra -std=gnu++11 -I${FLTK}/include 
LIBS = ${FLTK}/lib/libfltk.a -lXext -lpthread -ldl -lm -lX11

CPPFILES = ${wildcard *.cpp}
EXECBINS = ${CPPFILES:.cpp=}

all: ${EXECBINS}

%: %.cpp
	${GPP} -o $@ $< ${LIBS}

ci: ${CPPFILES} Makefile
	cid ${CPPFILES} Makefile

