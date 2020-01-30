#!/usr/bin/env bash

# Format all C files in main SRC dir.
clang-format -style=file ./src/*.c -i
clang-format -style=file ./src/*.h -i

# Format all libs, just because it's irritating for everything not to be alike.
clang-format -style=file ./src/libs/*.c -i
clang-format -style=file ./src/libs/*.h -i

# Format main entrypoint file
clang-format -style=file ./src/app/main.c -i