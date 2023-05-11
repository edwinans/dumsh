CC=gcc
CFLAGS= -g -Wall -o

.PHONY:all
all: dumsh

dumsh:dumsh.c
	$(CC)  $(CFLAGS)  dumsh dumsh.c

.PHONY:clean
clean:
	@rm -rf *.o *.out dumsh
