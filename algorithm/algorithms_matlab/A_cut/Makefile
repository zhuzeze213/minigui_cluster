OBJS=../lib/network.o ../lib/matlab.o ../lib/eig.o acut.o
CC=gcc
CFLAGS=-g
LIB=-lm

acut:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o acut

acut.o:acut.c ../include/mystd.h
	$(CC) $(CFLAGS) -c acut.c -o acut.o
	
clean:
	rm -rf *.o acut
