.DEFAULT_GOAL := all

.PHONY: all configure build format typst clean

all: build

configure:
	cmake -S . -B build

build: configure
	cmake --build build

format: configure
	cmake --build build --target format

typst:
	@command -v typst >/dev/null 2>&1 || { echo "Typst CLI is required. See README.md for installation." >&2; exit 1; }
	mkdir -p build
	typst compile trd.typ build/trd.pdf

clean:
	rm -rf build
