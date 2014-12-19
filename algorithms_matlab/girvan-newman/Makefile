OBJS=network.o matlab.o gn.o
CC=gcc
CFLAGS=-g
LIB=-lm

gn:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o gn
	
network.o:network.c mystd.h
	$(CC) -c $(CFLAGS) network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c $(CFLAGS) matlab.c -o matlab.o
	
gn.o:gn.c mystd.h
	$(CC) -c $(CFLAGS) gn.c -o gn.o	
	
clean:
	rm -rf *.o gn