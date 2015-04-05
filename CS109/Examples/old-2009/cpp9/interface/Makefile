# $Id: Makefile,v 1.5 2009-03-06 20:04:35-08 - - $

COMPILE = CC -g -features=extensions
MAKEDEP = CC -xM1
DEPFILE = Makefile.deps

HEADERS = stack.h arraystack.h linkedstack.h
SOURCES = ${HEADERS:.h=.cc} teststack.cc
ALLSRCS = ${HEADERS} ${SOURCES} Makefile
OBJECTS = ${SOURCES:.cc=.o}
EXECBIN = teststack
TESTOUT = teststack.output

all : ${EXECBIN}
	- checksource ${ALLSRCS}

${EXECBIN} : ${OBJECTS}
	${COMPILE} -o ${EXECBIN} ${OBJECTS}

%.o : %.cc
	${COMPILE} -c $<

spotless : clean
	- rm ${EXECBIN} ${DEPFILE}

clean :
	- rm ${OBJECTS} ${TESTOUT}

ci : ${ALLSRCS}
	cid + ${ALLSRCS}

lis : test
	mkpspdf Listing.ps ${ALLSRCS} ${DEPFILE} \
	        ${TESTOUT} ${EXECBIN}.errs

test : ${EXECBIN}
	bcheck -leaks ${EXECBIN} ${ALLSRCS} >${TESTOUT}

${DEPFILE} :
	@ echo "# ${DEPFILE} created `LC_TIME=C date`" >${DEPFILE}
	${MAKEDEP} ${SOURCES} >>${DEPFILE}

test : ${EXECBIN}

include ${DEPFILE}

