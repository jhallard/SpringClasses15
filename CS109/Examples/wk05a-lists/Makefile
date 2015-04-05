# $Id: Makefile,v 1.4 2013-08-21 12:37:12-07 - - $

GPP = g++ -g -O0 -Wall -Wextra -std=gnu++0x
GRIND =  valgrind --leak-check=full --show-reachable=yes
SOURCES =  xlist.h testxlist.cpp Makefile

all : testxlist

testxlist : ${SOURCES}
	tput init
	${GPP} testxlist.cpp -o testxlist

ci : ${SOURCES}
	cid ${SOURCES}

out : testxlist
	${GRIND} testxlist 2>&1 | tee testxlist.output

clean :
	- rm testxlist testxlist.output

lis : out
	mkpspdf testxlist.ps ${SOURCES} testxlist.output

