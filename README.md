# nuclear
TRD for std::nuclear team...

## Requirements

- A C++20 compiler
- CMake 3.15 or newer
- Make
- clang-format (only for `make format`)

## Build

Run from the repository root:

```sh
make
```

This configures CMake in `build/` and runs the build. The TRD currently consists
only of headers, so there are no compilation targets or dependencies to download.

## Auto-formatting

```sh
make format
```

## Cleaning

```sh
make clean
```

This removes `build/`. The next build configures everything again.
