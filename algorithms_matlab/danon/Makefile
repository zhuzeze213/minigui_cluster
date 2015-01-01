OBJS=../lib/network.o ../lib/matlab.o danon.o
CC=gcc
CFLAGS=-g
LIB=-lm

danon:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o danon
	
danon.o:danon.c ../include/mystd.h
	$(CC) -c $(CFLAGS) danon.c -o danon.o	
	
clean:
	rm -rf *.o danon