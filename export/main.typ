#import "@preview/cmarker:0.1.6"
#import "@preview/mitex:0.2.4": mitex
#import "@preview/codly:1.3.0": *
#import "@preview/codly-languages:0.1.1": *

// Page.
#set page(
  paper: "a4",
  flipped: true,
  margin: (bottom: 9mm, rest: 6mm), // 5mm may be enough for me.
  numbering: "1",
  footer-descent: 1mm,
  footer: context [
    #set align(center)
    #counter(page).display("— 1 —")
  ],
)
#show: columns.with(2, gutter: 3mm)

// Font.
#let h2_size = 14pt
#let h3_size = 12pt
#let text_size = 10pt
#let code_size = 8pt
#let text_font = "Sarasa Term SC Nerd"
#let code_font = "FiraMono Nerd Font Mono"

// Text style.
#set text(size: text_size, font: text_font)
#show raw.where(block: false): set text(size: text_size, font: code_font)

// Title style.
#show heading.where(
  level: 2,
): it => block(width: 100%)[
  #set align(center)
  #set text(size: h2_size, weight: "regular")
  #upper(it.body)
]
#show heading.where(
  level: 3,
): it => text(
  size: h3_size,
  weight: "regular",
  style: "italic",
  it.body,
)

// Code block style.
#show: codly-init.with()
#codly(number-format: none, display-icon: false, zebra-fill: none)
#show raw.where(block: true): it => {
  set text(size: code_size, font: code_font)
  codly(languages: codly-languages)
  it
}

// Table of contents.
#set outline.entry(fill: repeat("—"))
#outline()

#cmarker.render(
  read("main.md"),
  math: mitex,
)
