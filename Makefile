DESTDIR   := build

CFLAGS    := -Wall -Wextra -O2

RM        := rm -rf
MAKEFLAGS := --no-print-directory

all: pr02

pr02: lib_simple_computer
	$(MAKE) -C console CFLAGS="$(CFLAGS)" DESTDIR="../$(DESTDIR)" LIB="../mySimpleComputer/build/mySimpleComputer.a"

lib_simple_computer:
	$(MAKE) -C mySimpleComputer CC="$(CC)" CFLAGS="$(CFLAGS)"

clean:
	find . -type f -name "*.o" -o -name "*.a" -o -name "*.so" -o -name "*.out" | xargs $(RM)
	find . -type d -name "build" -o -name "bin" | xargs $(RM)

format:
	find . -type f -name '*.[ch]' -o -name '*.cpp' -o -name '*.hpp' | xargs clang-format --style=file:.clang-format -sort-includes -i --verbose

re:
	$(MAKE) clean
	$(MAKE) all

.PHONY : all test clean format re
