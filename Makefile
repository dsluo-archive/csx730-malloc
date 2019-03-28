CC=gcc
AS=as
CFLAGS=-std=c17 -g -Wall -O0 -pedantic-errors
RM=rm -f

.PHONY: clean all test

all: csx730_malloc.o

csx730_malloc.o: csx730_malloc.s
	$(AS) -o $@ $<

csx730_malloc.s: csx730_malloc.c csx730_malloc.h
	$(CC) $(CFLAGS) -S $<

clean:
	$(RM) *.o
	$(RM) *.s
	$(RM) -r doc

doc: $(wildcard *.c) $(wildcard *.h)
	mkdir -p doc
	doxygen