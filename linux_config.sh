#! /bin/sh

sudo git clone https://github.com/riscv/riscv-gnu-toolchain

sudo apt-get install autoconf automake autotools-dev curl python3 libmpc-dev libmpfr-dev libgmp-dev gawk build-essential bison flex texinfo gperf libtool patchutils bc zlib1g-dev libexpat-dev ninja-build

cd riscv-gnu-toolchain

sudo ./configure --prefix=/opt/riscv

sudo make linux

export PATH=$PATH:.

cd ..
