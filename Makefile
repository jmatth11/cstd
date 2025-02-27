CC=gcc
CFLAGS=-Wall -O2 -Wextra -std=c11
LIBS=-L./deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a -lm -lpthread
OBJ=obj
BIN=lib
INCLUDES=-I. -I./deps/utf8-zig/headers/
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*' -not -path './libs/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -maxdepth 3 -name Makefile -printf '%h\n' | grep -v 'unittest' | grep -v '^.$$')
TARGET=libcustom_std.a

.PHONY: all
all: deps archive

.PHONY: install_deps
install_deps:
	$(shell ./install_deps.sh)

.PHONY: archive
archive: $(OBJECTS)
	@mkdir -p $(BIN)
	ar -r $(BIN)/$(ARCHIVE_NAME) $^

.PHONY: debug
debug: deps_debug debug_archive

.PHONY: debug_archive
debug_archive: $(DEBUG_OBJECTS)
	@mkdir -p $(BIN)
	ar -r $(BIN)/$(ARCHIVE_NAME) $^

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -o $@ $< $(CFLAGS) $(INCLUDES)

$(OBJ)/%-debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -ggdb -c -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null

.PHONY: deps
deps:
	@for i in $(DEPS); do\
		cd $${i} && $(MAKE) && cd -;\
	done

.PHONY: deps_debug
deps_debug:
	@for i in $(DEPS); do\
		cd $${i} && ($(MAKE) debug || $(MAKE)) && cd -;\
	done

