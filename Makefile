
OBJECTS = main.o \
		  rlcpong.o \
		  entity.o \
		  entity_manager.o \
		  inifile_parser.o \
		  render_window.o \
		  test.o

CC = gcc
MAKE = make

CFLAGS = -std=c99 -Wall -Wno-missing-braces -Wunused-result -D_DEFAULT_SOURCE \
	-Wextra -Wno-unused-parameter -Wshadow -Wwrite-strings -Wstrict-prototypes -Wmissing-prototypes \
	-Wold-style-definition -Wredundant-decls -Wnested-externs -Wmissing-include-dirs \
    -s -O2 -D_DEFAULT_SOURCE -Wl,-rpath

INCLUDE_PATHS = -Iinclude -Ivendor/raylib/src

LDFLAGS = -Lvendor/raylib/src -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lc

all: executable

# build main module
main.o: src/main.c include/rlcpong.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build rlcpong module
rlcpong.o: src/rlcpong.c include/rlcpong.h vendor/raylib/src/raylib.h vendor/raylib/src/raymath.h include/entity.h include/entity_manager.h include/inifile_parser.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build entity module
entity.o: src/entity.c include/entity.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build entity_manager module
entity_manager.o: src/entity_manager.c include/entity_manager.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build inifile_parser module
inifile_parser.o: src/inifile_parser.c include/inifile_parser.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build render_window module
render_window.o: src/render_window.c include/rlcpong.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build test module
test.o: tests/test.c include/rlcpong.h
	$(CC) -c $< $(CFLAGS) $(INCLUDE_PATHS)

# build the executable
executable: $(OBJECTS) libraylib.a
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# build raylib vendor
libraylib.a: vendor/raylib/src
	$(MAKE) -C $< PLATFORM=PLATFORM_DESKTOP

.PHONY: clean clean_vendor

clean:
	@rm -f $(OBJECTS)

clean_vendor:
	$(MAKE) -C vendor/raylib/src clean
