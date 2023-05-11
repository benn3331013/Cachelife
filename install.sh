#!/bin/bash

# SDL2
# Clone the repo
git clone https://github.com/libsdl-org/SDL.git --branch SDL2
cd SDL
# Build SDL2
./configure --prefix=$PWD/..
make all
sudo make install
cd ..

# GMP
# untar the archive
tar -xf gmp-6.2.1.tar.xz
cd gmp-6.2.1

# Build GMP 6.2.1
./configure --prefix=$PWD/..
make
make check
make install