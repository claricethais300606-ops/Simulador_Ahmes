CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -pedantic -Isrc/nucleo -Isrc/interface
SOURCES = $(wildcard src/*.c src/nucleo/*.c src/interface/*.c tests/*.c)

.PHONY: all test clean
all: build/ahmes

build/ahmes: $(SOURCES)
	@mkdir -p build
	$(CC) $(CFLAGS) $(SOURCES) -o $@

test: build/ahmes
	./build/ahmes --testes

clean:
	rm -rf build
