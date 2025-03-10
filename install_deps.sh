#!/bin/bash
which zig > /dev/null
if [ $? -ne 0 ]; then
  sudo apt install -y snapd
  sudo snap install zig --classic --beta
fi

if [ ! -d ./deps/utf8-zig ]; then
  git clone https://github.com/jmatth11/utf8-zig.git deps/utf8-zig
fi
