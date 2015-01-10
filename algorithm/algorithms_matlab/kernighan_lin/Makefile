OBJS=../lib/network.o ../lib/matlab.o kl.o
CC=gcc
CFLAGS=-g
LIB=-lm

kl:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o kl
	
kl.o:kl.c ../include/mystd.h
	$(CC) -c $(CFLAGS) kl.c -o kl.o	
	
clean:
	rm -rf *.o kl