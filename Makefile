.DEFAULT_GOAL := all

.PHONY: all configure build format clean

all: build

configure:
	cmake -S . -B build

build: configure
	cmake --build build

format: configure
	cmake --build build --target format

clean:
	rm -rf build
