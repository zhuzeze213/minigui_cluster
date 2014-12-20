LIB=-lpthread -lminigui_ths -ljpeg -lpng -lz -lm -ldl
CC=gcc
CFLAGS=-c
OBJS=main.o menu.o

main:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o main

menu.o:menu.c menu.h
	$(CC) $(CFLAGS) menu.c -o menu.o
	
main.o:main.c menu.h myarg.h
	$(CC) $(CFLAGS) main.c -o main.o
	
clean:
	rm -rf *.o main