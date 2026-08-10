#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

// large infinity constant
const long long INF_VAL = 1e15;

// bellman ford algorithm
bool runBellmanFord(const csrGraph& g, int srcNod, vector<long long>& currDist) {

    int totalNodes = g.numNodes;
    currDist.assign(totalNodes, INF_VAL);
    currDist[srcNod] = 0;

    // relax edges v-1 times
    for (int p = 0; p < totalNodes - 1; p++) {

        bool updated = false;

        for (int u = 0; u < totalNodes; u++) {

            if (currDist[u] == INF_VAL) continue;

            int stIdx = g.rowPtr[u];
            int endIdx = g.rowPtr[u + 1];

            for (int i = stIdx; i < endIdx; i++) {

                int v = g.colIndic[i];
                long long w = g.valList[i];

                if (currDist[u] + w < currDist[v]) {

                    currDist[v] = currDist[u] + w;
                    updated = true;
                }
            }
        }

        // stop early if no updates
        if (!updated) {
            break;
        }
    }

    // check for negative weight cycle
    for (int u = 0; u < totalNodes; u++) {

        if (currDist[u] == INF_VAL) continue;

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        for (int i = stIdx; i < endIdx; i++) {

            int v = g.colIndic[i];
            long long w = g.valList[i];

            if (currDist[u] + w < currDist[v]) {

                return true;
            }
        }
    }

    return false;
}

// read source vertex from input file
int fetchSrcNode(const string& filePath) {

    ifstream fin(filePath);

    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        exit(1);
    }

    string word;
    int srcVal = 0;

    while (fin >> word) {

        if (word == "SOURCE") {

            fin >> srcVal;
            break;
        }
    }

    fin.close();

    return srcVal;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string fileLoc = argv[1];

    // load graph and source node
    csrGraph g = graphToCSR(fileLoc);
    int srcNod = fetchSrcNode(fileLoc);

    vector<long long> shortestDistances;

    // execution timer
    auto tStart = chrono::high_resolution_clock::now();

    bool isNegCycle = runBellmanFord(g, srcNod, shortestDistances);

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    // output print
    cout << "Algorithm: Bellman-Ford\n";
    cout << "Source: " << srcNod << "\n";

    if (isNegCycle) {

        cout << "Negative cycle: true\n";
    } else {

        cout << "Vertex Distance\n";

        for (int i = 0; i < g.numNodes; i++) {

            cout << i << " ";

            if (shortestDistances[i] >= INF_VAL / 2) {

                cout << "INF\n";
            } else {

                cout << shortestDistances[i] << "\n";
            }
        }

        cout << "Negative cycle: none\n";
    }

    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}