#!/usr/bin/env bash

# Format all C files in main SRC dir.
clang-format -style=file ./src/**/*.cpp -i
clang-format -style=file ./src/**/*.hpp -i

# Format main entrypoint file
#clang-format -style=file ./src/app/main.cpp -i