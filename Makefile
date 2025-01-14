.PHONY: all run clean

PLATFORM ?= PLATFORM_DESKTOP
PROJECT_NAME ?= game
# Locations of raylib.h and libraylib.a/libraylib.so
# NOTE: Those variables are only used for PLATFORM_OS: LINUX
RAYLIB_INCLUDE_PATH ?= /usr/local/include
RAYLIB_LIB_PATH ?= /usr/local/lib
# Library type compilation: STATIC (.a) or SHARED (.so/.dll)
RAYLIB_LIBTYPE ?= STATIC
BUILD_MODE ?= DEBUG #RELEASE

ifeq ($(shell uname),Linux)
	PLATFORM_OS = LINUX
endif

CC = gcc
MAKE ?= make

CFLAGS = -std=c99 -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE
CFLAGS += -Wextra -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes
CFLAGS += -Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs
ifeq ($(BUILD_MODE),DEBUG)
    CFLAGS += -g -D_DEBUG
else
    CFLAGS += -s -O2
endif
ifeq ($(PLATFORM_OS),LINUX)
	ifeq ($(RAYLIB_LIBTYPE),STATIC)
		CFLAGS += -D_DEFAULT_SOURCE
	endif
	ifeq ($(RAYLIB_LIBTYPE),SHARED)
		CFLAGS += -Wl,-rpath
	endif
endif

# Define include paths for required headers: INCLUDE_PATHS
# NOTE: Some external/extras libraries could be required (stb, physac, easings...)
INCLUDE_PATHS = -I. -Iinclude -Iexternal/raylib/include
ifeq ($(PLATFORM_OS),LINUX)
	INCLUDE_PATHS += -I$(RAYLIB_INCLUDE_PATH)
endif

LDFLAGS = -L. -Lexternal/raylib/lib
ifeq ($(PLATFORM_OS),LINUX)
	LDFLAGS += -L$(RAYLIB_LIB_PATH)
	LDLIBS = -l:libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
	ifeq ($(RAYLIB_LIBTYPE),SHARED)
		LDLIBS += -lc
	endif
endif

PROJECT_SOURCE_FILES := \
    $(wildcard src/*.c) \
    $(wildcard src/**/*.c) \
    $(wildcard tests/*.c) \
    $(wildcard tests/**/*.c) \

OBJS = $(patsubst %.c, %.o, $(PROJECT_SOURCE_FILES))
MAKEFILE_PARAMS = $(PROJECT_NAME)

all:
	$(MAKE) $(MAKEFILE_PARAMS)

$(PROJECT_NAME): $(OBJS)
	$(CC) -o $(PROJECT_NAME)$(EXT) $(OBJS) $(CFLAGS) $(INCLUDE_PATHS) $(LDFLAGS) $(LDLIBS) -D$(PLATFORM)

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS) $(INCLUDE_PATHS) -D$(PLATFORM)

run:
	$(MAKE) $(MAKEFILE_PARAMS)

clean:
	rm -f $(wildcard src/*.o) $(wildcard src/**/*.o) $(wildcard tests/*.o) $(wildcard tests/**/*.o)
