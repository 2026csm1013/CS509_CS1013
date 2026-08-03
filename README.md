


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

Execution times were recorded using `std::chrono::high_resolution_clock` across all test files:

* **Test 1: Basic Sanity Check (2 x 3 x 2)**
  * **Simple GEMM:** 0.000 ms
  * **Tiled GEMM:** 0.000 ms
  * **Takeaway:** Checked that both algorithms produce identical outputs and that matrix dimensions line up properly.

* **Test 2: Small Input (32 x 32 x 32)**
  * **Simple GEMM:** 0.000 ms
  * **Tiled GEMM:** 0.000 ms
  * **Takeaway:** The matrix data easily fits inside L1 cache, so both methods finish immediately with no detectable delay.

* **Test 3: Moderate Input (128 x 128 x 128)**
  * **Simple GEMM:** 2.000 ms
  * **Tiled GEMM:** 1.999 ms
  * **Takeaway:** Times are virtually identical. Memory retrieval isn't slowing down execution at this scale yet.

* **Test 4: Medium Input (256 x 256 x 256)**
  * **Simple GEMM:** 13.001 ms
  * **Tiled GEMM:** 13.997 ms
  * **Takeaway:** The direct approach is slightly faster here. Running six nested loops in the tiled version adds minor control overhead that isn't offset by cache savings while the data still fits in memory.

* **Test 5: Large Input (512 x 512 x 512)**
  * **Simple GEMM:** 120.518 ms
  * **Tiled GEMM:** 116.624 ms
  * **Takeaway:** This is the inflection point where cache-blocking takes the lead as memory bandwidth begins to bottleneck standard loop iterations.

* **Test 6: Stress Test (1000 x 1000 x 1000)**
  * **Simple GEMM:** 1642.512 ms
  * **Tiled GEMM:** 1049.240 ms
  * **Takeaway:** Tiled multiplication drops overall runtime by roughly 593 ms (~36% speedup). Keeping sub-matrices constrained to $32 \times 32$ blocks maximizes cache hits and avoids constant round-trips to main RAM.

