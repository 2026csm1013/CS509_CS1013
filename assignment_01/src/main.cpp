#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include "gemm.hpp"

using namespace std;

// helper function to print result matrix
void printResultMat(const vector<vector<int>>& matrix) {

    int rows = matrix.size();
    if (rows == 0) {
        return;
    } 
    int cols = matrix[0].size();

    for (int r = 0; r < rows; r++) {

        for (int c = 0; c < cols; c++) {

            cout << matrix[r][c];
            if (c < cols - 1) {

                cout << " ";
            }
        }
        cout << "\n";
    }
}


int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string testFile = argv[1];
    ifstream fin(testFile);

    if (!fin.is_open()) {

        cerr << "file not opening " << testFile << "\n";
        return 1;
    }

    // load M, K, N dimensions
    int M, K, N;
    if (!(fin >> M >> K >> N)) {

        cerr << "invalid file content\n";
        return 1;
    }

    // allocate memory for matrices A, B, and output C
    vector<vector<int>> A(M, vector<int>(K));
    vector<vector<int>> B(K, vector<int>(N));
    vector<vector<int>> C1(M, vector<int>(N, 0));
    vector<vector<int>> C2(M, vector<int>(N, 0));

    // read matrix A
    for (int i = 0; i < M; i++) {

        for (int j = 0; j < K; j++) {

            fin >> A[i][j];
        }
    }

    // read matrix B
    for (int i = 0; i < K; i++) {

        for (int j = 0; j < N; j++) {

            fin >> B[i][j];
        }
    }

    fin.close();

    // execution time of Simple GEMM
    auto t1_start = chrono::steady_clock::now();

    simpleGEMM(M, K, N, A, B, C1);

    auto t1_end = chrono::steady_clock::now();

    // convert microseconds to milliseconds
    double time1 = chrono::duration_cast<chrono::microseconds>(t1_end - t1_start).count() / 1000.0;

    // execution time of Blocking GEMM
    auto t2_start = chrono::steady_clock::now();

    tiledGEMM(M, K, N, A, B, C2, 32);

    auto t2_end = chrono::steady_clock::now();

    double time2 = chrono::duration_cast<chrono::microseconds>(t2_end - t2_start).count() / 1000.0;

    // print results
    cout << "Algorithm: GEMM Simple\n";
    cout << "Result matrix:\n";
    printResultMat(C1);
    cout << "Execution time: " << time1 << " ms\n\n";

    cout << "Algorithm: GEMM Blocking\n";
    cout << "Result matrix:\n";
    printResultMat(C2);
    cout << "Execution time: " << time2 << " ms\n";

    return 0;
}