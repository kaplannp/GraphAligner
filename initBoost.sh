#!/usr/bin/bash
set -e 

cd include/boost
./bootstrap.sh --prefix=.
./b2 --prefix=.
