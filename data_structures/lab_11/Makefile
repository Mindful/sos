#################################################################
#
#  Makefile for Fibonacci Heap program, CS 4521, Fall, 2010
#
#  Files:
#  cmdint.cpp     The main program - the command interpreter
#
#  fibheap.h      The header file for the Fibonacci Heap class
#  fibheap.cpp    The implemention file for the Fibonacci Heap class
#
#  cmdint	  The executable program
#
#  Created by:    D. Dunham  November 14, 2010
#
##################################################################

CC = g++ 
DEBUG = -O

CFLAGS = $(DEBUG) -c

TARGETS = cmdint

all: $(TARGETS)


# Link the object files:

cmdint: cmdint.o fibheap.o
	$(CC) -o $@ cmdint.o fibheap.o


# Compile the C++ files into object files

cmdint.o: cmdint.cpp fibheap.h
	$(CC) $(CFLAGS) cmdint.cpp 

fibheap.o: fibheap.cpp fibheap.h
	$(CC) $(CFLAGS) fibheap.cpp 


# Remove all non-critical files with the command: %make clean

clean:
	rm -f *.o *~* *.a
	rm -f cmdint