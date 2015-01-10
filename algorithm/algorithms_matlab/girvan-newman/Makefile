OBJS=../lib/network.o ../lib/matlab.o gn.o
CC=gcc
CFLAGS=-g
LIB=-lm

gn:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o gn
	
gn.o:gn.c ../include/mystd.h
	$(CC) -c $(CFLAGS) gn.c -o gn.o	
	
clean:
	rm -rf *.o gn