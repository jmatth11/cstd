#!/usr/bin/env bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

which zig > /dev/null
if [ $? -ne 0 ]; then
  sudo apt install -y snapd
  sudo snap install zig --classic --beta
fi
which wasm-ld > /dev/null
if [ $? -ne 0 ]; then
  sudo apt-get install -y lld
  # for 32 bit stub files needed to compile wasm32
  sudo apt-get install -y libc6-dev-i386
fi

if [ ! -d "$SCRIPT_DIR/../deps/utf8-zig" ]; then
  git clone https://github.com/jmatth11/utf8-zig.git "$SCRIPT_DIR/../deps/utf8-zig"
  cd "$SCRIPT_DIR/../deps/utf8-zig"
  make
  zig build -Doptimize=ReleaseFast
  cd -
fi

