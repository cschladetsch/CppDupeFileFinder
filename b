#!/bin/bash

rm -rf build
mkdir build
cd build
cmake ..
make -j$(nproc)  # Build using all available cores for faster compilation
#./DuplicateFileFinderTest
./DuplicateFinderTest


