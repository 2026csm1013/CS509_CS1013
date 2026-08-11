# Assignment 1: Execution and Performance Report

**Course:** CS509 – Software Programming Lab  
**Assignment:** Assignment 1 – GEMM Task  
**Task Type:** Individual Assignment

---

## Student Information

| Field | Details |
|---|---|
| **Name** | Fardeen Khan Nabi Khan |
| **Entry Number** | 2026CSM1013 |
| **GitHub Repository** | [CS509_CS1013](https://github.com/2026csm1013/CS509_CS1013.git) |

---

# 1. Introduction & Overview

This report presents the implementation details, execution outputs, and benchmarking results for **Assignment 1 (GEMM Task)**.

The implementation includes two versions of General Matrix-Matrix Multiplication (GEMM):

1. **Simple GEMM** – Direct nested-loop matrix multiplication.
2. **Tiled/Blocking GEMM** – Cache-optimized matrix multiplication using loop tiling/blocking.

The objective of this assignment is to compare the execution performance of the two approaches and analyze the effect of cache-aware optimization on large matrix operations.

---

## 1.1 Timing Rule Compliance

The benchmarking methodology strictly follows the assignment timing guidelines:

- The execution timer starts **immediately before** invoking the matrix multiplication function.
- The timer stops **immediately after** the matrix multiplication function completes.
- Input file reading and text parsing are **excluded** from the measured execution time.
- Matrix memory allocation is **excluded** from the measured execution time.
- Result printing is **excluded** from the measured execution time.
- Each reported runtime represents the **average of 4 consecutive execution runs** to improve measurement stability and accuracy.

---

# 2. Directory Structure & Execution Setup

## 2.1 Project Layout

The project follows the following directory structure:

```text
CS509_CS1013/
├── driver/
│   └── gemm_runner.exe
│       └── Compiled GEMM executable driver
│
├── src/
│   └── gemm.cpp
│       └── GEMM algorithm implementations and runner main()
│
└── tests/
    ├── gemm_test_01.txt    # 2×3 and 3×2 matrix test
    ├── gemm_test_02.txt    # 32×32 and 32×32 matrix test
    ├── gemm_test_03.txt    # 128×128 and 128×128 matrix test
    ├── gemm_test_04.txt    # 256×256 and 256×256 matrix test
    ├── gemm_test_05.txt    # 512×512 and 512×512 matrix test
    └── gemm_test_06.txt    # 1000×1000 and 1000×1000 matrix test

    3. GEMM Benchmark Execution Results

Note: The execution times reported below represent the average of 4 independent benchmark runs.

3.1 Benchmark Results
Test File	Input Type / Size	Expected Output	Actual Output	Simple Time (AVG)	Blocking Time (AVG)	Block Size	Status
gemm_test_01.txt	2×3 and 3×2	Result matrix	Result matrix	0.000 ms	0.000 ms	32	✅ Pass
gemm_test_02.txt	32×32 and 32×32	Result matrix	Result matrix	0.000 ms	0.000 ms	32	✅ Pass
gemm_test_03.txt	128×128 and 128×128	Result matrix	Result matrix	2.6713 ms	2.299 ms	32	✅ Pass
gemm_test_04.txt	256×256 and 256×256	Result matrix	Result matrix	14.004 ms	15.702 ms	32	✅ Pass
gemm_test_05.txt	512×512 and 512×512	Result matrix	Result matrix	120.518 ms	116.624 ms	32	✅ Pass
gemm_test_06.txt	1000×1000 and 1000×1000	Result matrix	Result matrix	1642.512 ms	1049.240 ms	32	✅ Pass



4. Key Performance Observations & Analysis
4.1 Small Matrix Scale (N ≤ 32)

For smaller inputs, such as 2×3 × 3×2 and 32×32 × 32×32, both Simple GEMM and Tiled GEMM report approximately 0.000 ms.

At this scale, the matrices are sufficiently small that the data can be handled efficiently by the processor cache. Consequently, the benefits of cache blocking are negligible compared with the overhead of the computation itself.

4.2 Performance Improvement at Large Scale (1000×1000)

The most significant performance difference is observed for the 1000×1000 matrix multiplication.

Simple GEMM: 1642.512 ms
Blocking GEMM: 1049.240 ms

The approximate performance improvement is:

Improvement=
1642.512
1642.512−1049.240
	​

×100
≈36.1%

Thus, Tiled/Blocking GEMM achieves approximately 36.1% lower execution time than Simple GEMM for the 1000×1000 test case.

This improvement is primarily due to better cache locality. Blocking divides the matrices into smaller submatrices so that frequently accessed data can remain in the cache for longer, reducing expensive cache misses and improving data reuse.

4.3 Overhead Threshold at 256×256

For the 256×256 test case, blocking does not provide a performance advantage:

Simple GEMM: 14.004 ms
Blocking GEMM: 15.702 ms

Here, the blocking implementation is approximately 1.698 ms slower.

This behavior can be attributed to the additional loop-control and block-management overhead introduced by the tiled implementation. At this intermediate matrix size, the cache-locality benefits are not yet large enough to compensate for the additional overhead.

Therefore, blocking is not guaranteed to outperform the simple implementation for every matrix size.

4.4 Performance Trend

The benchmark results demonstrate the following trend:

For very small matrices, the difference between the two approaches is negligible.
At moderate sizes, blocking may introduce some overhead and can occasionally be slower.
At larger sizes, cache locality becomes increasingly important.
For the 1000×1000 matrix, blocking provides a substantial performance improvement.

This demonstrates that optimization techniques such as loop tiling are particularly beneficial for computation-intensive workloads involving large datasets.

5. Algorithmic Complexity Analysis
5.1 Simple GEMM

The Simple GEMM implementation uses three nested loops to perform matrix multiplication.

For matrices:

A
M×K
	​

×B
K×N
	​

=C
M×N
	​


the time complexity is:

O(M×K×N)

For square matrices of size $N \times N$:

O(N
3
)

Each element of the output matrix requires approximately $N$ multiplication and addition operations, and there are $N^2$ output elements.

Space Complexity

The Simple GEMM implementation requires:

O(1)

auxiliary space, excluding the memory required to store the input matrices $A$, $B$, and output matrix $C$.

5.2 Tiled / Blocking GEMM

The Tiled/Blocking GEMM implementation divides the matrices into smaller blocks and performs multiplication block by block.

The overall arithmetic complexity remains:

O(M×K×N)

and for square matrices:

O(N
3
)

Therefore, blocking does not reduce the number of arithmetic operations required for matrix multiplication.

Instead, its primary benefit comes from improving memory access patterns and cache locality.

With a block size $B$, blocking allows matrix elements to be reused within smaller working sets before they are evicted from the cache. This can significantly reduce cache misses and improve practical execution time for large matrices.

Space Complexity

The auxiliary space complexity remains:

O(1)

excluding the storage required for matrices $A$, $B$, and $C$.

6. Correctness Verification

The implementation was tested using six different input cases ranging from very small matrices to large 1000×1000 matrices.

For every test case:

The Simple GEMM implementation produced the expected result matrix.
The Tiled/Blocking GEMM implementation produced the expected result matrix.
The results of both implementations were identical.
All six benchmark test cases passed successfully.

Therefore, the benchmarking results demonstrate both correctness and performance characteristics of the two implementations.

7. Conclusion

The benchmarking results clearly illustrate the performance characteristics of General Matrix-Matrix Multiplication (GEMM).

The key conclusions are:

Both Simple and Tiled GEMM implementations produce identical result matrices, confirming the correctness of the implementations.
Simple GEMM has an $O(N^3)$ time complexity for square matrices, while Tiled GEMM retains the same asymptotic computational complexity.
Loop tiling improves cache locality rather than reducing the number of arithmetic operations.
For small matrices, the performance difference between the two implementations is negligible.
At intermediate matrix sizes, the overhead introduced by blocking can occasionally make the Tiled implementation slower, as observed for the 256×256 test case.
For large matrices, blocking becomes significantly beneficial. For the 1000×1000 test case:
Simple GEMM: 1642.512 ms
Blocking GEMM: 1049.240 ms
Performance improvement: approximately 36.1%
Input parsing, file I/O, matrix allocation, and result printing were strictly excluded from the algorithm execution timers, following the assignment timing requirements.