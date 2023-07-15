#!/bin/sh
ver=1.0.0
mkdir ud-$ver
cp -v main.c CMakeLists.txt LICENSE README.md ud-$ver/
tar zcvf ud-$ver.tar.gz ud-$ver/
rm -r ud-$ver/
