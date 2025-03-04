CC=gcc
CFLAGS=-Wall -g
INCLUDES=-I../headers -I../deps/utf8-zig/headers
LIBS=-L../lib/ -lcustom_std -lm -lpthread

.PHONY: all
all: build

.PHONY: build
build:
	$(CC) $(CFLAGS) $(INCLUDES) -o tests main.c $(LIBS)

