OBJS=network.o matlab.o fcm.o ncut.o
CC=gcc
CFLAGS=-g
LIB=-lm

ncut:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o ncut

ncut.o:ncut.c mystd.h
	$(CC) -c ncut.c -o ncut.o
	
network.o:network.c mystd.h
	$(CC) -c network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c matlab.c -o matlab.o
	
fcm.o:fcm.c mystd.h
	$(CC) -c fcm.c -o fcm.o	
	
clean:
	rm -rf *.o ncut