CC = g++
CFLAGS = -pedantic-errors -Wall -Wextra -Werror
INCLUDE = -I include/

SOURCE = $(wildcard src/*.cpp)

build/a.out: $(SOURCE)
	mkdir -p build
	$(CC) $(CFLAGS) $(INCLUDE) -o $@ $^


.PHONY: run

run:
	build/a.out