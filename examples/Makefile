CC=clang
CFLAGS=-Wall -Wextra -std=c11 -fsanitize=address,undefined,leak -I../ -L../lib -lcustom_std

EXAMPLES=$(wildcard *.c)
BINARIES=$(EXAMPLES:.c=)

SRCS=../src
ARENA_SRC=$(SRCS)/arena.c
BASE_STR_SRC=$(SRCS)/base_str.c
CRYPT_SRC=$(SRCS)/crypt.c

.PHONY: all clean

all: $(BINARIES)

arena_example: arena_example.c $(ARENA_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(ARENA_SRC)

array_template_example: array_template_example.c
	$(CC) $(CFLAGS) -o $@ $<

base_str_example: base_str_example.c $(BASE_STR_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(BASE_STR_SRC)

crypt_example: crypt_example.c $(CRYPT_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(CRYPT_SRC)

clean:
	rm -f $(BINARIES)
