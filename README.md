


# CS509_CS1013 - Assignment 1: General Matrix Multiplication (GEMM) Optimization

## 📌 Project Overview
This project implements and evaluates **General Matrix Multiplication (GEMM)** algorithms in C++, comparing standard direct matrix multiplication against an optimized cache-blocked (tiled) approach.

* **Algorithm 1: Simple GEMM**  
  Direct $O(N^3)$ triple-nested loop implementation ($i \to j \to k$).
* **Algorithm 2: Cache-Blocked (Tiled) GEMM**  
  Optimized $O(N^3)$ implementation using a $32 \times 32$ tile/block size to maximize CPU L1/L2 cache locality and minimize cache misses.

---

## 📂 Project Directory Structure

```text
assignment_01/
├── src/
│   └── gemm.cpp             # Core GEMM implementations and test driver
├── driver/                  # Target directory for compiled binaries
├── tests/
│   ├── generate_tests.cpp   # Automated test file generator
│   ├── gemm_test_01.txt     # Test 1: Baseline sample (2 x 3 x 2)
│   ├── gemm_test_02.txt     # Test 2: Small scale (32 x 32 x 32)
│   ├── gemm_test_03.txt     # Test 3: Moderate scale (128 x 128 x 128)
│   ├── gemm_test_04.txt     # Test 4: Medium scale (256 x 256 x 256)
│   ├── gemm_test_05.txt     # Test 5: Large scale (512 x 512 x 512)
│   └── gemm_test_06.txt     # Test 6: Peak benchmark (1000 x 1000 x 1000)
└── README.md                # Project documentation and benchmark report


## 📊 Test Results & Timing Notes
## 📊 Test Results & Timing Notes

Execution times were recorded using `std::chrono::high_resolution_clock` across all test files:

| Test Case | Matrix Dimensions ($M \times K \times N$) | Simple GEMM Time | Tiled GEMM Time |
| :--- | :--- | :--- | :--- |
| **Test 1: Basic Sanity Check** | $2 \times 3 \times 2$ | 0.000 ms | 0.000 ms |
| **Test 2: Small Input** | $32 \times 32 \times 32$ | 0.000 ms | 0.000 ms |
| **Test 3: Moderate Input** | $128 \times 128 \times 128$ | 2.000 ms | 1.999 ms |
| **Test 4: Medium Input** | $256 \times 256 \times 256$ | 13.001 ms | 13.997 ms |
| **Test 5: Large Input** | $512 \times 512 \times 512$ | 120.518 ms | 116.624 ms |
| **Test 6: Stress Test** | $1000 \times 1000 \times 1000$ | 1642.512 ms | 1049.240 ms |