// Load Markdown packages only when a Markdown entry is included.
#let render-markdown(path, prefix) = {
  import "@preview/cmarker:0.1.10"
  import "@preview/mitex:0.2.7": mitex
  let directory = path.split("/").slice(0, -1).join("/")
  set image(width: 100%)
  // Notes use their own topic labels; keep inline expressions readable.
  set heading(numbering: none)
  show raw.where(block: false): set text(size: 9pt)
  cmarker.render(
    read(path),
    h1-level: 3,
    set-document-title: false,
    raw-typst: false,
    label-prefix: prefix + "-",
    math: mitex,
    scope: (
      image: (source, ..args) => image(
        if type(source) == str and not source.starts-with("/") {
          directory + "/" + source
        } else { source },
        ..args,
      ),
    ),
  )
}

// Extract only explicitly marked, non-nested regions. Keep code indentation intact.
#let extract-code(source, path) = {
  let open = none
  let lines = ()
  let fragments = ()
  let example = none
  for (index, line) in source.replace("\r\n", "\n").split("\n").enumerate() {
    let marker = line.trim()
    let location = path + ":" + str(index + 1)
    if marker in ("/// &TRD_BEGIN", "/// &TRD_EXAMPLE_BEGIN") {
      assert(open == none, message: location + ": nested TRD marker")
      open = marker
      lines = ()
    } else if marker in ("/// &TRD_END", "/// &TRD_EXAMPLE_END") {
      assert(open != none and marker == open.replace("_BEGIN", "_END"),
        message: location + ": unmatched TRD marker")
      let code = lines.join("\n")
      assert(code.trim() != "", message: location + ": empty TRD fragment")
      if marker == "/// &TRD_EXAMPLE_END" {
        assert(example == none, message: location + ": multiple usage examples")
        example = code
      } else {
        fragments.push(code)
      }
      open = none
    } else if open != none {
      lines.push(line)
    }
  }
  assert(open == none, message: path + ": unclosed TRD marker")
  assert(fragments.len() > 0, message: path + ": no TRD markers found")
  (implementation: fragments.join("\n\n"), example: example)
}

#let require-string(value, field) = {
  assert(type(value) == str, message: field + " must be a string")
  assert(value.trim() != "", message: field + " must not be empty")
  value
}

#let require-array(value, field) = {
  assert(type(value) == array, message: field + " must be an array")
  value
}

#let require-dictionary(value, field) = {
  assert(type(value) == dictionary, message: field + " must be a mapping")
  value
}

#let config = require-dictionary(yaml("trd.yaml"), "trd.yaml")
#let title = require-string(config.at("title", default: none), "title")
#let university = require-string(config.at("university", default: none), "university")
#let team = require-string(config.at("team", default: none), "team")
#let sections = require-array(config.at("sections", default: none), "sections")

#set document(title: title, author: "std::nuclear")
#set page(
  paper: "a4",
  flipped: true,
  margin: 14mm,
  numbering: "1",
  number-align: top + right,
  header: context {
    set text(size: 9pt)
    grid(
      columns: (1fr, auto),
      column-gutter: 8mm,
      [#university — #team],
      counter(page).display("1"),
    )
  },
)
#set text(font: "Libertinus Serif", size: 10pt, lang: "ru")
#set par(leading: 0.55em)
#set heading(numbering: "1.1")
#set raw(tab-size: 4)
#show raw: set text(font: "DejaVu Sans Mono", size: 6pt)
#show raw.where(block: true): set block(breakable: true)
#show raw.where(block: true): set par(leading: 0.36em)

#outline(title: [std#text(fill: rgb("#d49c00"))[::]nuclear · Содержание], depth: 2)
#set page(
  columns: 2,
  background: layout(size => align(center + horizon,
    line(end: (0pt, size.height - 28mm), stroke: 0.3pt + rgb("#dddddd"))
  )),
)
#set columns(gutter: 8mm)

#for (section-index, value) in sections.enumerate() {
  let field-path = "sections[" + str(section-index) + "]"
  let section = require-dictionary(value, field-path)
  heading(level: 1, require-string(section.at("title", default: none), field-path + ".title"))
  let files = require-array(section.at("files", default: none), field-path + ".files")
  for (file-index, value) in files.enumerate() {
    let field-path = field-path + ".files[" + str(file-index) + "]"
    let entry = require-dictionary(value, field-path)
    let name = require-string(entry.at("title", default: none), field-path + ".title")
    let path = require-string(entry.at("path", default: none), field-path + ".path")
    heading(level: 2, name)
    if lower(path).ends-with(".md") {
      render-markdown(path, "markdown-" + str(section-index) + "-" + str(file-index))
    } else {
      let code = extract-code(read(path), path)
      raw(code.implementation, block: true, lang: "cpp")
      if code.example != none {
        block(breakable: false, raw(code.example, block: true, lang: "cpp"))
      }
    }
  }
}
