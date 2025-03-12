#!/bin/bash
which zig > /dev/null
if [ $? -ne 0 ]; then
  sudo apt install -y snapd
  sudo snap install zig --classic --beta
fi
which wasm-ld > /dev/null
if [ $? -ne 0 ]; then
  sudo apt-get install -y lld
  sudo apt-get install libc6-dev-i386
fi

if [ ! -d ./deps/utf8-zig ]; then
  git clone https://github.com/jmatth11/utf8-zig.git deps/utf8-zig
fi
if [ ! -d ./deps/wasi-libc ]; then
  git clone https://github.com/CraneStation/wasi-libc.git deps/wasi-libc
  cd deps/wasi-libc
  make install INSTALL_DIR=./build
  cd -
fi
