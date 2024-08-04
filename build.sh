#!/bin/sh
set -xe
#CFLAGS='-Wall -Wextra -std=c99 -g -D_DEBUG -Wpedantic -Wformat=2 -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -O2'
make #-B PLATFORM=PLATFORM_DESKTOP
