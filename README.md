# ud

Which UNIX day is it today? `ud` can let you know!

UNIX days are calculated from the current UNIX time, which is the number of seconds since January 1st, 1970 at 00:00:00 UTC.

UNIX day `20000` is at **2024**-10-04 (the 4th of October). It's a special day, since the next round UNIX day is `30000` at **2052**-02-20.

This README.md file was written on UNIX day `19553` (which is 2023-07-15).

### The `ud` utility can

* Output the UNIX day for today.
* Take a UNIX day and return the corresponding date.
* Take a date and return the UNIX day.

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

* Version: 1.0.1
* License: BSD-3
* Author: Alexander F. Rødseth &lt;xyproto@archlinux.org&gt;
