# Assignment 1: GEMM (General Matrix Multiplication) & CSR Graph Representation

**Name:** Fardeen Khan Nabi Khan  
**Entry Number:** 2026CSM1013 
**Course:** CS509 (PG Software Lab), M.Tech CSE  

---

## 1. Introduction & Overview

This directory contains the source code, compiled driver binaries, test suite, and benchmarking evaluations for **Assignment 1 (GEMM Task & CSR Graph Representation)**[cite: 1, 2].

The implementation includes:
* **GEMM Simple (`GEMM_simple.cpp`):** Direct triple-nested-loop matrix multiplication computing $C = A \times B$[cite: 1, 2].
* **GEMM Blocking (`GEMM_blocking.cpp`):** Cache-blocked (tiled) matrix multiplication using a configurable block size ($B = 32$) to maximize spatial and temporal L1/L2 cache locality and reduce memory bus traffic[cite: 1, 2].
* **CSR Conversion Helper (`CSR.cpp`, `csr.hpp`):** A two-pass preprocessing helper that reads graph adjacency lists and converts them into the Compressed Sparse Row (CSR) format (`row_ptr`, `col_idx`, and `values`) for downstream graph algorithms.

### Timing Rule Compliance
* Timers start immediately before calling the algorithm function and stop immediately upon its completion[cite: 1, 2].
* Input parsing, text file I/O, memory allocation, CSR preprocessing, and output printing are completely excluded from measured execution times[cite: 1, 2].
* All reported runtime figures represent the arithmetic mean of **4 independent execution runs**[cite: 1, 2].

---

## 2. Directory Structure & Execution Setup

### 2.1 Project Layout

```text
CS509_CS1013/
├── common_wrapper/
│   ├── wrapper.cpp              # Interactive menu-driven build/run interface
│   └── wrapper_runner.exe       # Compiled wrapper executable
├── assignment_01/
│   ├── driver/
│   │   └── gemm_runner.exe      # Compiled GEMM & CSR executable driver
│   ├── src/
│   │   ├── CSR.cpp              # CSR data structures & adjacency-list converter
│   │   ├── csr.hpp              # CSR header declarations & struct definitions
│   │   ├── GEMM_blocking.cpp    # Cache-blocked (tiled) GEMM implementation
│   │   ├── GEMM_simple.cpp      # Direct triple-nested-loop GEMM implementation
│   │   ├── gemm.hpp             # Matrix struct, prototypes, and I/O helpers
│   │   └── main.cpp             # Driver runner, parser, and benchmark harness
│   └── tests/
│       ├── csr_unweighted_07.txt# Unweighted graph CSR test case (V=5, E=5)
│       ├── csr_weighted_08.txt  # Weighted graph CSR test case (V=5, E=6)
│       ├── gemm_test_01.txt     # 2x3 and 3x2 matrix test
│       ├── gemm_test_02.txt     # 32x32 and 32x32 matrix test
│       ├── gemm_test_03.txt     # 128x128 and 128x128 matrix test
│       ├── gemm_test_04.txt     # 256x256 and 256x256 matrix test
│       ├── gemm_test_05.txt     # 512x512 and 512x512 matrix test
│       └── gemm_test_06.txt     # 1000x1000 and 1000x1000 matrix test
└── README.md

2.2 Input Specifications
GEMM File Format (gemm_test_XX.txt):

M K N
<A 0 elements... row>
...
<A M-1 elements... row>
<B 0 elements... row>
...
<B K-1 elements... row>


Matrices $A$ ($M \times K$) and $B$ ($K \times N$) produce matrix $C$ ($M \times N$).CSR Graph File Format (csr_*.txt):

V E
u0 degree neighbor1 [weight1] neighbor2 [weight2] ...
...
u(V-1) degree ...
```

---

## 3. Compilation & Execution (Common Wrapper)

All assignments and tests are managed through the interactive common wrapper.

### 3.1 Build Common Wrapper
Run from the root repository directory:

```bash
# Bash / Linux
g++ -O3 -std=c++17 common_wrapper/wrapper.cpp -o common_wrapper/wrapper_runner.exe

# PowerShell
g++ -O3 -std=c++17 .\common_wrapper\wrapper.cpp -o .\common_wrapper\wrapper_runner.exe


3.2 Run Common Wrapper
Launch the menu interface:

# Bash / Linux
./common_wrapper/wrapper_runner.exe

# PowerShell
.\common_wrapper\wrapper_runner.exe

The interactive menu enables you to:List available assignmentsCompile selected assignment driversRun an individual test fileRun all test files automaticallyBenchmark and execute across all assignments4. Benchmark Execution Results4.1 GEMM Benchmark Results TableNote: All runtime values represent the average calculated over 4 independent benchmark runs with a block size of $B = 32$

Test FileInput Type / SizeExpected OutputActual OutputSimple Time (AVG)Blocking Time (AVG)Block SizeStatusgemm_test_01.txt$2\times 3$ and $3\times 2$Result matrixResult matrix0.000 ms0.000 ms32Pass  gemm_test_02.txt$32\times 32$ and $32\times 32$Result matrixResult matrix0.000 ms0.000 ms32Pass  gemm_test_03.txt$128\times 128$ and $128\times 128$Result matrixResult matrix2.6713 ms2.299 ms32Pass  gemm_test_04.txt$256\times 256$ and $256\times 256$Result matrixResult matrix14.004 ms15.702 ms32Pass  gemm_test_05.txt$512\times 512$ and $512\times 512$Result matrixResult matrix120.518 ms116.624 ms32Pass  gemm_test_06.txt$1000\times 1000$ and $1000\times 1000$Result matrixResult matrix1642.512 ms1049.240 ms32Pass  


4.2 CSR Conversion Benchmark Results Table
Note: Conversion timing isolates the two-pass prefix-sum vector creation from disk read and parsing overhead.

Test FileInput Graph TypeVertices (V)Edges (E)Expected OutputActual OutputConversion Time (AVG)Statuscsr_unweighted_07.txtUnweighted Adjacency List55Valid CSR ArraysValid CSR Arrays0.001 msPasscsr_weighted_08.txtWeighted Adjacency List56Valid CSR ArraysValid CSR Arrays0.001 msPass


5. Performance Observations & Architectural AnalysisL1 Cache Residency at Small Dimensions ($N \le 32$): For matrices of size $2\times 3$ and $32\times 32$, working sets fit entirely inside CPU L1 data cache, yielding execution times of virtually 0.000 ms.  Loop-Control Overhead Threshold ($256\times 256$): At intermediate sizes ($256\times 256$), index management and loop boundary tracking in Tiled GEMM ($15.702\text{ ms}$) slightly outweigh cache reuse advantages compared to Simple GEMM ($14.004\text{ ms}$).  Cache Blocking Speedup at Large Scale ($1000\times 1000$): In Simple GEMM, traversing large arrays causes frequent cache line invalidations and memory stalls. Tiled GEMM keeps active sub-blocks inside L1/L2 cache, delivering a ~36% speedup ($1049.240\text{ ms}$ vs. $1642.512\text{ ms}$).  Linear Preprocessing Scalability of CSR: The adjacency-list-to-CSR converter runs in strict $O(V + E)$ time, computing prefix sums in pass 1 and assigning elements into continuous memory blocks in pass 2.

6. Algorithmic Complexity Analysis6.1 Simple GEMMTime Complexity: $O(M \cdot K \cdot N)$ arithmetic operations ($O(N^3)$ for square matrices).  Space Complexity: $O(1)$ auxiliary space excluding matrix allocation.  6.2 Tiled / Blocking GEMMTime Complexity: $O(M \cdot K \cdot N)$ arithmetic operations, with cache misses reduced from $O(N^3)$ to $O(N^3 / B)$.  Space Complexity: $O(1)$ auxiliary space.  6.3 CSR Conversion HelperTime Complexity: $O(V + E)$ two-pass prefix-sum construction[cite: 2].Space Complexity: $O(V + E)$ to store row_ptr (size $V+1$), col_idx (size $E$), and values (size $E$).

7. ConclusionNumerical Equivalence: Both Simple and Tiled GEMM implementations yield exact matrix outputs across all dimensions, confirming mathematical correctness.  Effective Memory Hierarchy Exploitation: Tiling resolves memory bandwidth saturation for large matrices ($1000\times 1000$), delivering a ~36% performance improvement through temporal and spatial data reuse.  Clean Preprocessing Separation: Timing isolation strictly ensures that file I/O, parsing, and CSR generation overheads do not affect algorithmic benchmarking.