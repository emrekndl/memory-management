**Memory Management in C**

This repository contains a step-by-step tutorial series in C for learning the fundamentals of memory management. Unlike high-level languages with automatic memory handling, you'll build your own garbage collectors (refcounting and mark-and-sweep) from scratch in C.

> Course content is based on the "Memory Management in C" (TJ DeVries) course from boot.dev.

## Chapters

1. **C Basics** (`1-basics/`)

   * The basics of the C programming language
2. **Structs** (`2-structs/`)

   * Defining structs and their memory layout
3. **Pointers** (`3-pointers/`)

   * Hands-on pointer exercises
4. **Enums** (`4-enums/`)

   * Using `enum` for named constant sets
5. **Unions** (`5-unions/`)

   * How C `union` differs from TypeScript’s
6. **Stack and Heap** (`6-stack-heap/`)

   * Differences between stack and heap allocation
7. **Advanced Pointers** (`7-adv-pointers/`)

   * Pointers to pointers, pointer arithmetic, etc.
8. **Stack Data Structure** (`8-stack-ds/`)

   * Implementing a stack using structs and pointers
9. **Objects** (`9-objects/`)

   * Building a simple object system in C
10. **Refcounting GC** (`10-refcounting-gc/`)

    * Implementing a reference-counting garbage collector
11. **Mark and Sweep GC** (`11-mark-sweep-gc/`)

    * Implementing a basic mark-and-sweep collector and comparing tradeoffs

## Requirements

* GCC or Clang (with C99 support)
* Make
* [`munit`](https://github.com/nemequ/munit) — a minimal C unit testing library

## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/emrekndl/memory-management.git
   cd memory-management
   ```

2. Add `munit` as a submodule:

   ```bash
   git submodule add https://github.com/nemequ/munit.git munit
   git submodule update --init --recursive
   ```

3. (Optional) Build and install `munit` system-wide or locally:

   ```bash
   cd munit
   meson setup builddir && meson compile -C builddir
   sudo meson install -C builddir
   ```

## Building and Running

You can compile and run chapters as follows:

```bash
# Build all chapters
env CC=gcc make build

# Build a specific chapter (e.g., 3-pointers)
env CC=gcc make build 3-pointers

# Build using clang
env CC=clang make build 2-structs

# Compile and run a chapter
env CC=gcc make run 1-basics
```

Adjust the `CC` environment variable to switch between GCC and Clang.

---

*This project is designed for developers eager to master memory management in C.*

