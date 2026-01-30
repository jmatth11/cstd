# Custom Standard (CSTD) C Library

This is my collection of C functions and data structures I commonly use in my projects.

I do not guarantee that they are implemented the best but they meet the needs I have
and are useful in the ways I like.

Currently List of Features:

- Arena allocator `arena.h`
- Type safe Dynamic array `array_template.h`
- Basic String structure `base_str.h`
- Unicode string structure `unicode_str.h`
- Crypto functionality (not much currently) `crypto`
- Preprocessor defines `defs.h`
- File operations `file_ops.h`
- Gap buffer implementation `gap_buffer.h`
- Hash map `hash_map.h`
- Linked List `linked_list.h`
- Simple Logging functions `log.h`
- Magic preprocessor functions (like DEFER) `magic.h`
- OS functions `os.h`
- Simple queue implementation `queue.h`
- String operations `string.h`

Other functionality not included in this repo:

WebSockets - https://github.com/jmatth11/websocket-c

## Build

There are two ways to build. A Makefile way or a Zig way.

### Makefile

Build the static and shared library:
```bash
make
```

Build in Release mode add `RELEASE=1` or you can build in debug mode with `DEBUG=1`.

### Zig Build

Build a static library and wasm64 library in debug mode with:
```bash
zig build
```

Build shared library:
```bash
zig build -Dlinkage=dynamic
```

Build in release mode:
```bash
zig build -Doptimize=ReleaseSafe
```

