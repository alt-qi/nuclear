# nuclear
TRD for std::nuclear team...

## Moscow ICPC notes

The PDF includes the [theory notes](include/notes/theory.md) and
[problem-solving patterns](include/notes/problem-solving.md).
[Advanced topics](docs/moscow/advanced-theory.md) are available for preparation.
The [contest archive and sources](https://github.com/alt-qi/nuclear/tree/trd/moscow-2016-2025/docs/moscow)
cover the 2016–2025 Moscow ICPC contests.

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
a centered `std::nuclear` title with yellow colons and a two-column table of
contents on the same first page,
numbered sections and C++ syntax highlighting. Every page shows the university
and team at the top left and its page number at the top right. This command
does not run CMake. Typst is not required for the ordinary `make` command.
Markdown entries use cmarker 0.1.10 and MiTeX 0.2.7, downloaded automatically
from Typst Universe on the first Markdown build (internet access is required
until the packages are cached). Code-only documents need no external packages.

Edit `trd.yaml` to set the title, university, team, sections and source files.

```yaml
title: "std::nuclear — TRD"
university: "NRNU MEPhI"
team: "std::nuclear"
sections:
  - title: "Data structures"
    files:
      - title: "2D Fenwick tree"
        path: "include/algo/data_structures/fenwick_tree/fenwick_tree_2d.hpp"
```

Paths are relative to the repository root. Sections and files appear in YAML
order; files not listed are excluded.

### Markdown text

Add `.md` files to the same `files` list to include explanatory text:

```yaml
      - title: "Fenwick tree notes"
        path: "include/algo/data_structures/fenwick_tree/notes.md"
      - title: "2D Fenwick tree"
        path: "include/algo/data_structures/fenwick_tree/fenwick_tree_2d.hpp"
```

Markdown files are included in full, without TRD markers. They support paragraphs,
headings, emphasis, lists, links, tables, blockquotes, fenced code blocks, and
LaTeX formulas (`$...$` inline or `$$...$$` as a block). For example:

```markdown
# Complexity

An update takes **logarithmic time**: $O(\log n)$.

- Store partial sums in `tree`.
- Visit the next index with `i += i & -i`.
```

The YAML title remains the document subsection; Markdown headings are nested
under it (`#` becomes level 3). Local image paths are relative to the Markdown
file; download remote images before including them. Raw Typst inside HTML
comments is disabled.

### Source code

In each selected source file, mark the code to include:

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
