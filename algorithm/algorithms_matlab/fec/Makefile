OBJS=../lib/network.o ../lib/matlab.o fec.o
CC=gcc
CFLAGS=-g
LIB=-lm

fec:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fec
	
fec.o:fec.c ../include/mystd.h
	$(CC) -c $(CFLAGS) fec.c -o fec.o	
	
clean:
	rm -rf *.o fec
