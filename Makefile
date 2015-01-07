LIB=-lpthread -lminigui_ths -ljpeg -lpng -lz -lm -ldl
CC=gcc
CFLAGS=-c
OBJS=main.o menu.o button.o listbox.o

main:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o main

button.o:button.c button.h
	$(CC) $(CFLAGS) button.c -o button.o

listbox.o:listbox.c listbox.h
	$(CC) $(CFLAGS) listbox.c -o listbox.o
	
menu.o:menu.c menu.h
	$(CC) $(CFLAGS) menu.c -o menu.o
	
main.o:main.c menu.h myarg.h button.h
	$(CC) $(CFLAGS) main.c -o main.o
	
clean:
	rm -rf *.o main
