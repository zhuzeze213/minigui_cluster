OBJS=network.o matlab.o feclib.o fec.o
CC=gcc
CFLAGS=-g
LIB=-lm

fec:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fec
	
network.o:network.c mystd.h
	$(CC) -c -g network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c -g matlab.c -o matlab.o

feclib.o:feclib.c mystd.h
	$(CC) -c -g feclib.c -o feclib.o

fec.o:fec.c mystd.h
	$(CC) -c -g fec.c -o fec.o
	
clean:
	rm -rf *.o
