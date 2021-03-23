#!/bin/bash
# This source file is part of the aument project
# Copyright (c) 2021 the aument contributors
#
# Licensed under Apache License v2.0 with Runtime Library Exception
# See LICENSE.txt for license information

mkdir -p build
meson setup build --buildtype=debug || exit 1
cd build
ninja || exit 1
sudo meson install
cd ..
