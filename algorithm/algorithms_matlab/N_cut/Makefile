OBJS=../lib/network.o ../lib/matlab.o ../lib/eig.o ncut.o
CC=gcc
CFLAGS=-g
LIB=-lm

ncut:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o ncut

ncut.o:ncut.c ../include/mystd.h
	$(CC) $(CFLAGS) -c ncut.c -o ncut.o
	
clean:
	rm -rf *.o ncut
