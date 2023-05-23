#!/bin/bash
rm bulid -r
mkdir bulid
cd bulid
cmake -DCMAKE_TOOLCHAIN_FILE=../arm_linux_setup.cmake ..
cmake ..
make
cp app ~/nfs_rootfs
