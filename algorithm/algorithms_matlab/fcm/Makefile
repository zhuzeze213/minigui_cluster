OBJS=network.o matlab.o fcm.o
CC=gcc
CFLAGS=-g
LIB=-lm

fcm:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o fcm
	
network.o:network.c mystd.h
	$(CC) -c network.c -o network.o

matlab.o:matlab.c mystd.h
	$(CC) -c matlab.c -o matlab.o
	
fcm.o:fcm.c mystd.h
	$(CC) -c fcm.c -o fcm.o	
	
clean:
	rm -rf *.o fcm