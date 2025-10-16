"""
Convert files in `${SRC_DIR}` to a single file `${DST_FILE}`.

- Contents in `${SRC_DIR}/${MD_DIR}` are treated as markdown files and are put
  at the beginning of `${DST_FILE}`.
- For other files in `${SRC_DIR}/${HPP_DIRS}`,
  - Comment begin with "//" at the beginning of each source file are treated
    as markdown content.
  - The rest are treated as cpp code blocks.
"""

import io
import os
from enum import IntEnum, unique

type handle_t = io.TextIOWrapper[io._WrappedBuffer]

SRC_DIR = "src"
DST_FILE = "export/main.md"
MD_DIR = "_markdown"
HPP_DIRS = ["math", "ds", "graph", "misc"]
HPP_DIRS_FULL = {
    "math": "mathematics",
    "ds": "data structure",
    "graph": "graph theory",
    "misc": "miscellaneous",
}


def output_header(out_handle: handle_t):
    out_handle.write("<!-- This file is generated automatically, do not edit. -->\n")


def output_md_file(path: str, out_handle: handle_t):
    with open(path, "r", encoding="utf-8") as f:
        out_handle.write("\n")
        out_handle.write(f.read())


def output_hpp_file(path: str, out_handle: handle_t):
    @unique
    class Status(IntEnum):
        MARKDOWN = 0
        CODE = 1

    buffer: list[str] = []
    title = os.path.basename(path).split(".")[0]
    markdown: list[str] = []
    code: list[str] = []
    status = Status.MARKDOWN

    with open(path, "r", encoding="utf-8") as f:
        buffer = f.readlines()
    for line in buffer:
        if status == Status.MARKDOWN:
            if line.startswith("//"):
                markdown.append(line[2:].lstrip())
            else:
                status = Status.CODE
                code.append(line)
        elif status == Status.CODE:
            code.append(line)

    out_handle.write(f"\n### {title}\n\n")
    if markdown:
        for line in markdown:
            out_handle.write(line)
        out_handle.write("\n")
    if code:
        out_handle.write("```cpp\n")
        for line in code:
            out_handle.write(line)
        out_handle.write("```\n")


def main():
    with open(DST_FILE, "w", encoding="utf-8") as out_handle:
        output_header(out_handle)

        # Output markdown files.
        for root, _, files in os.walk(os.path.join(SRC_DIR, MD_DIR)):
            files.sort()
            for file in files:
                if not file.endswith(".md"):
                    print(f"Warning: Ignoring non-markdown file {root}/{file}.")
                    continue
                output_md_file(os.path.join(root, file), out_handle)

        # Output hpp files.
        for dir in HPP_DIRS:
            out_handle.write(f"\n## {HPP_DIRS_FULL[dir]}\n")
            for root, _, files in os.walk(os.path.join(SRC_DIR, dir)):
                files.sort()
                for file in files:
                    if not file.endswith(".hpp"):
                        print(f"Warning: Ignoring non-hpp file {root}/{file}.")
                        continue
                    output_hpp_file(os.path.join(root, file), out_handle)


if __name__ == "__main__":
    main()
