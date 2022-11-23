#!/bin/bash

rm bulid -r
mkdir bulid
cd bulid
cmake ..
make
./server

