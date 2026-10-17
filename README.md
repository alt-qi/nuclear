# nuclear
TRD for std::nuclear team...

## Source layout

Algorithms are grouped by topic under `include/algo/`:

```text
include/algo/
├── data_structures/
│   ├── fenwick_tree/
│   ├── splay_tree/
│   └── link_cut_tree.hpp
└── strings/
    └── dynamic_aho_corasick/
```

Use `snake_case` for source file and directory names.

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

The result is `build/trd.pdf`: a landscape A4 document with two code columns,
a table of contents, numbered sections and C++ syntax highlighting. This command does not
run CMake. Typst is not required for the ordinary `make` command; no external
Typst packages or code-generation scripts are used.

Edit `trd.yaml` to choose the document's title, sections and source files:

```yaml
title: "std::nuclear — TRD"
sections:
  - title: "Data structures"
    files:
      - title: "2D Fenwick tree"
        path: "include/algo/data_structures/fenwick_tree/fenwick_tree_2d.hpp"
```

Paths are relative to the repository root. Sections and files appear in YAML
order; files not listed are excluded. In each selected source file, mark the
code to include:

```cpp
/// &TRD_BEGIN
/// @author someone
/// @brief Description of the algorithm and its purpose.
/// @date 2026-10-17
/// @note How the code was tested.

// <code included in the document>
/// &TRD_END
```

Every TRD fragment must include the following documentation inside its markers:

- `@author`: the author of the implementation (name or handle).
- `@brief`: a short description of the algorithm and its purpose.
- `@date`: the date of the documented implementation in `YYYY-MM-DD` format.

Write these as `///` comments without a colon after the tag, as shown above.
This is a contribution requirement; the build does not validate these fields.

Markers must occupy separate lines, optionally surrounded by whitespace.
Multiple pairs per file are supported: their code is joined in source order
with a blank line between fragments. Indentation is preserved, LF and CRLF
line endings are supported, and the markers themselves are omitted.

Missing, nested or unbalanced markers and empty fragments stop the build with
the source path in the error message. Invalid configuration and missing files
also stop the build. Run `make typst` again after editing the YAML or code.
Document styling lives in `trd.typ`; `make clean` removes the generated PDF.

## Automatic PDF releases

The **Publish TRD** GitHub Actions workflow runs after every push to `main`.
It builds the PDF with `make typst` and creates or updates the single
[`trd-latest` release](https://github.com/alt-qi/nuclear/releases/tag/trd-latest).
The `trd.pdf` asset is replaced on each successful build; the release tag and
description point to the source commit used for that build.

[Download the current TRD PDF](https://github.com/alt-qi/nuclear/releases/download/trd-latest/trd.pdf).

To rebuild manually, open **Actions → Publish TRD → Run workflow** and select
`main`. Both automatic and manual runs build the current `main` branch.
The workflow uses Typst 0.15.1 and the built-in `GITHUB_TOKEN` with
`contents: write`; no additional repository secrets are required.
