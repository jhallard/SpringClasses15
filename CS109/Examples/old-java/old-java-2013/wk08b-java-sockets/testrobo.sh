#!/bin/sh
roboclient localhost 50000 java 3 10 this is a java test &
roboclient localhost 50000 C++ 2 10 C++ C++ C++ C++ &
roboclient localhost 50000 slowpoke 10 5 this is a slow client &
