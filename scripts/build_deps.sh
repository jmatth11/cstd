#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

if [ ! -d "$SCRIPT_DIR/../deps/utf8-zig" ]; then
  git clone https://github.com/jmatth11/utf8-zig.git "$SCRIPT_DIR/../deps/utf8-zig"
  cd "$SCRIPT_DIR/../deps/utf8-zig"
  make
  zig build -Doptimize=ReleaseFast
  cd -
else
  cd "$SCRIPT_DIR/../deps/utf8-zig"
  make
  zig build -Doptimize=ReleaseFast
  cd -
fi
