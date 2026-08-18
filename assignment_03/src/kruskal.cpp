#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

// edg struct
struct Edg {

    int u;
    int v;
    long long w;
};

// sort by wt
bool sortEdg(Edg a, Edg b) {

    return a.w < b.w;
}

// find root with path comp
int findParent(int nod, vector<int>& par) {

    if (par[nod] == nod) {

        return nod;
    }

    return par[nod] = findParent(par[nod], par);
}

// dsu union
bool unionNod(int a, int b, vector<int>& par) {

    int rA = findParent(a, par);
    int rB = findParent(b, par);

    if (rA != rB) {

        par[rA] = rB;
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "file path missing\n";
        return 1;
    }

    string fileLoc = argv[1];

    // read graph
    csrGraph g = graphToCSR(fileLoc);

    int totalNod = g.numNodes;
    vector<Edg> mstEdgs;
    long long mstTWt = 0;

    // start timer
    auto tStart = chrono::high_resolution_clock::now();

    // get edges from csr
    vector<Edg> edgList;

    for (int u = 0; u < totalNod; u++) {

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        for (int i = stIdx; i < endIdx; i++) {

            int nbr = g.colIndic[i];
            long long wt = g.valList[i];

            if (u < nbr) {

                edgList.push_back({u, nbr, wt});
            }
        }
    }

    // sort edgs
    sort(edgList.begin(), edgList.end(), sortEdg);

    // init parent arr
    vector<int> par(totalNod);

    for (int i = 0; i < totalNod; i++) {

        par[i] = i;
    }

    // greedy pick
    int pickEdg = 0;

    for (int i = 0; i < edgList.size(); i++) {

        int u = edgList[i].u;
        int v = edgList[i].v;
        long long w = edgList[i].w;

        if (unionNod(u, v, par)) {

            mstEdgs.push_back(edgList[i]);
            mstTWt = mstTWt + w;
            pickEdg++;

            if (pickEdg == totalNod - 1) {

                break;
            }
        }
    }

    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    // print output
    cout << "Algorithm: Kruskal's MST\n";
    cout << "MST edges:\n";

    for (int i = 0; i < mstEdgs.size(); i++) {

        cout << mstEdgs[i].u << " " << mstEdgs[i].v << " " << mstEdgs[i].w << "\n";
    }

    cout << "Total MST weight: " << mstTWt << "\n";
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}