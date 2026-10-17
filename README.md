# nuclear
TRD for std::nuclear team...

## Requirements

- A C++20 compiler
- CMake 3.20 or newer
- Make
- clang-format

An internet connection is required on the first build to download GoogleTest.

## Build

Run from the repository root:

```sh
make
```

This configures CMake and builds the project in `build/`. Subsequent runs rebuild
only what has changed.

## Running tests

```sh
make test
```

This builds the project first, then runs the tests, including formatting checks.
Failed test output is printed automatically.

## Auto-formatting

```sh
make format
```

## Cleaning

```sh
make clean
```

This removes `build/`. The next build configures everything again.

## Using CMake directly

The Makefile is a shortcut for the usual CMake workflow, which is also supported:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```
