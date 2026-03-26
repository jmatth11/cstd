CC=clang
CFLAGS=-Wall -std=c11 -march=native
WEB_FLAGS=-D__EMSCRIPTEN__=1
LIBS=-L./deps/utf8-zig/zig-out/lib/ -l:libutf8-zig.a -lm -lpthread
WEB_LIBS=-L./deps/utf8-zig/zig-out/lib/ -lwebutf8-zig
WASI_LIB=./deps/wasi-libc/build
INCLUDES=-I. -I./deps/utf8-zig/headers/ -I/usr/include/x86_64-linux-gnu -I/usr/include

SOURCES=$(shell find ./src -name '*.c')
OBJECTS=$(addprefix $(OBJ)/,$(SOURCES:%.c=%.o))

TARGET=libcustom_std
OBJ=obj
BIN=lib

# setup up conditional build flags
# if debug is set to 1, add debug specific flags
ifeq ($(DEBUG), 1)
	CFLAGS += -DDEBUG=1 -ggdb
endif
# Release specific flags
ifeq ($(RELEASE), 1)
	CFLAGS += -O2
else
	CFLAGS += -fsanitize=undefined
endif

.PHONY: all
all: archive

.PHONY: archive
archive: $(OBJECTS)
	@mkdir -p $(BIN)
	$(CC) -shared -fPIC -o $(BIN)/$(TARGET).so $^ $(LIBS)
	ar -rcs $(BIN)/$(TARGET).a $^

.PHONY: web
web: $(SOURCES)
	$(CC) $(WEB_FLAGS) $(INCLUDES) $(WEB_LIBS) --target=wasm32-unknown-wasi --sysroot $(WASI_LIB) -nostartfiles -Wl,--import-memory -Wl,--export-all -Wl,--no-entry -o libcustom_std.wasm $^

$(OBJ)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS) $(INCLUDES)

.PHONY: clean
clean:
	@rm -rf $(OBJ)/* 2> /dev/null
	@rm -f $(BIN)/* 2> /dev/null
