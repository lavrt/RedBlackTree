# Red-Black Tree

## Overview

This project implements a Red-Black Tree data structure in C++. A Red-Black Tree is a self-balancing binary search tree that ensures O(log n) time complexity for various operations. This implementation focuses on insertion, range queries, and iterator support, with comprehensive testing using end-to-end and unit tests.

## Theoretical Background on Red-Black Trees

A Red-Black Tree is a type of self-balancing binary search tree where each node has an extra attribute, a color (red or black), to maintain balance.

<div align="center">
<img src="docs/rbt_example.jpg" style="width: 50%; height: auto;">
</div>

The tree adheres to the following properties:

1. **Node Color**: Every node is either red or black.

2. **Root Property**: The root node is always black.

3. **Leaf Property**: All leaf nodes (NIL nodes) are black.

4. **Red Property**: No two red nodes can be adjacent (i.e., a red node cannot have a red parent or child).

5. **Black Depth Property**: Every path from a node to its descendant leaves contains the same number of black nodes.

## Features

- **Insertion**: Add nodes to the tree while maintaining Red-Black Tree properties.

- **Range Query**: Count keys within an inclusive range `[l, r]` using `LowerBound` / `UpperBound` and subtree-size augmentation.

- **Iterators**: Provide begin() and end() iterators for tree traversal.

- **Self-Balancing**: Maintains balance through left and right rotations and color adjustments.

- **Visualization** *(Debug only)*: Dump the tree structure to a Graphviz file for debugging.


## Requirements

- C++20

- A C++ compiler (e.g., g++, clang)

- CMake

- Graphviz (optional, for visualizing the tree)

- Python3 (optional, for e2e testing)

## Installing and Running

```bash
git clone https://github.com/lavrt/RedBlackTree
cd RedBlackTree

cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build

./build/tree            # running the main application

ctest --test-dir build       # running unit tests

python3 tests/e2e/run_e2e.py     # running e2e tests
```

## Visualization

The Red-Black Tree supports visualization.

<div align="center">
<img src="docs/dump_example.png" style="width: 70%; height: auto;">
</div>

To convert the generated DOT (.gv) files to PNG images:
1. Build in **Debug** so the `RBTREE_DEBUG` macro is enabled, and include the header conditionally:
```cpp
#ifdef RBTREE_DEBUG
#include "rbtree_visualizer.hpp"
#endif
```
Configure and build in Debug mode:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build
```

2. Run your program. The `.gv` files are generated automatically when you call:

```cpp
Trees::RBTreeVisualizer<KeyT>::Dump(tree, "file_name");
```

3. Install Graphviz (if not already installed) and convert to PNG:
```bash
dot filename.gv -Tpng -o filename.png
```
