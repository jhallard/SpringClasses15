# $Id: Makefile,v 1.3 2014-05-16 21:43:35-07 - - $

GPP        = g++ -g -O0 -Wall -Wextra -std=gnu++11

DEPFILE    = Makefile.dep
HEADERS    = socket.h socket_error.h client_socket.h server_socket.h
CPPSRCS    = socket.cpp client_socket.cpp server_socket.cpp \
             simple_client.cpp simple_server.cpp
CLIENTOBJS = socket.o client_socket.o simple_client.o
SERVEROBJS = socket.o server_socket.o simple_server.o
OBJECTS    = ${CLIENTOBJS} ${SERVEROBJS}
EXECBINS   = simple_client simple_server
LISTING    = Listing.ps
SOURCES    = ${HEADERS} ${CPPSRCS} Makefile ${DEPFILE}

all: ${EXECBINS}

simple_client: ${CLIENTOBJS}
	${GPP} -o $@ ${CLIENTOBJS}

simple_server: ${SERVEROBJS}
	${GPP} -o $@ ${SERVEROBJS}

%.o: %.cpp
	${GPP} -c $<

ci:
	- checksource ${SOURCES}
	- cid + ${SOURCES}

lis: ${SOURCES}
	mkpspdf ${LISTING} ${SOURCES}

clean:
	- rm ${LISTING} ${LISTING:.ps=.pdf} ${OBJECTS}

spotless: clean
	- rm ${EXECBINS} ${DEPFILE}

dep:
	- rm ${DEPFILE}
	make --no-print-directory ${DEPFILE}

${DEPFILE}:
	${GPP} -MM ${CPPSRCS} >${DEPFILE}

again: ${SOURCES}
	make --no-print-directory spotless ci all lis

include ${DEPFILE}

