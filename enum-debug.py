#!/usr/bin/env python3

import re
from pathlib import Path


def get_enum_code(source: str) -> list[str]:
    for location in re.finditer(r"(?:\s)enum(?:\s)", source):
        print(location)


path = Path("include/soda")
for header_path in path.glob("*.hpp"):
    with open(header_path, "r") as header_file:
        header_contents = header_file.read()
        get_enum_code(header_contents)
        # enum_start = header_contents.find("enum")
        # if enum_start == -1:
        #     continue
        # enum_end = enum_start
        # while header_contents[enum_end] != ";":
        #     enum_end += 1
        # enum_end += 1
        # print(header_contents[enum_start:enum_end])
