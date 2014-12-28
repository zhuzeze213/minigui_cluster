OBJS=../lib/network.o ../lib/matlab.o cm.o
CC=gcc
CFLAGS=-g
LIB=-lm

cm:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o cm
	
cm.o:cm.c ../include/mystd.h
	$(CC) -c $(CFLAGS) cm.c -o cm.o	
	
clean:
	rm -rf *.o cm
