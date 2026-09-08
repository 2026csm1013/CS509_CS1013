# Assignment 4: Execution and Performance Report (Individual Tasks)

**Name:** Fardeen Khan Nabi Khan  
**Entry Number:** 2026CSM1013  
**Course:** CS509 (PG Software Lab), M.Tech CSE  

---

## 1. Introduction & Overview

This report presents the implementation, execution, correctness verification, and performance analysis of the two individual tasks from **Assignment 4**:

1. **Greedy Vertex Coloring**
2. **PageRank**

The implementations are written in **C++17** and compiled using the GNU C++ compiler with optimization enabled using the `-O3` flag.

The experiments were performed on graphs of different sizes to evaluate the correctness and execution performance of both algorithms.

### 1.1 Task 1: Greedy Vertex Coloring

The Vertex Coloring algorithm assigns a color to every vertex such that no two adjacent vertices have the same color.

The implementation uses a greedy strategy:

- Vertices are processed in their input/natural order.
- For each vertex, the colors already assigned to its neighbors are identified.
- The smallest available color is assigned to the vertex.
- An independent verification step checks whether the final coloring is valid.

The number of colors used and the correctness of the coloring are reported for every test graph.

### 1.2 Task 2: PageRank

PageRank is implemented using the iterative power-method approach.

The implementation uses:

- Damping factor: `0.85`
- Initial rank: `1 / V`
- Convergence tolerance: `0.0001`
- Maximum iterations: `100`
- Proper handling of dangling vertices
- Simultaneous rank updates in every iteration

The algorithm terminates when the rank difference between consecutive iterations falls below the specified tolerance or when the maximum number of iterations is reached.

The sum of all PageRank values is also verified to ensure that it remains approximately equal to `1.0`.

### 1.3 Timing Methodology

Execution time is measured using a high-resolution clock.

The timing region starts immediately before the algorithm execution and ends immediately after the algorithm completes.

The following operations are **excluded** from the measured execution time:

- File reading
- Input parsing
- CSR construction/conversion
- Memory allocation and vector initialization
- Output formatting
- Printing results

For PageRank, the complete iterative computation, including all iterations until convergence, is included in the measured execution time.

---

## 2. Directory Structure & Execution Setup

### 2.1 Project Layout

The project is organized as follows:

```text
CS509_CS1013/
├── common_wrapper/
│   ├── wrapper.cpp
│   └── wrapper_runner.exe
│
├── assignment_04/
│   ├── driver/
│   │   ├── vertex_coloring_runner.exe
│   │   └── pagerank_runner.exe
│   │
│   ├── src/
│   │   ├── vertex_coloring.cpp
│   │   └── pagerank.cpp
│   │
│   └── tests/
│       ├── color_10.txt
│       ├── color_100.txt
│       ├── color_10000.txt
│       ├── color_50000.txt
│       ├── color_100000.txt
│       ├── pagerank_10.txt
│       ├── pagerank_100.txt
│       ├── pagerank_1000.txt
│       ├── pagerank_10000.txt
│       └── pagerank_50000.txt
│
└── README.md
```

### 2.2 Input Format

The graph input files use the following adjacency-list format:

```text
V E
u0 degree neighbor1 neighbor2 ...
u1 degree neighbor1 neighbor2 ...
...
u(V-1) degree ...
```

where:

- `V` = number of vertices
- `E` = number of edges
- `u` = vertex identifier
- `degree` = degree/out-degree of the vertex
- Remaining values represent neighboring vertices

For PageRank, the input also contains algorithm parameters such as:

```text
DAMPING 0.85
TOLERANCE 0.0001
MAX_ITERATIONS 100
```

### 2.3 Compilation Commands

The programs were compiled using **G++**, C++17, and `-O3` optimization.

#### Vertex Coloring

```powershell
g++ -O3 -std=c++17 assignment_04/src/vertex_coloring.cpp -o assignment_04/driver/vertex_coloring_runner.exe
```

#### PageRank

```powershell
g++ -O3 -std=c++17 assignment_04/src/pagerank.cpp -o assignment_04/driver/pagerank_runner.exe
```

### 2.4 Execution Commands

#### Vertex Coloring

```powershell
.\assignment_04\driver\vertex_coloring_runner.exe .\assignment_04\tests\color_10.txt
```

#### PageRank

```powershell
.\assignment_04\driver\pagerank_runner.exe .\assignment_04\tests\pagerank_10.txt
```

The same commands can be used with the other benchmark input files by replacing the input filename.

---

## 3. Benchmark Execution Results Tables

### 3.1 Task 1: Greedy Vertex Coloring Results

The following table summarizes the execution and correctness results for the Vertex Coloring algorithm.

| File | Vertices (V) | Edges (E) | Colors Used | Valid? | Execution Time | Status |
|:---|---:|---:|---:|:---:|---:|:---:|
| `color_10.txt` | 10 | 15 | 3 | Yes | 0.0000 ms | Pass |
| `color_100.txt` | 100 | 200 | 4 | Yes | 0.0000 ms | Pass |
| `color_10000.txt` | 10,000 | 20,000 | 5 | Yes | 0.0000 ms | Pass |
| `color_50000.txt` | 50,000 | 100,000 | 5 | Yes | 1.7500 ms | Pass |
| `color_100000.txt` | 100,000 | 200,000 | 7 | Yes | 3.8760 ms | Pass |

### 3.2 Task 2: PageRank Results

The following table summarizes the PageRank execution results.

| File | Vertices (V) | Edges (E) | Damping | Top Vertex | Sum of Ranks | Iterations / Time | Status |
|:---|---:|---:|---:|---:|---:|---:|:---:|
| `pagerank_10.txt` | 10 | 30 | 0.85 | 9 | 1.000000 | 11 / 0.0000 ms | Pass |
| `pagerank_100.txt` | 100 | 400 | 0.85 | 14 | 1.000000 | 11 / 0.0000 ms | Pass |
| `pagerank_1000.txt` | 1,000 | 4,000 | 0.85 | 851 | 1.000000 | 12 / 0.0000 ms | Pass |
| `pagerank_10000.txt` | 10,000 | 40,000 | 0.85 | 3745 | 1.000000 | 12 / 0.9510 ms | Pass |
| `pagerank_50000.txt` | 50,000 | 200,000 | 0.85 | 0 (tied) | 1.000000 | 10 / 5.0080 ms | Pass |

---

## 4. Key Performance Observations & Analysis

### 4.1 Greedy Vertex Coloring

The Greedy Vertex Coloring implementation successfully processed all five benchmark graphs.

The independent verifier checked the coloring constraints across the graph, and **all test cases were reported as valid**.

The number of colors used increased with graph size and graph structure:

- `color_10.txt` used **3 colors**.
- `color_100.txt` used **4 colors**.
- `color_10000.txt` used **5 colors**.
- `color_50000.txt` used **5 colors**.
- `color_100000.txt` used **7 colors**.

The largest test case contained **100,000 vertices and 200,000 edges** and completed in **3.8760 ms**.

The execution time increased as the graph size increased, which is consistent with the fact that the algorithm needs to process vertices and their adjacency relationships.

### 4.2 PageRank

The PageRank implementation successfully converged for all five benchmark graphs.

The sum of PageRank values was consistently:

```text
1.000000
```

This confirms that the implementation maintains the expected normalization of PageRank scores.

The algorithm converged within **10–12 iterations** for all benchmark graphs:

- `pagerank_10.txt`: 11 iterations
- `pagerank_100.txt`: 11 iterations
- `pagerank_1000.txt`: 12 iterations
- `pagerank_10000.txt`: 12 iterations
- `pagerank_50000.txt`: 10 iterations

Dangling vertices were handled by redistributing their rank contribution across the graph.

For the largest PageRank benchmark:

- Vertices: **50,000**
- Edges: **200,000**
- Damping factor: **0.85**
- Iterations: **10**
- Execution time: **5.0080 ms**
- Sum of ranks: **1.000000**

### 4.3 Overall Performance Comparison

Both algorithms demonstrated low execution times for the tested graph sizes.

The largest measured execution times were:

| Algorithm | Largest Test Case | Vertices | Edges | Execution Time |
|:---|:---|---:|---:|---:|
| Greedy Vertex Coloring | `color_100000.txt` | 100,000 | 200,000 | 3.8760 ms |
| PageRank | `pagerank_50000.txt` | 50,000 | 200,000 | 5.0080 ms |

PageRank requires multiple iterations over the graph, which explains why its execution time is influenced by both graph size and the number of iterations required for convergence.

---

## 5. Algorithmic Complexity Analysis

### 5.1 Greedy Vertex Coloring

For each vertex, the algorithm examines its neighboring vertices to determine which colors are already used.

If the vertices are processed directly in their input order, the graph traversal requires:

**Time Complexity:**

```text
O(V + E)
```

where:

- `V` = number of vertices
- `E` = number of edges

If an explicit degree-based ordering such as Welsh-Powell is performed, sorting the vertices by degree introduces an additional:

```text
O(V log V)
```

Therefore, with explicit degree sorting, the overall complexity becomes:

```text
O(V log V + E)
```

**Space Complexity:**

```text
O(V + E)
```

The space is required for storing the graph representation, vertex colors, and auxiliary data structures.

### 5.2 PageRank

Each PageRank iteration processes the vertices and their outgoing edges.

Therefore, the cost of one iteration is:

```text
O(V + E)
```

If the algorithm requires `I` iterations to converge, the total time complexity becomes:

```text
O(I(V + E))
```

where:

- `V` = number of vertices
- `E` = number of edges
- `I` = number of PageRank iterations

**Space Complexity:**

```text
O(V + E)
```

This includes the graph representation, current PageRank vector, next PageRank vector, and auxiliary storage.

---

## 6. Conclusion

The Assignment 4 implementation successfully demonstrates two important graph algorithms: **Greedy Vertex Coloring** and **PageRank**.

The major observations from the experiments are:

- All Vertex Coloring test cases produced **valid colorings**.
- The number of colors used ranged from **3 to 7** across the tested graphs.
- The largest Vertex Coloring graph contained **100,000 vertices and 200,000 edges** and executed in **3.8760 ms**.
- PageRank successfully converged on all tested graphs.
- PageRank required only **10–12 iterations** for convergence.
- The sum of PageRank values remained **1.000000** for every test case.
- The largest PageRank benchmark contained **50,000 vertices and 200,000 edges** and executed in **5.0080 ms**.
- Timing measurements excluded input/output, parsing, CSR conversion, allocation, and output formatting.

Overall, the experimental results show that both implementations provide efficient execution for the benchmark graph sizes while maintaining the required correctness properties.