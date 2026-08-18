# Assignment 1: GEMM (General Matrix Multiplication) & CSR Graph Representation

**Name:** Fardeen Khan Nabi Khan
**Entry Number:** 2026CSM1013
**Course:** CS509 (PG Software Lab), M.Tech CSE

---

## 1. Introduction & Overview

This directory contains the source code, compiled driver binaries, test suite, and benchmarking evaluations for **Assignment 1 (GEMM Task & CSR Graph Representation)**.

The implementation includes:

* **GEMM Simple (`GEMM_simple.cpp`):** Direct triple-nested-loop matrix multiplication computing $C = A \times B$.
* **GEMM Blocking (`GEMM_blocking.cpp`):** Cache-blocked (tiled) matrix multiplication using a configurable block size ($B = 32$) to maximize spatial and temporal L1/L2 cache locality and reduce memory bus traffic.
* **CSR Conversion Helper (`CSR.cpp`, `csr.hpp`):** A two-pass preprocessing helper that reads graph adjacency lists and converts them into the Compressed Sparse Row (CSR) format (`row_ptr`, `col_idx`, and `values`) for downstream graph algorithms.

### Timing Rule Compliance

* Timers start immediately before calling the algorithm function and stop immediately upon its completion.
* Input parsing, text file I/O, memory allocation, CSR preprocessing, and output printing are completely excluded from measured execution times.
* All reported runtime figures represent the arithmetic mean of **4 independent execution runs**.

---

## 2. Directory Structure & Execution Setup

### 2.1 Project Layout

```text
CS509_CS1013/
├── common_wrapper/
│   ├── wrapper.cpp
│   └── wrapper_runner.exe
│
├── assignment_01/
│   ├── driver/
│   │   └── gemm_runner.exe
│   │
│   ├── src/
│   │   ├── CSR.cpp
│   │   ├── csr.hpp
│   │   ├── GEMM_blocking.cpp
│   │   ├── GEMM_simple.cpp
│   │   ├── gemm.hpp
│   │   └── main.cpp
│   │
│   └── tests/
│       ├── csr_unweighted_07.txt
│       ├── csr_weighted_08.txt
│       ├── gemm_test_01.txt
│       ├── gemm_test_02.txt
│       ├── gemm_test_03.txt
│       ├── gemm_test_04.txt
│       ├── gemm_test_05.txt
│       └── gemm_test_06.txt
│
└── README.md
```

### File Description

| File / Directory                       | Description                                           |
| -------------------------------------- | ----------------------------------------------------- |
| `common_wrapper/wrapper.cpp`           | Interactive menu-driven build and execution interface |
| `common_wrapper/wrapper_runner.exe`    | Compiled wrapper executable                           |
| `assignment_01/driver/gemm_runner.exe` | Compiled GEMM and CSR executable driver               |
| `assignment_01/src/CSR.cpp`            | CSR data structures and adjacency-list converter      |
| `assignment_01/src/csr.hpp`            | CSR declarations and structure definitions            |
| `assignment_01/src/GEMM_blocking.cpp`  | Cache-blocked GEMM implementation                     |
| `assignment_01/src/GEMM_simple.cpp`    | Direct triple-nested-loop GEMM implementation         |
| `assignment_01/src/gemm.hpp`           | Matrix structures, prototypes, and I/O helpers        |
| `assignment_01/src/main.cpp`           | Driver, parser, and benchmark harness                 |
| `assignment_01/tests/`                 | GEMM and CSR input test cases                         |

---

### 2.2 Input Specifications

#### GEMM File Format (`gemm_test_XX.txt`)

The GEMM input file follows the format below:

```text
M K N
<A 0 elements... row>
...
<A M-1 elements... row>
<B 0 elements... row>
...
<B K-1 elements... row>
```

Matrices:

* $A$ has dimensions $M \times K$
* $B$ has dimensions $K \times N$
* Result matrix $C$ has dimensions $M \times N$

The multiplication is:

$$
C = A \times B
$$

#### CSR Graph File Format (`csr_*.txt`)

```text
V E
u0 degree neighbor1 [weight1] neighbor2 [weight2] ...
...
u(V-1) degree ...
```

The input supports both:

* **Unweighted adjacency lists**
* **Weighted adjacency lists**

---

## 3. Compilation & Execution (Common Wrapper)

All assignments and tests are managed through the interactive common wrapper.

### 3.1 Build Common Wrapper

Run the following commands from the root repository directory.

#### Bash / Linux

```bash
g++ -O3 -std=c++17 common_wrapper/wrapper.cpp -o common_wrapper/wrapper_runner.exe
```

#### PowerShell

```powershell
g++ -O3 -std=c++17 .\common_wrapper\wrapper.cpp -o .\common_wrapper\wrapper_runner.exe
```

---

### 3.2 Run Common Wrapper

Launch the menu interface using one of the following commands.

#### Bash / Linux

```bash
./common_wrapper/wrapper_runner.exe
```

#### PowerShell

```powershell
.\common_wrapper\wrapper_runner.exe
```

The interactive menu enables you to:

1. List available assignments
2. Compile selected assignment drivers
3. Run an individual test file
4. Run all test files automatically
5. Benchmark and execute across all assignments

---

# 4. Benchmark Execution Results

## 4.1 GEMM Benchmark Results

> **Note:** All runtime values represent the average calculated over **4 independent benchmark runs** with a block size of **$B = 32$**.

| Test File          | Input Type / Size                         | Expected Output | Actual Output | Simple Time (AVG) | Blocking Time (AVG) | Block Size | Status   |
| ------------------ | ----------------------------------------- | --------------- | ------------- | ----------------: | ------------------: | ---------: | -------- |
| `gemm_test_01.txt` | $2 \times 3$ and $3 \times 2$             | Result matrix   | Result matrix |          0.000 ms |            0.000 ms |         32 | **Pass** |
| `gemm_test_02.txt` | $32 \times 32$ and $32 \times 32$         | Result matrix   | Result matrix |          0.000 ms |            0.000 ms |         32 | **Pass** |
| `gemm_test_03.txt` | $128 \times 128$ and $128 \times 128$     | Result matrix   | Result matrix |         2.6713 ms |            2.299 ms |         32 | **Pass** |
| `gemm_test_04.txt` | $256 \times 256$ and $256 \times 256$     | Result matrix   | Result matrix |         14.004 ms |           15.702 ms |         32 | **Pass** |
| `gemm_test_05.txt` | $512 \times 512$ and $512 \times 512$     | Result matrix   | Result matrix |        120.518 ms |          116.624 ms |         32 | **Pass** |
| `gemm_test_06.txt` | $1000 \times 1000$ and $1000 \times 1000$ | Result matrix   | Result matrix |       1642.512 ms |         1049.240 ms |         32 | **Pass** |

---

## 4.2 CSR Conversion Benchmark Results

> **Note:** Conversion timing isolates the two-pass prefix-sum vector creation from disk read and parsing overhead.

| Test File               | Input Graph Type          | Vertices (V) | Edges (E) | Expected Output  | Actual Output    | Conversion Time (AVG) | Status   |
| ----------------------- | ------------------------- | -----------: | --------: | ---------------- | ---------------- | --------------------: | -------- |
| `csr_unweighted_07.txt` | Unweighted Adjacency List |            5 |         5 | Valid CSR Arrays | Valid CSR Arrays |              0.001 ms | **Pass** |
| `csr_weighted_08.txt`   | Weighted Adjacency List   |            5 |         6 | Valid CSR Arrays | Valid CSR Arrays |              0.001 ms | **Pass** |

---

# 5. Performance Observations & Architectural Analysis

## 5.1 L1 Cache Residency at Small Dimensions ($N \leq 32$)

For matrices of size $2 \times 3$ and $32 \times 32$, the working sets fit entirely inside the CPU L1 data cache, yielding execution times of virtually **0.000 ms**.

---

## 5.2 Loop-Control Overhead Threshold ($256 \times 256$)

At intermediate sizes ($256 \times 256$), index management and loop boundary tracking in Tiled GEMM (**15.702 ms**) slightly outweigh cache reuse advantages compared to Simple GEMM (**14.004 ms**).

---

## 5.3 Cache Blocking Speedup at Large Scale ($1000 \times 1000$)

In Simple GEMM, traversing large arrays causes frequent cache misses and memory stalls.

Tiled GEMM keeps active sub-blocks inside L1/L2 cache, delivering an approximately **36% speedup**.

| Implementation |     Runtime |
| -------------- | ----------: |
| Simple GEMM    | 1642.512 ms |
| Blocking GEMM  | 1049.240 ms |
| Block Size     |          32 |

The speedup is calculated as:

$$
\text{Speedup} =
\frac{1642.512 - 1049.240}{1642.512}
\times 100
$$

$$
\text{Speedup} \approx 36.12%
$$

This demonstrates the benefit of temporal and spatial data reuse for large matrix dimensions.

---

## 5.4 Linear Preprocessing Scalability of CSR

The adjacency-list-to-CSR converter runs in strict:

$$
O(V + E)
$$

time.

The conversion consists of two passes:

1. **Pass 1:** Computes row offsets using prefix sums.
2. **Pass 2:** Assigns elements into continuous memory blocks.

This provides an efficient and compact representation for downstream graph algorithms.

---

# 6. Algorithmic Complexity Analysis

## 6.1 Simple GEMM

### Time Complexity

The Simple GEMM implementation performs:

$$
O(M \cdot K \cdot N)
$$

arithmetic operations.

For square matrices where:

$$
M = K = N
$$

the complexity becomes:

$$
O(N^3)
$$

### Space Complexity

The auxiliary space complexity is:

$$
O(1)
$$

excluding the memory required for matrix allocation.

---

## 6.2 Tiled / Blocking GEMM

### Time Complexity

The Tiled GEMM implementation performs:

$$
O(M \cdot K \cdot N)
$$

arithmetic operations.

For square matrices, this becomes:

$$
O(N^3)
$$

The main performance improvement comes from reducing cache misses through block-based computation and improved data locality.

### Space Complexity

The auxiliary space complexity is:

$$
O(1)
$$

excluding the memory required for matrix allocation.

---

## 6.3 CSR Conversion Helper

### Time Complexity

The CSR conversion uses a two-pass prefix-sum construction and runs in:

$$
O(V + E)
$$

where:

* $V$ = number of vertices
* $E$ = number of edges

### Space Complexity

The CSR representation requires:

$$
O(V + E)
$$

space to store:

| CSR Array |    Size | Purpose                           |
| --------- | ------: | --------------------------------- |
| `row_ptr` | $V + 1$ | Stores row/vertex offsets         |
| `col_idx` |     $E$ | Stores destination vertex indices |
| `values`  |     $E$ | Stores edge weights or values     |

---

# 7. Conclusion

## 7.1 Numerical Equivalence

Both **Simple GEMM** and **Tiled GEMM** implementations yield exact matrix outputs across all tested dimensions, confirming their mathematical correctness.

---

## 7.2 Effective Memory Hierarchy Exploitation

Cache blocking significantly improves performance for large matrices, particularly at the **$1000 \times 1000$** scale.

The blocking implementation achieves approximately **36.12% performance improvement** compared with Simple GEMM through improved temporal and spatial data reuse.

---

## 7.3 Clean Preprocessing Separation

The timing methodology strictly isolates algorithmic execution from:

* File I/O
* Input parsing
* Memory allocation
* CSR generation
* Output printing

This ensures that the reported benchmark results accurately represent the computational performance of the implemented algorithms.

---

# 8. Overall Summary

| Component      | Implementation             | Time Complexity | Key Observation                                                  |
| -------------- | -------------------------- | --------------- | ---------------------------------------------------------------- |
| Simple GEMM    | Triple-nested loops        | $O(MKN)$        | Simple implementation with higher cache pressure at large sizes  |
| Blocking GEMM  | Cache-tiled multiplication | $O(MKN)$        | Better cache locality and significant speedup for large matrices |
| CSR Conversion | Two-pass prefix-sum        | $O(V+E)$        | Efficient and compact graph representation                       |
| Benchmarking   | 4-run arithmetic mean      | —               | I/O and preprocessing excluded from measured runtime             |





