OBJS=network.o matlab.o sa.o
CC=gcc
CFLAGS=-c -g
LIB=-lm

sa:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o sa
	
network.o:network.c mystd.h
	$(CC) $(CFLAGS) network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) $(CFLAGS) matlab.c -o matlab.o

sa.o:sa.c mystd.h
	$(CC) $(CFLAGS) sa.c -o sa.o

clean:
	rm -rf *.o sa
