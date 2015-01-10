OBJS=../lib/network.o ../lib/matlab.o fn.o
CC=gcc
CFLAGS=-g
LIB=-lm

fn:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fn
	
fn.o:fn.c ../include/mystd.h
	$(CC) -c $(CFLAGS) fn.c -o fn.o	
	
clean:
	rm -rf *.o fn