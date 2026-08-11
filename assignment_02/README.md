Assignment 1 Execution and Performance Report (Individual Task)
Name: Fardeen Khan Nabi Khan
Entry Number: 2026CSM1013
GitHub Repository Link: https://github.com/2026csm1013/CS509_CS1013.git
1. Introduction & Overview
This report presents the implementation details, execution outputs, and benchmarking results for
Assignment 1 (GEMM Task). The implementation includes both Simple GEMM (direct nestedloop matrix multiplication) and Tiled/Blocking GEMM (cache-optimized block matrix
multiplication) in C++.
Timing Rule Compliance
In strict adherence to the assignment timing guidelines:
 The execution timer begins immediately before invoking the matrix multiplication function
and stops immediately after its completion.
 Input file reading, text parsing, matrix memory allocation, and result printing are
completely excluded from the measured execution time.
 All reported runtime values represent the average of 4 consecutive execution runs to
ensure measurement stability and accuracy.
 2. Directory Structure & Execution Setup
 2.1 Project Layout
 Plaintext
 CS509_CS1013/
 ├── driver/
 │ └── gemm_runner.exe # Compiled GEMM executable driver
 ├── src/
 │ └── gemm.cpp # GEMM algorithm implementations and
runner main()
 └── tests/
 ├── gemm_test_01.txt # 2x3 and 3x2 matrix test
 ├── gemm_test_02.txt # 32x32 and 32x32 matrix test
 ├── gemm_test_03.txt # 128x128 and 128x128 matrix test
 ├── gemm_test_04.txt # 256x256 and 256x256 matrix test
 ├── gemm_test_05.txt # 512x512 and 512x512 matrix test
 └── gemm_test_06.txt # 1000x1000 and 1000x1000 matrix test
3. GEMM Benchmark Execution Results Table
Note: The execution times reported represent the average calculated over 4 independent
benchmark runs
Test File Input Type /
Size
Expected
Output
Actual
Output
Simple
Time
(AVG)
Blocking
Time
(AVG)
Block
Size
Status
gemm_test_01.txt 2x3 and 3x2 Result
matrix
Result
matrix
0.000 ms 0.000 ms 32 Pass
gemm_test_02.txt 32x32 and
32x32
Result
matrix
Result
matrix
0.000 ms 0.000 ms 32 Pass
gemm_test_03.txt 128x128 and
128x128
Result
matrix
Result
matrix
2.6713 ms 2.299 ms 32 Pass
gemm_test_04.txt 256x256 and
256x256
Result
matrix
Result
matrix
14.004 ms 15.702 ms 32 Pass
gemm_test_05.txt 512x512 and
512x512
Result
matrix
Result
matrix
120.518
ms
116.624
ms
32 Pass
gemm_test_06.txt 1000x1000
and
1000x1000
Result
matrix
Result
matrix
1642.512
ms
1049.240
ms
32 Pass
4. Key Performance Observations & Analysis
1. Small Matrix Scale (𝑁 ≤ 32): For smaller inputs (e.g., 2 × 3 and 32 × 32), the execution
times for both Simple and Tiled versions are virtually 0.000 ms, as the CPU cache easily
accommodates the data entirely without spatial or temporal penalty.
2. Impact of Tiling/Blocking at Large Scale (1000 × 1000): As matrix size grows to
1000 × 1000, Tiled GEMM (1049.240 ms) achieves a significant speedup over Simple
GEMM (1642.512 ms). This demonstrates the advantage of cache tiling, which minimizes
L1/L2 cache misses by accessing sub-blocks repeatedly before eviction.
3. Overhead Threshold (256 × 256): At medium sizes like 256 × 256, loop tiling
introduces slight loop-control overhead, making Tiled GEMM (15.702 ms) run
comparably to or slightly behind Simple GEMM (14.004 ms) before memory bandwidth
becomes the primary bottleneck.
5. Algorithmic Complexity Analysis
5.1 Simple GEMM
 Time Complexity: 𝑂(𝑀 ⋅ 𝐾 ⋅ 𝑁)
For square matrices of size 𝑁 × 𝑁, the time complexity is 𝑂(𝑁3). The direct implementation
consists of three nested loops, computing 𝑁 multiplications and additions for each of the 𝑁2
elements in the output matrix.
 Space Complexity: 𝑂(1) auxiliary space (excluding memory allocated for matrices 𝐴, 𝐵,
and 𝐶).
5.2 Tiled / Blocking GEMM
 Time Complexity: 𝑂(𝑀 ⋅ 𝐾 ⋅ 𝑁)
While the total number of arithmetic operations remains 𝑂(𝑁3), loop tiling dramatically reduces
cache misses from 𝑂(𝑁3) to 𝑂(𝑁3/𝐵) (where 𝐵 is the block size), leading to substantially lower
overall execution time for large inputs.
 Space Complexity: 𝑂(1) auxiliary space.
6. Conclusion
The benchmarking results clearly illustrate the performance characteristics of General Matrix
Multiplication:
1. Both Simple and Tiled versions yield identical result matrices, confirming correctness.
2. Loop tiling effectively addresses memory access bottlenecks for large matrices (1000 ×
1000), yielding a ~36% performance improvement by maximizing cache line reuse.
3. Preprocessing, memory allocation, and file I/O overheads were strictly isolated from
algorithm timers as per the assignment specifications. 