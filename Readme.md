# CS163 Project - The Dictionary

The Group Project of the CS163 - Data Structures course of APCS Program, University of Science, HCMC (HCMUS).

## Group Members

- Nguyễn Võ Hoàng Thông
- Lê Phát Minh
- Lương Nguyên Khoa
- Nguyễn Hữu Quốc Thắng

## Report

[Read here.](./CS163-GroupProject-Report.pdf)

## Goal achieved from the project

- To gain a better understanding of the data structures, specifically, the trie, and how they are used in real scenarios.
- To learn how to work in a group and resolve problems that occur in the process.

## Folder structure

- [`data`](./data/): Where the datasets and other necessary files are stored.
- [`include`](./include/): The header files.
- [`src`](./src/): The actual source codes.
- [`static`](./static/): Resources such as fonts, images,...
- [`visualisations`](./visualisations/): The folder where it ***used*** to host the project's execution flow illustrations, project requirements, and a bunch of other files. As of now, the diagram file is lost and broken.
- [`.clang-format`](./.clang-format): The Clang-Format settings for the project, based on [OpenTelemetry's Clang-Format](https://github.com/open-telemetry/opentelemetry-cpp/blob/main/.clang-format), Rookie Nguyen's preferred code style from the CS161 Solo Project till now.
- [`CMakeLists.txt`](./CMakeLists.txt): The CMakeList of the project.
- [`CMakeSettings.json`](./CMakeSettings.json): Since part of the goal for the project was to be as cross-platform as possible, including Windows, we opted to add this file to define a few settings for [Microsoft Visual Studio](https://visualstudio.microsoft.com/).
- [`CodingRules.md`](./CodingRules.md): This ***was*** supposed to be the coding rules for the project, like variable names casings, braces styles,... We ended up ignoring it somewhat. ¯\_(ツ)_/¯

Within the `include` and `src` folder:
- `dictionary`: the backend source/include files.
- `frontend`: the frontend source/include files.
  - `pages`: the source/include files for each of the page in the dictionary.
- `globalVars`: the source/include file for the global variables definitions and declarations.

## Build instructions

- Requirements:
  - Latest version of [CMake](https://cmake.org).
  - [Raylib](https://github.com/raysan5/raylib) v4.5
  - [RayGUI](https://github.com/raysan5/raygui) v3.6
    - Note: You don't need to download Raylib and RayGUI, as those will be downloaded upon running CMake.

- This project is designed to be cross-compatible, however, it has only primarily tested on MacOS (Clang) and Linux (GCC). We haven't tested on Windows (MSVC), but this should run, [with a few modifications to `raylib.h`](https://github.com/raysan5/raylib/wiki/Using-raylib-with-Cpp#how-can-i-fix-c-compound-literals-related-errors).

1. Create a new `build` directory at the root of the project.
2. `cd` into the `build` directory, then execute:

```bash
   cmake ..
```

3. Run `make` to build the program. The resulting executable will be in `bin/cs163_project`.
