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

#gcc -c src/main.c -o src/main.o -std=c99 -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE -g -D_DEBUG -D_DEFAULT_SOURCE -I. -I/home/viniciusmoura/workspaces/probe/rl_cpong/lib/raylib/src -I/home/viniciusmoura/workspaces/probe/rl_cpong/lib/raylib/src/external -I/home/viniciusmoura/workspaces/probe/rl_cpong/lib/raylib/src/extras -Iinclude -I/usr/local/include -DPLATFORM_DESKTOP
make -B PLATFORM=PLATFORM_DESKTOP RAYLIB_PATH=lib/raylib
