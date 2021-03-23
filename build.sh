#!/bin/bash
mkdir -p build
meson setup build --buildtype=debug
cd build
ninja
cd ..