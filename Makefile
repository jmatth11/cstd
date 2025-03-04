CC=gcc
CFLAGS=-Wall -O2 -std=c11
LIBS=-L./deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a -lm -lpthread
OBJ=obj
BIN=lib
INCLUDES=-I. -I./deps/utf8-zig/headers/
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*' -not -path './libs/*' -not -path './tests/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -maxdepth 3 -name Makefile -printf '%h\n' | grep -v 'tests' | grep -v '^.$$')
SHARED=libcustom_std.so
ARCHIVE=libcustom_std.a

.PHONY: all
all: deps archive

.PHONY: install_deps
install_deps:
	$(shell ./install_deps.sh)
	@echo "deps installed."

.PHONY: archive
archive: $(OBJECTS)
	@mkdir -p $(BIN)
	gcc -shared -fPIC -o $(BIN)/$(SHARED) $^ $(LIBS)
	ar -rcs $(BIN)/$(ARCHIVE) $^

.PHONY: debug
debug: deps_debug debug_archive

.PHONY: debug_archive
debug_archive: $(DEBUG_OBJECTS)
	@mkdir -p $(BIN)
	gcc -shared -fPIC -o $(BIN)/$(SHARED) $^ $(LIBS)
	ar -rcs $(BIN)/$(ARCHIVE) $^

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS) $(INCLUDES)

$(OBJ)/%-debug.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -ggdb -c -fPIC -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null

.PHONY: deps
deps: install_deps
	@for i in $(DEPS); do\
		cd $${i} && $(MAKE) && cd -;\
	done

.PHONY: deps_debug
deps_debug: install_deps
	@for i in $(DEPS); do\
		cd $${i} && ($(MAKE) debug || $(MAKE)) && cd -;\
	done

