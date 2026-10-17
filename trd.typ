// Extract only explicitly marked, non-nested regions. Keep code indentation intact.
#let extract-code(source, path) = {
  let inside = false
  let lines = ()
  let fragments = ()
  for (index, line) in source.replace("\r\n", "\n").split("\n").enumerate() {
    let marker = line.trim()
    let location = path + ":" + str(index + 1)
    if marker == "/// &TRD_BEGIN" {
      assert(not inside, message: location + ": nested &TRD_BEGIN")
      inside = true
      lines = ()
    } else if marker == "/// &TRD_END" {
      assert(inside, message: location + ": &TRD_END without &TRD_BEGIN")
      let code = lines.join("\n")
      assert(code.trim() != "", message: location + ": empty TRD fragment")
      fragments.push(code)
      inside = false
    } else if inside {
      lines.push(line)
    }
  }
  assert(not inside, message: path + ": unclosed &TRD_BEGIN")
  assert(fragments.len() > 0, message: path + ": no TRD markers found")
  fragments.join("\n\n")
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
#let sections = require-array(config.at("sections", default: none), "sections")

#set document(title: title, author: "std::nuclear")
#set page(paper: "a4", flipped: true, margin: 14mm, numbering: "1")
#set text(font: "Libertinus Serif", size: 10pt, lang: "ru")
#set par(leading: 0.55em)
#set heading(numbering: "1.1")
#set raw(tab-size: 4)
#show raw: set text(font: "DejaVu Sans Mono", size: 8pt)
#show raw.where(block: true): set block(breakable: true)

#align(center, text(size: 22pt, weight: "bold", title))
#v(8mm)
#outline(title: [Содержание], depth: 2)
#pagebreak()
#set page(columns: 2)
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
    raw(extract-code(read(path), path), block: true, lang: "cpp")
  }
}
