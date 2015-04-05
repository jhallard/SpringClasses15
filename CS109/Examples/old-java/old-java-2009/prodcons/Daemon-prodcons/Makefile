# $Id: Makefile,v 1.1 2009-02-26 20:19:07-08 - - $

SOURCES    = ${wildcard *.java}
CLASSES    = ${SOURCES:.java=.class}
JARCLASSES = ${CLASSES:.class=*.class}
MAINCLASS  = main
JARFILE    = runsimulation

all : ${JARFILE}

${JARFILE} : ${CLASSES}
	echo Main-class: ${MAINCLASS} >Manifest
	jar cvfm ${JARFILE} Manifest ${JARCLASSES}
	chmod +x ${JARFILE}
	- rm Manifest

%.class : %.java
	cid + $<
	- checksource $<
	javac $<

