LIB=-lpthread -lminigui_ths -ljpeg -lpng -lz -lm -ldl
CC=gcc
CFLAGS=-c
OBJS=main.o menu.o button.o listbox.o setpath.o propsheet.o edit.o combobox.o

main:$(OBJS)
	$(CC) $(OBJS) $(LIB) -o main

button.o:button.c button.h combobox.h myarg.h
	$(CC) $(CFLAGS) button.c -o button.o

listbox.o:listbox.c listbox.h
	$(CC) $(CFLAGS) listbox.c -o listbox.o

combobox.o:combobox.c combobox.h myarg.h
	$(CC) $(CFLAGS) combobox.c -o combobox.o
	
edit.o:edit.c listbox.h
	$(CC) $(CFLAGS) edit.c -o edit.o
	
setpath.o:setpath.c listbox.h
	$(CC) $(CFLAGS) setpath.c -o setpath.o
	
menu.o:menu.c menu.h
	$(CC) $(CFLAGS) menu.c -o menu.o
	
propsheet.o:propsheet.c propsheet.h
	$(CC) $(CFLAGS) propsheet.c -o propsheet.o
	
main.o:main.c menu.h myarg.h button.h propsheet.h
	$(CC) $(CFLAGS) main.c -o main.o
	
clean:
	rm -rf *.o main
