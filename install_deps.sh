#!/bin/bash
sudo apt install -y snapd
sudo snap install zig --classic --beta

if [ ! -d ./deps/utf8-zig ]; then
  git clone https://github.com/jmatth11/utf8-zig.git deps/utf8-zig
fi
