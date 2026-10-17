.DEFAULT_GOAL := all

.PHONY: all configure build test format clean

all: build

configure:
	cmake -S . -B build

build: configure
	cmake --build build

test: build
	ctest --test-dir build --output-on-failure

format: configure
	cmake --build build --target format

clean:
	rm -rf build
