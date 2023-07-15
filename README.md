# ud

Which UNIX day is it today? `ud` can let you know!

This README.md file was written on UNIX day `19553` (which is `2023-07-15`).

UNIX day `20000` is at `2024-10-04` (the 4th of October), and should surely be celebrated!

### The `ud` utility can

* Output the UNIX day number for today.
* Take a UNIX day number and return the corresponding date.
* Take a date and return the UNIX day number.

## Build

### With CMake and Ninja

    cmake -S . -B build -G Ninja
    ninja -C build

### With gcc

    gcc -std=c18 -O2 -D_GNU_SOURCE -o ud main.c

## Install

### On Linux, using sudo

    sudo install -Dm755 ud /usr/bin/ud

### On FreeBSD, using doas

    doas install -d /usr/local/bin
    doas install -m755 ud /usr/local/bin/ud

## General info

* Version: 1.0.0
* License: BSD-3
* Author: Alexander F. Rødseth &lt;xyproto@archlinux.org&gt;
