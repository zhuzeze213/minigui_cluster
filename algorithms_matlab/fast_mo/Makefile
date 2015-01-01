OBJS=../lib/network.o ../lib/matlab.o fm.o
CC=gcc
CFLAGS=-g
LIB=-lm

fm:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fm
	
fm.o:fm.c ../include/mystd.h
	$(CC) -c $(CFLAGS) fm.c -o fm.o	
	
clean:
	rm -rf *.o fm