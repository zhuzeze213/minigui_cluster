OBJS=network.o matlab.o feclib.o fec.o
CC=gcc
CFLAGS=-c -g
LIB=-lm

fec:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fec
	
network.o:network.c mystd.h
	$(CC) $(CFLAGS) network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) $(CFLAGS) matlab.c -o matlab.o
	
feclib.o:feclib.c mystd.h
	$(CC) $(CFLAGS) feclib.c -o feclib.o

fec.o:fec.c mystd.h
	$(CC) $(CFLAGS) fec.c -o fec.o

clean:
	rm -rf *.o fec
