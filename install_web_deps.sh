#!/bin/bash

# for Makefile use

# function to link specific bin executables to a missing common name
function link_bin() {
  # find the executables
  args=$(find /usr/bin -name $1*)
  # ensure we only take one value (if there are multiple values)
  single_arg=$(echo $args | cut -d" " -f2)
  sudo ln -s $single_arg "/usr/bin/$1"
}

if [ ! -d ./deps/wasi-libc ]; then
  # this is to have a wasm compliant libc to link against
  git clone https://github.com/CraneStation/wasi-libc.git deps/wasi-libc
  cd deps/wasi-libc
  # this failed first time I did it
  # I needed to make symlinks to llvm-ar-14 -> llvm-ar and llvm-nm-14 -> llvm-nm
  # then everything was fine
  which llvm-ar > /dev/null
  if [ $? -ne 0 ]; then
    link_bin llvm-ar
  fi
  which llvm-nm > /dev/null
  if [ $? -ne 0 ]; then
    link_bin llvm-nm
  fi
  make install INSTALL_DIR=./build
  cd -
fi
