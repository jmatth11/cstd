CC=gcc
CFLAGS=-Wall -g -fsanitize=address,undefined,leak
INCLUDES=-I../headers -I../deps/utf8-zig/headers
LIBS=../lib/libcustom_std.a -L../deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a -lm -lpthread

.PHONY: all
all: build

.PHONY: build
build:
	$(CC) $(CFLAGS) $(INCLUDES) -o tests main.c $(LIBS)

