OBJS=network.o matlab.o fn.o
CC=gcc
CFLAGS=-g
LIB=-lm

fn:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fn
	
network.o:network.c mystd.h
	$(CC) -c $(CFLAGS) network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c $(CFLAGS) matlab.c -o matlab.o
	
fn.o:fn.c mystd.h
	$(CC) -c $(CFLAGS) fn.c -o fn.o	
	
clean:
	rm -rf *.o fn
