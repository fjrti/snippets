#!/bin/bash

[ -z "$1" ] && exit -1

image="$1".img

[ -n "$D" -a "$D" == "1" ] && DEBUG="-s -S"
[ -n "$G" -a "$G" == "0" ] && CURSES=-curses

qemu-system-i386 $CURSES $DEBUG -m 129M -fda $image -boot a
