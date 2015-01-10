OBJS=../lib/network.o ../lib/matlab.o isodata.o
CC=gcc
CFLAGS=-g
LIB=-lm

isodata:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o isodata
	
isodata.o:isodata.c ../include/mystd.h
	$(CC) -c $(CFLAGS) isodata.c -o isodata.o	
	
clean:
	rm -rf *.o isodata
