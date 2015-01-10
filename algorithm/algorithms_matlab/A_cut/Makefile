OBJS=network.o matlab.o fcm.o acut.o
CC=gcc
CFLAGS=-g
LIB=-lm

acut:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o acut

acut.o:acut.c mystd.h
	$(CC) -c acut.c -o acut.o
	
network.o:network.c mystd.h
	$(CC) -c network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c matlab.c -o matlab.o
	
fcm.o:fcm.c mystd.h
	$(CC) -c fcm.c -o fcm.o	
	
clean:
	rm -rf *.o acut