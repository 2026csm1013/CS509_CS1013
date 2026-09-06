#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

// nod deg struct
struct NodDeg {

    int deg;
    int u;

};

// sort by deg
bool compDeg(NodDeg a, NodDeg b) {

    if (a.deg != b.deg) {

        return a.deg > b.deg;
    }

    return a.u < b.u;

}

// verify coloring
bool verifyColor(const csrGraph& g, const vector<int>& col) {

    int totalNod = g.numNodes;

    for (int u = 0; u < totalNod; u++) {

        if (col[u] == -1) {

            return false;
        }

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        for (int i = stIdx; i < endIdx; i++) {

            int nbr = g.colIndic[i];

            if (u != nbr && col[u] == col[nbr]) {

                return false;

            }
        }


    }



    return true;
}

// validate inpt
bool checkInputFile(const string& filePath) {

    ifstream fin(filePath);

    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        return false;
    }


    int n, m;

    if (!(fin >> n >> m)) {

        cerr << "invalid dimensions\n";
        return false;
    }

    string line;
    getline(fin, line);

    int lineCount = 0;

    while (lineCount < n && getline(fin, line)) {

        if (line.empty()) continue;

        stringstream ss(line);
        int u, deg;

        if (!(ss >> u >> deg)) {

            cerr << "corrupted vertex header\n";
            return false;
        }


        if (u < 0 || u >= n) {

            cerr << "vertex id out of bounds: " << u << "\n";
            return false;
        }



        int neighborCount = 0;
        int v;

        while (ss >> v) {

            if (v < 0 || v >= n) {

                cerr << "neighbor id out of bounds: " << v << "\n";
                return false;
            }


            if (u == v) {

                cerr << "self-loop detected at node: " << u << "\n";
                return false;
            }

            neighborCount++;
        }

        if (neighborCount != deg) {

            cerr << "mismatch in degree count for node: " << u << "\n";
            return false;
        }

        lineCount++;
    }
    

    fin.close();
    return true;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "file path missing\n";
        return 1;
    }

    string fileLoc = argv[1];

    // check inpt
    if (!checkInputFile(fileLoc)) {

        cerr << "input validation failed\n";
        return 1;

    }

    // read graph
    csrGraph g = graphToCSR(fileLoc);

    int totalNod = g.numNodes;
    vector<int> col(totalNod, -1);
    int totalColors = 0;

    // start timer
    auto tStart = chrono::high_resolution_clock::now();

    // get degs from csr
    vector<NodDeg> degArr(totalNod);

    for (int u = 0; u < totalNod; u++) {

        int d = g.rowPtr[u + 1] - g.rowPtr[u];
        degArr[u] = {d, u};

    }

    // sort degs
    sort(degArr.begin(), degArr.end(), compDeg);

    // greedy pick
    vector<int> takenColors;
    int highestColor = 0;

    for (int i = 0; i < totalNod; i++) {

        int u = degArr[i].u;

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        // get nbr colors
        takenColors.clear();

        for (int j = stIdx; j < endIdx; j++) {

            int nbr = g.colIndic[j];

            if (col[nbr] != -1) {

                takenColors.push_back(col[nbr]);

            }


        }

        // sort colors
        sort(takenColors.begin(), takenColors.end());
        takenColors.erase(unique(takenColors.begin(), takenColors.end()), takenColors.end());

        // pick color
        int assigned = 0;

        for (int c : takenColors) {

            if (c == assigned) {

                assigned++;
            } else if (c > assigned) {

                break;
            }
        }

        col[u] = assigned;

        if (assigned > highestColor) {

            highestColor = assigned;
        }
    }

    if (totalNod > 0) {

        totalColors = highestColor + 1;
    }

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    bool isValid = verifyColor(g, col);

  
    cout << "Algorithm: Greedy Vertex Coloring\n";
    cout << "Vertex colors:\n";

    for (int i = 0; i < totalNod; i++) {

        cout << i << " " << col[i] << "\n";
    }

    cout << "Colors used: " << totalColors << "\n";
    cout << "Valid: " << (isValid ? "Yes" : "No") << "\n";
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}