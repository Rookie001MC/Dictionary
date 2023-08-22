# CS163 Project - The Dictionary

The Group Project of the CS163 - Data Structures course of APCS Program, University of Science, HCMC (HCMUS).

## Group Members

- Nguyễn Võ Hoàng Thông
- Lê Phát Minh
- Lương Nguyên Khoa
- Nguyễn Hữu Quốc Thắng

## Report

*to be added later*

## Goal achieved from the project

- To gain a better understanding of the data structures, specifically, the trie, and how they are used in real scenarios.
- To learn how to work in a group and resolve problems that occur in the process.

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
