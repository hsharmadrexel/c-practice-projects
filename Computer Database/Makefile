#=========================== \
 * Title: CS283 Assignment 4 Makefile \
 * Author: Harsh Sharma \
 * Purpose: Compile all the files in a single call and be able to clean them appropriately \
 * Date Modified: 4th August 2020 \
 * Notes: Look at README for compiling and running instructions \
===========================

CC=gcc
CFLAGS=-o

ccomp: db menu.o add.o item.o list.o del.o match.o year.o edit.o

db:
	touch ccomp.db

menu.o: ccmenu.c
	$(CC) $(CFLAGS) ccmenu ccmenu.c

add.o: ccadd.c
	$(CC) $(CFLAGS) ccadd ccadd.c

item.o: ccitem.c
	$(CC) $(CFLAGS) ccitem ccitem.c

list.o: cclist.c
	$(CC) $(CFLAGS) cclist cclist.c
   
del.o: ccdel.c
	$(CC) $(CFLAGS) ccdel ccdel.c

match.o: ccmatch.c
	$(CC) $(CFLAGS) ccmatch ccmatch.c

year.o: ccyear.c
	$(CC) $(CFLAGS) ccyear ccyear.c

edit.o: ccedit.c 
	$(CC) $(CFLAGS) ccedit ccedit.c

clean: 
	find . -perm +100 -type f -delete
	rm ccomp.db