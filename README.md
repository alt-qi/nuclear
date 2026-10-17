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

## Building the TRD document

Install the [Typst CLI](https://github.com/typst/typst#installation) (on macOS:
`brew install typst`), then run from the repository root:

```sh
make typst
```

The result is `build/trd.pdf`: an A4 document in one column, with a table of
contents, numbered sections and C++ syntax highlighting. This command does not
run CMake. Typst is not required for the ordinary `make` command; no external
Typst packages or code-generation scripts are used.

Edit `trd.yaml` to choose the document's title, sections and source files:

```yaml
title: "std::nuclear — TRD"
sections:
  - title: "Data structures"
    files:
      - title: "2D Fenwick tree"
        path: "include/algo/sem2/fenwick_tree/fenwick_tree_2d.hpp"
```

Paths are relative to the repository root. Sections and files appear in YAML
order; files not listed are excluded. In each selected source file, mark the
code to include:

```cpp
/* @TRD_BEGIN */
// Code included in the document.
/* @TRD_END */
```

Markers must occupy separate lines, optionally surrounded by whitespace.
Multiple pairs per file are supported: their code is joined in source order
with a blank line between fragments. Indentation is preserved, LF and CRLF
line endings are supported, and the markers themselves are omitted.

Missing, nested or unbalanced markers and empty fragments stop the build with
the source path in the error message. Invalid configuration and missing files
also stop the build. Run `make typst` again after editing the YAML or code.
Document styling lives in `trd.typ`; `make clean` removes the generated PDF.
