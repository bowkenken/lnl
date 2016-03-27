#!/bin/sh

./configure
make clean
make
# make install

cd src/xlnl

./make-ln

wsbuilder.sh xlnl.prj &
