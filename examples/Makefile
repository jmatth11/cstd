CC=clang
CFLAGS=-Wall -Wextra -std=c11 -fsanitize=address,undefined,leak -I../ -I../deps/utf8-zig/headers -L../lib -lcustom_std

EXAMPLES=$(wildcard *.c)
BINARIES=$(EXAMPLES:.c=)

SRCS=../src
ARENA_SRC=$(SRCS)/arena.c
BASE_STR_SRC=$(SRCS)/base_str.c
CRYPT_SRC=$(SRCS)/crypt.c
GAP_BUFFER_SRC=$(SRCS)/gap_buffer.c
HASH_MAP_SRC=$(SRCS)/hash_map.c
LINKED_LIST_SRC=$(SRCS)/linked_list.c

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

gap_buffer_example: gap_buffer_example.c $(GAP_BUFFER_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(GAP_BUFFER_SRC)

hash_map_example: hash_map_example.c $(HASH_MAP_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(HASH_MAP_SRC)

linked_list_example: linked_list_example.c $(LINKED_LIST_SRC)
	$(CC) $(CFLAGS) -o $@ $< $(LINKED_LIST_SRC)

clean:
	rm -f $(BINARIES)
