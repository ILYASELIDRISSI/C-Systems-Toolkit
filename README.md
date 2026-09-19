# C Systems Toolkit

A C11 systems programming project implementing fundamental data structures and memory-management components from scratch.

The project focuses on manual memory management, pointer manipulation, ownership, fixed-size allocation, API design, testing, and portable C development.

## Features

The toolkit currently contains eight modules:

| Module             | Implementation Highlights                            |
| ------------------ | ---------------------------------------------------- |
| Dynamic Array      | Dynamic allocation, resizing, indexed access         |
| Linked List        | Pointer-based nodes, insertion, removal, traversal   |
| Stack              | LIFO container built on the dynamic array            |
| Queue              | Fixed-capacity circular queue                        |
| Circular Buffer    | Wrap-around indexing and bounded storage             |
| Hash Table         | String keys, separate chaining, collision handling   |
| Binary Search Tree | Insertion, search, deletion, recursive traversal     |
| Memory Pool        | Fixed-size block allocator with free-list management |

## Project Structure

```text
.
├── .github/
│   └── workflows/
│       └── ci.yml
├── include/
│   ├── binary_search_tree.h
│   ├── circular_buffer.h
│   ├── dynamic_array.h
│   ├── hash_table.h
│   ├── linked_list.h
│   ├── memory_pool.h
│   ├── queue.h
│   └── stack.h
├── src/
│   ├── binary_search_tree.c
│   ├── circular_buffer.c
│   ├── dynamic_array.c
│   ├── hash_table.c
│   ├── linked_list.c
│   ├── memory_pool.c
│   ├── queue.c
│   └── stack.c
├── tests/
│   ├── test_binary_search_tree.c
│   ├── test_circular_buffer.c
│   ├── test_dynamic_array.c
│   ├── test_hash_table.c
│   ├── test_linked_list.c
│   ├── test_memory_pool.c
│   ├── test_queue.c
│   └── test_stack.c
└── CMakeLists.txt
```

## Building

Requirements:

* C11-compatible compiler
* CMake 3.20 or newer
* CTest

Configure the project:

```bash
cmake -S . -B build
```

Build:

```bash
cmake --build build
```

## Running Tests

Run the complete test suite with:

```bash
ctest --test-dir build --output-on-failure
```

Each module has its own test executable and is registered with CTest.

## Continuous Integration

The repository uses GitHub Actions to automatically configure, compile, and test the project on Linux for pushes and pull requests.

The CI pipeline performs:

```text
Checkout
   ↓
CMake Configure
   ↓
Build
   ↓
CTest
```

Compiler warnings are enabled and treated as errors.

For GCC/Clang-style compilers:

```text
-Wall
-Wextra
-Werror
```

## Memory Management

The project intentionally performs memory management explicitly rather than relying on external container libraries.

Examples include:

* dynamic allocation and resizing
* linked-node allocation and cleanup
* ownership of copied hash-table keys
* recursive binary-tree destruction
* fixed-size memory-pool allocation
* free-list management

Every owning container provides a cleanup operation to release its resources.

## Memory Pool

The memory pool demonstrates a fixed-size allocation strategy commonly relevant to systems and embedded programming.

Instead of performing a heap allocation for every object, the pool allocates one contiguous region:

```text
[ block0 ][ block1 ][ block2 ][ block3 ]
```

Free blocks form an intrusive free list:

```text
free_list
    ↓
 block0 → block1 → block2 → block3 → NULL
```

Allocation removes the head of the free list:

```text
block0 returned

free_list
    ↓
 block1 → block2 → block3 → NULL
```

Freeing a block inserts it back at the head:

```text
free block0

free_list
    ↓
 block0 → block1 → block2 → block3 → NULL
```

This design provides constant-time allocation and release for valid usage without searching for free blocks.

The implementation also validates pool boundaries and block alignment for returned pointers.

## Hash Table

The hash table supports string keys and integer values.

Collisions are handled using separate chaining:

```text
bucket[0] → node → node → NULL
bucket[1] → NULL
bucket[2] → node → NULL
```

Keys are copied into memory owned by the table, making ownership explicit between the API and its caller.

## Binary Search Tree

The binary search tree supports:

* insertion
* search
* deletion
* inorder traversal
* preorder traversal
* postorder traversal

Traversal is exposed through callback functions so callers can process values without exposing traversal implementation details.

## Complexity

| Operation                    | Typical Complexity |
| ---------------------------- | -----------------: |
| Dynamic Array Access         |               O(1) |
| Stack Push / Pop             |     O(1) amortized |
| Queue Enqueue / Dequeue      |               O(1) |
| Circular Buffer Push / Pop   |               O(1) |
| Hash Table Lookup            |       O(1) average |
| BST Search / Insert / Delete |               O(h) |
| Memory Pool Allocate         |               O(1) |
| Memory Pool Free             |               O(1) |

For the unbalanced binary search tree, `h` is the tree height and may reach `n` in the worst case.

Hash-table complexity depends on hash distribution and collision behavior.

## Engineering Goals

This project was built to practice and demonstrate:

* C11
* pointers and pointer arithmetic
* manual memory management
* memory ownership
* dynamic and fixed-size allocation
* linked data structures
* callbacks and function pointers
* defensive API design
* modular header/source organization
* CMake
* CTest
* compiler warning discipline
* continuous integration

## Scope

The goal of this repository is not to provide a replacement for production container libraries.

It is an educational and portfolio project focused on implementing and understanding lower-level data structures and memory-management techniques directly in C.


