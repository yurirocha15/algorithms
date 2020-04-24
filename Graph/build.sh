#!/bin/sh

mkdir -p build
cd build
cmake ..
make all -j8
cd ..