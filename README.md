# Custom Standard (CSTD) C Library

A collection of reusable C utilities, data structures, and algorithms for
everyday programming.

## Features

### Memory
- **Arena allocator** - Fast bump allocator for temporary memory (`arena.h`)

### Data Structures
- **Dynamic array** - Type-safe resizable array (`array_template.h`)
- **Hash map** - Key-value dictionary (`hash_map.h`)
- **Linked list** - Doubly-linked list (`linked_list.h`)
- **Queue** - Simple FIFO queue (`queue.h`)
- **Gap buffer** - Text editor buffer (`gap_buffer.h`)

### Strings
- **Basic string** - Simple string type (`base_str.h`)
- **Unicode string** - UTF-8 string handling (`unicode_str.h`)
- **String operations** - Common string utilities (`string.h`)

### System
- **File operations** - File I/O helpers (`file_ops.h`)
- **OS functions** - Platform abstractions (`os.h`)

### Utilities
- **Logging** - Simple logging functions (`log.h`)
- **Preprocessor defines** - Common macros (`defs.h`)
- **Magic preprocessor** - DEFER and similar macros (`magic.h`)

### Crypto
- **Crypto** - Basic cryptographic utilities (`crypto/`)

## Other Libraries

Other useful libraries I've built out.
- [WebSockets](https://github.com/jmatth11/websocket-c) - WebSocket client
  implementation.

## Quick Start

Clone the repository to your dependency folder.

Build the project.
```bash
make RELEASE=1
```

Update your Makefile to include these flags
```bash
# link path to header files
-I<path to dependencies>/cstd/headers

# link path to library shared object
# Built with Makefile
-L<path to dependencies>/cstd/lib
# Built with Zig Build
-L<path to dependencies>/cstd/zig-out/lib

# include shared object
-lcustom_std
```

You should be able to import and use the library now.
```c
#include "hash_map.h"

int main(void) {
  struct hash_map_t *hm = hash_map_create(16);

  int *num1 = malloc(sizeof(int));
  *num1 = 42;

  (void)hash_map_set(hm, "number_one", num1);

  void *val = NULL;
  if (hash_map_get(hm, "number_one", &val)) {
    printf("number_one = %d\n", *(int *)val);
  }

  hash_map_destroy(&hm, true);
  return 0;
}
```

## Table of Contents

- [Install Deps](#install-deps)
- [Build](#build)
    - [Makefile](#makefile)
    - [Zig Build](#zig-build)
- [Test](#test)
- [Docs](#docs)
- [Examples](#examples)

## Install Deps

Run this script to install the necessary dependencies.

```bash
./scripts/install_deps.sh
```

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

## Test

You must [install deps](#install-deps) and [build](#build) the project first.
Then run this command to build and run the unit tests.

```bash
make test
```

## Docs

Install doxygen CLI tool.

```bash
sudo apt-get install -y doxygen
```

Then run this script to generate doxygen docs for this project.

```bash
./scripts/generate_docs.sh
```

Next you should be able to open the `doxygen/html/index.html` file to view the
docs.

## Examples

Examples live under the `examples/` directory.
To build examples you must [install deps](#install-deps) and [build](#build)
the project first.

Then you can navigate to the examples directory and run the Makefile.
```bash
make
```

To run the example follow this pattern:
```bash
LD_LIBRARY_PATH=../lib <example>
```
