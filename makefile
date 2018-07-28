# the compiler: gcc for C program, define as g++ for C++
CC = icpc
# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -g -Wall -std=c++0x -larmadillo

all: aout

aout: fssh.C fssh.h lib.C lib.h
	$(CC) $(CFLAGS) -o aout fssh.C lib.C

clean:
	$(RM) aout 


