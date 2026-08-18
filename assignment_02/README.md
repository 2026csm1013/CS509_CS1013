# Assignment 2: Shortest Path Graph Algorithms (Bellman-Ford & Floyd-Warshall)

**Name:** Fardeen Khan Nabi Khan
**Entry Number:** 2026CSM1013
**Course:** CS509 (PG Software Lab), M.Tech CSE

---

## 1. Introduction & Overview

This directory contains the source implementations, compiled drivers, test cases, and benchmarking results for **Assignment 2 (Individual Task: Graph Shortest Path Algorithms)**.

The implementation includes:

* **Bellman-Ford (Single-Source Shortest Path):** Computes shortest distances from a single source vertex to all reachable vertices on directed graphs supporting negative edge weights using Compressed Sparse Row (CSR) representation. It includes a $V^{\text{th}}$ pass for negative cycle detection.
* **Floyd-Warshall (All-Pairs Shortest Path):** Computes shortest paths between all pairs of vertices in a directed graph using dynamic programming over an adjacency matrix. It identifies negative cycles by inspecting matrix diagonals where $\text{dist}[i][i] < 0$.

### Timing Rule Compliance

* The execution timer begins immediately before invoking the shortest path algorithm and stops immediately after its completion, including the negative-cycle detection check.
* File reading, text parsing, dynamic matrix allocations, adjacency-list-to-CSR conversion, and result printing are completely excluded from the measured execution time.
* All reported runtime values represent the exact average calculated over **4 consecutive benchmark runs**.

---

# 2. Directory Structure & Execution Setup

## 2.1 Project Layout

```text
CS509_CS1013/
├── common_wrapper/
│   ├── wrapper.cpp                  # Interactive menu-driven build/run interface
│   └── wrapper_runner.exe           # Compiled wrapper executable
│
├── common/
│   └── csr_graph.hpp                # Shared CSR conversion helper for Bellman-Ford
│
├── assignment_02/
│   ├── driver/
│   │   ├── bellman_ford_runner.exe    # Compiled Bellman-Ford driver
│   │   └── floyd_warshall_runner.exe  # Compiled Floyd-Warshall driver
│   │
│   ├── src/
│   │   ├── bellman_ford.cpp           # Bellman-Ford SSSP implementation
│   │   └── floyd_warshall.cpp         # Floyd-Warshall APSP implementation
│   │
│   └── tests/
│       ├── bf_10.txt                  # Bellman-Ford test case (V=10)
│       ├── bf_100.txt                 # Bellman-Ford test case (V=100)
│       ├── bf_10000.txt               # Bellman-Ford test case (V=10,000)
│       ├── bf_50000.txt               # Bellman-Ford test case (V=50,000)
│       ├── bf_100000.txt              # Bellman-Ford test case (V=100,000)
│       ├── bf_neg_cycle.txt           # Bellman-Ford negative-cycle test
│       ├── fw_10.txt                  # Floyd-Warshall test case (V=10)
│       ├── fw_100.txt                 # Floyd-Warshall test case (V=100)
│       ├── fw_500.txt                 # Floyd-Warshall test case (V=500)
│       ├── fw_1000.txt                # Floyd-Warshall test case (V=1,000)
│       ├── fw_2000.txt                # Floyd-Warshall test case (V=2,000)
│       └── fw_neg_cycle.txt           # Floyd-Warshall negative-cycle test
│
└── README.md
```

### File Description

| File / Directory                                 | Description                                           |
| ------------------------------------------------ | ----------------------------------------------------- |
| `common_wrapper/wrapper.cpp`                     | Interactive menu-driven build and execution interface |
| `common_wrapper/wrapper_runner.exe`              | Compiled wrapper executable                           |
| `common/csr_graph.hpp`                           | Shared CSR graph conversion helper                    |
| `assignment_02/driver/bellman_ford_runner.exe`   | Compiled Bellman-Ford driver                          |
| `assignment_02/driver/floyd_warshall_runner.exe` | Compiled Floyd-Warshall driver                        |
| `assignment_02/src/bellman_ford.cpp`             | Bellman-Ford SSSP algorithm implementation            |
| `assignment_02/src/floyd_warshall.cpp`           | Floyd-Warshall APSP algorithm implementation          |
| `assignment_02/tests/`                           | Bellman-Ford and Floyd-Warshall input test cases      |

---

## 2.2 Input Specifications

### Bellman-Ford Weighted Adjacency List Format

**Input files:** `bf_*.txt`

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree ...
SOURCE s
```

Where:

* `V` = number of vertices
* `E` = number of directed edges
* `u` = source vertex of an adjacency-list entry
* `degree` = number of outgoing edges
* `neighbor` = destination vertex
* `weight` = edge weight
* `SOURCE s` = source vertex for the single-source shortest path computation

The graph is represented internally using **Compressed Sparse Row (CSR)** format.

---

### Floyd-Warshall Dense Adjacency Matrix Format

**Input files:** `fw_*.txt`

```text
V
0 weight_01 INF weight_03 ...
INF 0 weight_12 INF ...
...
```

Where:

* `V` = number of vertices
* `INF` denotes the absence of a direct edge between two vertices
* Diagonal entries are initially `0`

The algorithm operates directly on the dense $V \times V$ adjacency matrix.

---

# 3. Compilation & Execution

All assignments and tests can be compiled and executed through the central wrapper interface.

## 3.1 Build Common Wrapper

### Bash / Linux

```bash
g++ -O3 -std=c++17 common_wrapper/wrapper.cpp -o common_wrapper/wrapper_runner.exe
```

### PowerShell

```powershell
g++ -O3 -std=c++17 .\common_wrapper\wrapper.cpp -o .\common_wrapper\wrapper_runner.exe
```

---

## 3.2 Run Common Wrapper

Launch the menu interface.

### Bash / Linux

```bash
./common_wrapper/wrapper_runner.exe
```

### PowerShell

```powershell
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

### Run Bellman-Ford Directly

```powershell
.\assignment_02\driver\bellman_ford_runner.exe .\assignment_02\tests\bf_10.txt
```

### Run Floyd-Warshall Directly

```powershell
.\assignment_02\driver\floyd_warshall_runner.exe .\assignment_02\tests\fw_10.txt
```

---

# 4. Benchmark Execution Results

> **Note:** The execution times reported below represent the average calculated over **4 independent benchmark runs**.

## 4.1 Complete Benchmark Results

| Algorithm      | Test File          | Vertices (V) | Edges (E) | Source | Negative Cycle | Expected Output      | Actual Output        |  Time (AVG) | Status   |
| -------------- | ------------------ | -----------: | --------: | -----: | -------------- | -------------------- | -------------------- | ----------: | -------- |
| Bellman-Ford   | `bf_10.txt`        |           10 |        20 |      0 | No             | Distances            | Distances            |      0.0 ms | **Pass** |
| Bellman-Ford   | `bf_100.txt`       |          100 |       300 |      0 | No             | Distances            | Distances            |      0.0 ms | **Pass** |
| Bellman-Ford   | `bf_10000.txt`     |       10,000 |    30,000 |      0 | No             | Distances            | Distances            |    1.999 ms | **Pass** |
| Bellman-Ford   | `bf_50000.txt`     |       50,000 |   150,000 |      0 | No             | Distances            | Distances            |   15.949 ms | **Pass** |
| Bellman-Ford   | `bf_100000.txt`    |      100,000 |   300,000 |      0 | No             | Distances            | Distances            |   27.529 ms | **Pass** |
| Bellman-Ford   | `bf_neg_cycle.txt` |           10 |        25 |      0 | Yes            | Negative cycle: true | Negative cycle: true |      0.0 ms | **Pass** |
| Floyd-Warshall | `fw_10.txt`        |           10 |        20 |    N/A | No             | Distance Matrix      | Distance Matrix      |      0.0 ms | **Pass** |
| Floyd-Warshall | `fw_100.txt`       |          100 |       300 |    N/A | No             | Distance Matrix      | Distance Matrix      |     3.55 ms | **Pass** |
| Floyd-Warshall | `fw_500.txt`       |          500 |     2,000 |    N/A | No             | Distance Matrix      | Distance Matrix      | 1256.743 ms | **Pass** |
| Floyd-Warshall | `fw_1000.txt`      |        1,000 |     4,000 |    N/A | No             | Distance Matrix      | Distance Matrix      |  1904.99 ms | **Pass** |
| Floyd-Warshall | `fw_2000.txt`      |        2,000 |     8,000 |    N/A | No             | Distance Matrix      | Distance Matrix      |  16091.3 ms | **Pass** |
| Floyd-Warshall | `fw_neg_cycle.txt` |           10 |        25 |    N/A | Yes            | Negative cycle: true | Negative cycle: true |      0.0 ms | **Pass** |

---

# 5. Performance Observations & Analysis

## 5.1 Negative Cycle Detection Behavior

### Bellman-Ford (`bf_neg_cycle.txt`)

When a negative cycle is reachable from source $s$, the additional $V^{\text{th}}$ pass detects continued edge relaxation.

The implementation reports:

```text
Negative cycle: true
```

The distance table is omitted when a negative cycle is detected.

The measured runtime for this test case is **0.0 ms**.

---

### Floyd-Warshall (`fw_neg_cycle.txt`)

After completing the triple nested loops, the implementation inspects the diagonal elements of the distance matrix.

A negative cycle exists if:

$$
\text{dist}[i][i] < 0
$$

for any vertex $i$.

When detected, the implementation reports:

```text
Negative cycle: true
```

and omits the distance matrix.

The measured runtime for this test case is **0.0 ms**.

---

## 5.2 Scalability of Bellman-Ford on Sparse Graphs

Bellman-Ford has a theoretical complexity of:

$$
O(V \cdot E)
$$

For the large graph inputs `bf_50000.txt` and `bf_100000.txt`, the edge count remains approximately:

$$
E \approx 3V
$$

This sparse edge ratio keeps the edge-relaxation workload manageable.

The implementation scales to:

$$
V = 100,000
$$

with a measured average runtime of **27.529 ms**, without out-of-memory or core-dump exceptions.

---

## 5.3 Cubic Growth Profile of Floyd-Warshall

Floyd-Warshall has a theoretical time complexity of:

$$
O(V^3)
$$

The benchmark results demonstrate the expected rapid increase in execution time as the number of vertices grows.

| Vertices (V) | Runtime (AVG) |
| -----------: | ------------: |
|          100 |       3.55 ms |
|          500 |   1256.743 ms |
|        1,000 |    1904.99 ms |
|        2,000 |    16091.3 ms |

At $V = 2,000$, the algorithm performs approximately:

$$
V^3 = 2000^3 = 8 \times 10^9
$$

inner-loop iterations.

The dense matrix also requires:

$$
O(V^2)
$$

memory, making memory consumption an additional limiting factor for large values of $V$.

---

## 5.4 Cross-Check Correctness Verification

For scale sizes:

$$
V = 10
$$

and

$$
V = 100
$$

Bellman-Ford was executed by taking each vertex:

$$
i \in [0, V-1]
$$

as the source vertex.

The resulting Bellman-Ford distance vectors were compared against the corresponding rows of the Floyd-Warshall distance matrix.

The comparison produced:

> **100% agreement across all tested vertex pairs.**

This cross-validation confirms the correctness of both shortest-path implementations on the shared verification cases.

---

# 6. Algorithmic Complexity Analysis

## 6.1 Bellman-Ford (CSR Input)

### Time Complexity

Bellman-Ford has a time complexity of:

$$
O(V \cdot E)
$$

The implementation performs up to $V-1$ relaxation passes over all $E$ edges stored in the CSR representation.

This is followed by an additional $V^{\text{th}}$ pass for negative-cycle detection.

### Space Complexity

The auxiliary memory requirement is:

$$
O(V + E)
$$

This includes:

* CSR row pointer array
* CSR column index array
* CSR edge-value array
* Distance array

---

## 6.2 Floyd-Warshall (Matrix Input)

### Time Complexity

Floyd-Warshall has a time complexity of:

$$
O(V^3)
$$

The core recurrence is:

$$
\text{dist}[i][j]
=================

\min
\left(
\text{dist}[i][j],
\text{dist}[i][k] + \text{dist}[k][j]
\right)
$$

This computation is performed using three nested loops over the vertices.

After the main computation, an additional diagonal scan is performed in:

$$
O(V)
$$

time to detect negative cycles.

### Space Complexity

The algorithm requires:

$$
O(V^2)
$$

space to store the dense $V \times V$ distance matrix.

---

## 6.3 Complexity Comparison

| Algorithm      | Problem Type                | Representation     | Time Complexity | Space Complexity |
| -------------- | --------------------------- | ------------------ | --------------- | ---------------- |
| Bellman-Ford   | Single-Source Shortest Path | CSR / Sparse Graph | $O(VE)$         | $O(V+E)$         |
| Floyd-Warshall | All-Pairs Shortest Path     | Dense Matrix       | $O(V^3)$        | $O(V^2)$         |

---

# 7. Conclusion

## 7.1 Algorithmic Correctness

Both **Bellman-Ford** and **Floyd-Warshall** produced correct shortest-path results on the shared verification test cases:

* `bf_10.txt` / `fw_10.txt`
* `bf_100.txt` / `fw_100.txt`

The cross-check between Bellman-Ford distance vectors and corresponding Floyd-Warshall matrix rows resulted in **100% agreement**.

---

## 7.2 Robust Fault Detection

Both implementations reliably detect negative-weight cycles.

When a negative cycle is detected, both algorithms correctly report:

```text
Negative cycle: true
```

This behavior satisfies the required assignment specification.

---

## 7.3 Execution Profiling Separation

The benchmarking methodology strictly separates preprocessing from algorithm execution.

The following operations are excluded from measured execution time:

* CSR conversion
* Matrix reading
* Text parsing
* Dynamic memory allocation
* File I/O
* Result printing

Therefore, the reported runtimes represent the measured execution cost of the shortest-path algorithms themselves.

---

# 8. Overall Summary

| Component                   | Algorithm                       | Representation      | Complexity            | Status             |
| --------------------------- | ------------------------------- | ------------------- | --------------------- | ------------------ |
| Single-Source Shortest Path | Bellman-Ford                    | CSR                 | $O(VE)$               | **Completed**      |
| All-Pairs Shortest Path     | Floyd-Warshall                  | Dense Matrix        | $O(V^3)$              | **Completed**      |
| Negative Cycle Detection    | Both Algorithms                 | CSR / Matrix        | Included in execution | **Passed**         |
| Correctness Cross-Check     | Bellman-Ford vs. Floyd-Warshall | Distance comparison | —                     | **100% Agreement** |
| Benchmarking                | 4-run average                   | —                   | —                     | **Completed**      |


