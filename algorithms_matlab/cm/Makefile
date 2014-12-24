OBJS=network.o matlab.o cm.o
CC=gcc
CFLAGS=-g
LIB=-lm

cm:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o cm
	
network.o:network.c mystd.h
	$(CC) -c -g network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c -g matlab.c -o matlab.o
	
cm.o:cm.c mystd.h
	$(CC) -c -g cm.c -o cm.o	
	
clean:
	rm -rf *.o cm
