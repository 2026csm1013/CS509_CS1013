#ifndef GEMM_HPP
#define GEMM_HPP

#include <vector>

using namespace std;

// simple gemm function
void simpleGEMM(int m, int k, int n,
                const vector<vector<int>>& matA,
                const vector<vector<int>>& matB,
                vector<vector<int>>& resC);

// tiled gemm function
void tiledGEMM(int m, int k, int n,
               const vector<vector<int>>& matA,
               const vector<vector<int>>& matB,
               vector<vector<int>>& resC,
               int blkSize = 32);

// helper to print result matrix
void printResultMat(const vector<vector<int>>& matrix);

#endif // GEMM_HPP