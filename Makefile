CC=clang
CFLAGS=-Wall -O2 -std=c11
WEB_FLAGS=-D__EMSCRIPTEN__=1
LIBS=-L./deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a -lm -lpthread
WEB_LIBS=-L./deps/utf8-zig/zig-out/lib/ -lwebutf8-zig
WASI_LIB=./deps/wasi-libc/build
OBJ=obj
BIN=lib
INCLUDES=-I. -I./deps/utf8-zig/headers/ -I/usr/include/x86_64-linux-gnu -I/usr/include
SOURCES=$(shell find . -name '*.c' -not -path './plugins/*' -not -path './deps/*' -not -path './libs/*' -not -path './tests/*')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))
DEBUG_OBJECTS=$(patsubst %.c, $(OBJ)/%-debug.o, $(SOURCES))
DEPS=$(shell find . -maxdepth 3 -name Makefile -printf '%h\n' | grep -v 'tests' | grep -v '^.$$' | grep -v 'wasi')
SHARED=libcustom_std.so
ARCHIVE=libcustom_std.a

.PHONY: all
all: deps archive

.PHONY: install_deps
install_deps:
	./install_deps.sh
	@echo "deps installed."

.PHONY: install_web_deps
install_web_deps: deps
	./install_web_deps.sh
	@echo "deps installed."

.PHONY: archive
archive: $(OBJECTS)
	@mkdir -p $(BIN)
	$(CC) -shared -fPIC -o $(BIN)/$(SHARED) $^ $(LIBS)
	ar -rcs $(BIN)/$(ARCHIVE) $^

.PHONY: web
web: install_web_deps $(SOURCES)
	$(CC) $(WEB_FLAGS) $(INCLUDES) $(WEB_LIBS) --target=wasm32-unknown-wasi --sysroot $(WASI_LIB) -nostartfiles -Wl,--import-memory -Wl,--export-all -Wl,--no-entry -o libcustom_std.wasm $^

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
	$(foreach dir, $(DEPS), $(shell cd $(dir) && $(MAKE)))

.PHONY: deps_debug
deps_debug: install_deps
	@for i in $(DEPS); do\
		cd $${i} && ($(MAKE) debug || $(MAKE)) && cd -;\
	done

