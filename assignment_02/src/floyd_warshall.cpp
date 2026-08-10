#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

using namespace std;

// infinity constant for unreachable paths
const long long INF_VAL = 1e15;

// floyd warshall algorithm
bool solveFloydWarshall(int totalNodes, vector<vector<long long>>& dMat) {

    // main dp algorithm loops
    for (int k = 0; k < totalNodes; k++) {

        for (int i = 0; i < totalNodes; i++) {

            for (int j = 0; j < totalNodes; j++) {

                if (dMat[i][k] != INF_VAL && dMat[k][j] != INF_VAL) {

                    if (dMat[i][k] + dMat[k][j] < dMat[i][j]) {

                        dMat[i][j] = dMat[i][k] + dMat[k][j];
                    }
                }
            }
        }
    }

    // check diagonal elements for negative cycle
    for (int i = 0; i < totalNodes; i++) {

        if (dMat[i][i] < 0) {

            return true;
        }
    }

    return false;
}

// read matrix input file
void loadMatrix(const string& filePath, int& nVal, vector<vector<long long>>& dMat) {

    ifstream fin(filePath);

    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        exit(1);
    }

    fin >> nVal;

    dMat.assign(nVal, vector<long long>(nVal, INF_VAL));

    for (int r = 0; r < nVal; r++) {

        for (int c = 0; c < nVal; c++) {

            string strVal;
            fin >> strVal;

            if (strVal == "INF") {

                dMat[r][c] = INF_VAL;
            } else {

                dMat[r][c] = stoll(strVal);
            }
        }
    }

    fin.close();
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string fileLoc = argv[1];

    int numNod = 0;
    vector<vector<long long>> dMat;

    // load input matrix
    loadMatrix(fileLoc, numNod, dMat);

    // timer start
    auto tStart = chrono::high_resolution_clock::now();

    bool isNegCycle = solveFloydWarshall(numNod, dMat);

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    // print output results
    cout << "Algorithm: Floyd-Warshall\n";

    if (isNegCycle) {

        cout << "Negative cycle: true\n";
    } else {

        cout << "Distance matrix:\n";

        for (int i = 0; i < numNod; i++) {

            for (int j = 0; j < numNod; j++) {

                if (dMat[i][j] >= INF_VAL / 2) {

                    cout << "INF";
                } else {

                    cout << dMat[i][j];
                }

                if (j < numNod - 1) {

                    cout << " ";
                }
            }

            cout << "\n";
        }

        cout << "Negative cycle: none\n";
    }

    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}