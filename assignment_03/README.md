# Assignment 3: Minimum Spanning Tree Algorithms (Kruskal & Prim)

**Name:** Fardeen Khan Nabi Khan
**Entry Number:** 2026CSM1013
**Course:** CS509 (PG Software Lab), M.Tech CSE

---

## 1. Introduction & Overview

This directory contains the source implementations, compiled drivers, test cases, and benchmarking results for **Assignment 3 (Individual Task: Minimum Spanning Tree Algorithms)**.

The implementation includes:

* **Kruskal's Algorithm:** Computes a Minimum Spanning Tree (MST) on an undirected, weighted graph using Disjoint Set Union (DSU / Union-Find) with path compression and union by rank.
* **Prim's Algorithm:** Computes a Minimum Spanning Tree (MST) from a starting source node on an undirected, weighted graph using an adjacency list representation and a min-priority queue (binary heap).

### Timing Rule Compliance

* The execution timer begins immediately before invoking the MST computation and stops immediately after the total MST weight and tree edges are resolved.
* File reading, text parsing, dynamic memory allocations, graph conversions, and result printing are completely excluded from the measured execution time.
* All reported runtime values represent the benchmark execution time measured using high-resolution profiling.

---

# 2. Directory Structure & Execution Setup

## 2.1 Project Layout

```text id="3h0jcc"
CS509_CS1013/
├── common_wrapper/
│   ├── wrapper.cpp                  # Interactive menu-driven build/run interface
│   └── wrapper_runner.exe           # Compiled wrapper executable
│
├── assignment_03/
│   ├── driver/
│   │   ├── kruskal_runner.exe       # Compiled Kruskal's algorithm driver
│   │   └── prim_runner.exe          # Compiled Prim's algorithm driver
│   │
│   ├── src/
│   │   ├── kruskal.cpp              # Kruskal's algorithm implementation
│   │   └── prim.cpp                 # Prim's algorithm implementation
│   │
│   └── tests/
│       ├── mst_10.txt               # MST test case (V=10, E=20)
│       ├── mst_100.txt              # MST test case (V=100, E=250)
│       ├── mst_10000.txt            # MST test case (V=10,000, E=35,000)
│       ├── mst_50000.txt            # MST test case (V=50,000, E=180,000)
│       └── mst_100000.txt           # MST test case (V=100,000, E=380,000)
│
└── README.md
```

### File Description

| File / Directory                          | Description                                           |
| ----------------------------------------- | ----------------------------------------------------- |
| `common_wrapper/wrapper.cpp`              | Interactive menu-driven build and execution interface |
| `common_wrapper/wrapper_runner.exe`       | Compiled wrapper executable                           |
| `assignment_03/driver/kruskal_runner.exe` | Compiled Kruskal's algorithm driver                   |
| `assignment_03/driver/prim_runner.exe`    | Compiled Prim's algorithm driver                      |
| `assignment_03/src/kruskal.cpp`           | Kruskal's MST algorithm implementation                |
| `assignment_03/src/prim.cpp`              | Prim's MST algorithm implementation                   |
| `assignment_03/tests/`                    | Input test graph datasets from $V=10$ to $V=100,000$  |

---

## 2.2 Input Specifications

### Weighted Adjacency List Format

**Input files:** `mst_*.txt`

```text id="u8s6xq"
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree ...
```

Where:

* $V$ = number of vertices
* $E$ = number of undirected edges
* `u` = source vertex of an adjacency-list entry
* `degree` = number of incident edges
* `neighbor` = adjacent endpoint vertex
* `weight` = edge weight

The input graph is an **undirected, weighted graph**.

---

# 3. Compilation & Execution

All assignments and tests can be compiled and executed through the central wrapper interface or via direct standalone execution.

## 3.1 Build Common Wrapper

### Bash / Linux

```bash id="2f4dcr"
g++ -O3 -std=c++17 common_wrapper/wrapper.cpp -o common_wrapper/wrapper_runner.exe
```

### PowerShell

```powershell id="d0x0jj"
g++ -O3 -std=c++17 .\common_wrapper\wrapper.cpp -o .\common_wrapper\wrapper_runner.exe
```

---

## 3.2 Run Common Wrapper

### Bash / Linux

```bash id="j6uzx9"
./common_wrapper/wrapper_runner.exe
```

### PowerShell

```powershell id="5e1f0f"
.\common_wrapper\wrapper_runner.exe
```

The interactive wrapper provides a common interface for:

1. Listing available assignments
2. Compiling assignment drivers
3. Running individual test files
4. Running all test files
5. Executing benchmark runs

---

## 3.3 Standalone Direct Driver Execution

### Run Kruskal Directly

```powershell id="6h1vme"
.\assignment_03\driver\kruskal_runner.exe .\assignment_03\tests\mst_10.txt
```

### Run Prim Directly

```powershell id="x9v4gt"
.\assignment_03\driver\prim_runner.exe .\assignment_03\tests\mst_10.txt
```

---

# 4. Benchmark Execution Results

## 4.1 Complete Benchmark Results

The following table summarizes the expected MST weight, the weights produced by both algorithms, and their measured execution times.

| Test File        | Vertices (V) | Edges (E) | Expected MST Weight | Kruskal Weight | Prim Weight | Kruskal Time |  Prim Time | Equal? | Status   |
| ---------------- | -----------: | --------: | ------------------: | -------------: | ----------: | -----------: | ---------: | ------ | -------- |
| `mst_10.txt`     |           10 |        20 |                 169 |            169 |         169 |     0.000 ms |   0.000 ms | Yes    | **Pass** |
| `mst_100.txt`    |          100 |       250 |                2200 |           2200 |        2200 |     0.000 ms |   0.250 ms | Yes    | **Pass** |
| `mst_10000.txt`  |       10,000 |    35,000 |              174843 |         174843 |      174843 |     6.272 ms |   8.502 ms | Yes    | **Pass** |
| `mst_50000.txt`  |       50,000 |   180,000 |              849553 |         849553 |      849553 |    40.508 ms |  49.334 ms | Yes    | **Pass** |
| `mst_100000.txt` |      100,000 |   380,000 |             1616692 |        1616692 |     1616692 |    77.411 ms | 121.996 ms | Yes    | **Pass** |

---

# 5. Performance Observations & Analysis

## 5.1 Correctness & Weight Equivalence

For all test files ranging from $V=10$ to $V=100,000$:

$\text{Kruskal Weight} = \text{Prim Weight} = \text{Expected MST Weight}$

Both algorithms produced identical total spanning tree weights across every benchmark instance.

This confirms:

* Correct edge selection by Kruskal's algorithm
* Correct cycle prevention using DSU
* Correct minimum-edge selection by Prim's algorithm
* Agreement with the expected MST weight for every test case

---

## 5.2 Scalability on Sparse Graph Datasets

The test datasets exhibit sparse edge-density ratios approximately in the range:

$E \approx 3.5V \text{ to } 4V$

### Kruskal's Algorithm

Kruskal's algorithm scales efficiently with the number of edges because it performs edge sorting followed by near-constant amortized DSU operations.

Its main computational components are:

* Edge sorting: $O(E \log E)$
* DSU operations: approximately $O(E \cdot \alpha(V))$

where $\alpha(V)$ is the Inverse Ackermann function and grows extremely slowly.

For the largest test case:

* $V = 100,000$
* $E = 380,000$
* Runtime = **77.411 ms**

---

### Prim's Algorithm

Prim's algorithm uses a min-priority queue over an adjacency-list representation.

Its execution involves:

* Inserting candidate edges into the priority queue
* Extracting the minimum-weight edge
* Updating candidate vertices
* Examining incident edges

For the largest test case:

* $V = 100,000$
* $E = 380,000$
* Runtime = **121.996 ms**

The heap insertion and extraction operations introduce additional overhead compared with Kruskal's contiguous edge-array processing.

---

## 5.3 Comparative Performance Trends

### Small Graphs

For small graphs such as $V=10$ and $V=100$, both algorithms completed virtually instantaneously, with runtimes of at most **0.250 ms**.

### Large Sparse Graphs

For large sparse graphs where $V \geq 10,000$, Kruskal's algorithm consistently outperformed Prim's algorithm in the measured benchmarks.

The benchmark results show:

| Test File        | Kruskal Time |  Prim Time | Faster Algorithm |
| ---------------- | -----------: | ---------: | ---------------- |
| `mst_10.txt`     |     0.000 ms |   0.000 ms | Equal            |
| `mst_100.txt`    |     0.000 ms |   0.250 ms | Kruskal          |
| `mst_10000.txt`  |     6.272 ms |   8.502 ms | Kruskal          |
| `mst_50000.txt`  |    40.508 ms |  49.334 ms | Kruskal          |
| `mst_100000.txt` |    77.411 ms | 121.996 ms | Kruskal          |

For the largest graph, Kruskal's algorithm is approximately **36.5% faster** than Prim's algorithm based on the measured runtimes.

This performance difference can be attributed to the efficient processing of the sorted edge array and the relatively low overhead of DSU operations compared with repeated dynamic heap operations.

---

# 6. Algorithmic Complexity Analysis

## 6.1 Kruskal's Algorithm (DSU-Based)

### Time Complexity

The overall time complexity of Kruskal's algorithm is:

$$
O(E \log E)
$$

Since a connected graph has $E \geq V-1$, this is also commonly expressed as:

$$
O(E \log V)
$$

The main operations are:

* Sorting $E$ edges: $O(E \log E)$
* DSU `find` and `union` operations: $O(E \cdot \alpha(V))$

where $\alpha(V)$ is the Inverse Ackermann function and is effectively constant for practical input sizes.

### Space Complexity

The space complexity is:

$$
O(V + E)
$$

Memory is used for:

* Edge list: $O(E)$
* DSU parent array: $O(V)$
* DSU rank array: $O(V)$

---

## 6.2 Prim's Algorithm (Min-Heap / Adjacency List)

### Time Complexity

Using an adjacency list and binary min-heap, Prim's algorithm has a time complexity of:

$$
O((V + E)\log V)
$$

The main operations are:

* Vertex extraction from the min-heap: $O(V \log V)$
* Edge examination and heap operations: $O(E \log V)$

Therefore, the overall complexity is:

$$
O((V + E)\log V)
$$

### Space Complexity

The space complexity is:

$$
O(V + E)
$$

Memory is used for:

* Adjacency list: $O(V + E)$
* Visited array: $O(V)$
* Priority queue: $O(V)$ in the typical implementation

---

## 6.3 Complexity Comparison

| Algorithm | Approach            | Data Structure            | Time Complexity  | Space Complexity |
| --------- | ------------------- | ------------------------- | ---------------- | ---------------- |
| Kruskal's | Edge-based greedy   | Disjoint Set Union (DSU)  | $O(E \log E)$    | $O(V+E)$         |
| Prim's    | Vertex-based greedy | Min-Heap + Adjacency List | $O((V+E)\log V)$ | $O(V+E)$         |

---

# 7. Conclusion

## 7.1 Algorithmic Correctness

Both **Kruskal's** and **Prim's** algorithms produced exact matches with the expected minimum spanning tree weights across all five benchmark files.

| Test File        | Expected MST Weight | Kruskal Weight | Prim Weight |
| ---------------- | ------------------: | -------------: | ----------: |
| `mst_10.txt`     |                 169 |            169 |         169 |
| `mst_100.txt`    |                2200 |           2200 |        2200 |
| `mst_10000.txt`  |              174843 |         174843 |      174843 |
| `mst_50000.txt`  |              849553 |         849553 |      849553 |
| `mst_100000.txt` |             1616692 |        1616692 |     1616692 |

The results demonstrate **100% agreement** between the two algorithms and the expected MST weights.

---

## 7.2 Execution Profiling Separation

The benchmarking framework strictly isolates algorithm execution from data preprocessing.

The following operations are excluded from the recorded runtimes:

* File I/O
* Input parsing
* Adjacency-list construction
* Edge-list initialization
* Graph conversion
* Result printing

Therefore, the reported metrics reflect the measured algorithmic computation time.

---

# 8. Overall Summary

| Component                | Algorithm                      | Representation            | Complexity       | Status                  |
| ------------------------ | ------------------------------ | ------------------------- | ---------------- | ----------------------- |
| Minimum Spanning Tree    | Kruskal's                      | Edge List + DSU           | $O(E \log E)$    | **Completed**           |
| Minimum Spanning Tree    | Prim's                         | Adjacency List + Min-Heap | $O((V+E)\log V)$ | **Completed**           |
| Correctness Verification | Kruskal vs. Prim vs. Expected  | Weight Comparison         | —                | **100% Match (Passed)** |
| Large-Scale Benchmarking | Up to $V=100,000$, $E=380,000$ | High-Resolution Timing    | —                | **Completed**           |


