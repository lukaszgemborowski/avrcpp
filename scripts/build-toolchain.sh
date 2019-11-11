#!/bin/bash

set -e

if [ -z "$1" ]; then
    echo "you need to pass install dir of the toolchain"
    exit 1
fi

PREFIX_DIR=$1

DIR_BINUTILS=binutils-2.32
FILE_BINUTILS=$DIR_BINUTILS.tar.xz

DIR_GCC=gcc-9.2.0
FILE_GCC=$DIR_GCC.tar.xz

DIR_LIBC=avr-libc-2.0.0
FILE_LIBC=$DIR_LIBC.tar.bz2

if [ ! -f $FILE_BINUTILS ]; then
    wget https://sunsite.icm.edu.pl/pub/gnu/binutils/$FILE_BINUTILS
fi

if [ ! -f $FILE_GCC ]; then
    wget https://sunsite.icm.edu.pl/pub/gnu/gcc/gcc-9.2.0/$FILE_GCC
fi

if [ ! -f $FILE_LIBC ]; then
    wget http://download.savannah.gnu.org/releases/avr-libc/$FILE_LIBC
fi

if [ ! -d $DIR_BINUTILS ]; then
    tar xvf $FILE_BINUTILS
fi

if [ ! -d $DIR_GCC ]; then
    tar xvf $FILE_GCC
fi

if [ ! -d $DIR_LIBC ]; then
    tar xvf $FILE_LIBC
fi

mkdir -p build/binutils
mkdir -p build/gcc
mkdir -p build/libc

cd build/binutils
../../$DIR_BINUTILS/configure --prefix=$PREFIX_DIR --target=avr --disable-nls
# TODO: run gmake on FreeBSD
make -j4
make install

cd ../gcc
../../$DIR_GCC/configure --prefix=$PREFIX_DIR --target=avr --enable-languages=c,c++ \
    --disable-nls --disable-libssp --with-dwarf2
make -j4
make install

cd ../libc
PATH=$PREFIX_DIR/bin:$PATH ../../$DIR_LIBC/configure --prefix=$PREFIX_DIR --build=`../../$DIR_LIBC/config.guess` --host=avr
make -j4
make install
