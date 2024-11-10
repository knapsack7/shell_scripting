# shell_scripting
Some Real World Use Cases Programming in Shell Scripting

# K-Clique Detection Program

This program implements a multi-threaded algorithm to detect K-Cliques in an undirected graph. The program uses a depth-first search (DFS) approach combined with multi-threading for efficient processing of large graphs.

## Features

- Detects all K-Cliques in an undirected graph.
- Utilizes multi-threading to speed up the process by dividing the workload across available CPU cores.
- Supports the C++11 (or newer) standard.

## Requirements

- A C++ compiler that supports C++11 or higher (e.g., `g++`, `clang++`).
- The program uses `std::vector`, `std::set`, and `std::thread` from the C++ Standard Library.
- Optional: Xcode Command Line Tools or GCC for macOS/Linux systems.

## Compilation and Usage

### Step 1: Install Dependencies

Ensure you have a working C++ compiler installed. If you're on macOS, you can install the necessary tools via:

```bash
xcode-select --install
