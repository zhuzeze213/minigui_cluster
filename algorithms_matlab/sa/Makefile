OBJS=../lib/network.o ../lib/matlab.o sa.o
CC=gcc
CFLAGS=-g
LIB=-lm

sa:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o sa
	
sa.o:sa.c ../include/mystd.h
	$(CC) -c $(CFLAGS) sa.c -o sa.o	
	
clean:
	rm -rf *.o sa