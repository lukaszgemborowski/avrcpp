#!/bin/bash

wget https://sunsite.icm.edu.pl/pub/gnu/binutils/binutils-2.32.tar.xz
wget https://sunsite.icm.edu.pl/pub/gnu/gcc/gcc-9.2.0/gcc-9.2.0.tar.xz
wget http://download.savannah.gnu.org/releases/avr-libc/avr-libc-2.0.0.tar.bz2
tar xvf binutils-2.32.tar.xz
tar xvf gcc-9.2.0.tar.xz
tar xvf avr-libc-2.0.0.tar.bz2

mkdir -p build/binutils
mkdir -p build/gcc
cd build/binutils
../../binutils-2.32/configure --prefix=/home/icek/opt --target=avr --disable-nls
make -j4
make install
cd ../gcc
../../gcc-9.2.0/configure --prefix=/home/icek/opt --target=avr --enable-languages=c,c++ \
    --disable-nls --disable-libssp --with-dwarf2
make -j4
make install
