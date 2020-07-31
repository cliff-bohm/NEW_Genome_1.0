#!/bin/bash

BUILD=$1
TYPE=$2

# compile
cmake ../$BUILD && make

# move out of file
rm "cmake_install.cmake"
rm "CMakeCache.txt"
rm -r "CMakeFiles"
rm -r "Makefile"
rm -r "Genomes"
# find . -type d -name "CMakeFiles" -exec rm -rf {} \;

