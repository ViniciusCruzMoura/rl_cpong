#!/bin/sh

set -xe

#CC='gcc'
#CFLAGS='-Wall -Wextra -std=c99 -g -D_DEBUG -Wpedantic -Wformat=2 -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs -O2'
#INCLUDE_PATHS = -I. -Iinclude
#LDFLAGS = -L. -Lsrc
#LDLIBS = -lraylib -lGL -lm -lpthread -ldl -lrt
#PROJECT_SOURCE_FILES='main.c'

#$CC $CFLAGS -o ./outmain vtut.c

#gcc -Wall -Wextra -ggdb -o ./outmain main.c

make #-B PLATFORM=PLATFORM_DESKTOP
