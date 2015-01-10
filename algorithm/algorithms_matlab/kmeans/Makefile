OBJS=../lib/network.o ../lib/matlab.o kmeans.o
CC=gcc
CFLAGS=-g
LIB=-lm

kmeans:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o kmeans
	
kmeans.o:kmeans.c ../include/mystd.h
	$(CC) -c $(CFLAGS) kmeans.c -o kmeans.o	
	
clean:
	rm -rf *.o kmeans