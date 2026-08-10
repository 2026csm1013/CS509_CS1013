#include "gemm.hpp"
#include <vector>
#include <algorithm>

using namespace std;

// Tiled GEMM
void tiledGEMM(int m, int k, int n,
               const vector<vector<int>>& matA,
               const vector<vector<int>>& matB,
               vector<vector<int>>& resC,
               int blkSize) {

    // reset outp mat
    for (int r = 0; r < m; r++) {

        fill(resC[r].begin(), resC[r].end(), 0);
    }

    // block level loop
    for (int bRow = 0; bRow < m; bRow = bRow + blkSize) {

        for (int bCol = 0; bCol < n; bCol = bCol + blkSize) {

            for (int bDepth = 0; bDepth < k; bDepth = bDepth + blkSize) {

                // elemnt level loop within curr block
                for (int i = bRow; i < min(bRow + blkSize, m); i++) {

                    for (int p = bDepth; p < min(bDepth + blkSize, k); p++) {

                        for (int j = bCol; j < min(bCol + blkSize, n); j++) {

                            resC[i][j] = resC[i][j] + matA[i][p] * matB[p][j];
                        }
                    }
                }
            }
        }
    }
}