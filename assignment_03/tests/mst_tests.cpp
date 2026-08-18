#include <iostream>
#include <vector>
#include <fstream>
#include <random>
#include <set>
#include <algorithm>
#include <numeric>

using namespace std;

// struct for edge entry
struct EdgItem {

    int toNod;
    long long wt;
};

// generate connected weighted graph
void genGraph(int numNod, int targetEdg, const string& fileLoc) {

    if (targetEdg < numNod - 1) {

        targetEdg = numNod - 1;
    }

    mt19937_64 rng(42 + numNod);
    uniform_int_distribution<long long> distWt(1, 100);

    set<pair<int, int>> edgSet;
    vector<vector<EdgItem>> adjList(numNod);

    // make random spanning tree for connectivity
    vector<int> nodArr(numNod);
    iota(nodArr.begin(), nodArr.end(), 0);
    shuffle(nodArr.begin(), nodArr.end(), rng);

    for (int i = 1; i < numNod; i++) {

        uniform_int_distribution<int> parDist(0, i - 1);
        int p = parDist(rng);

        int uNod = nodArr[i];
        int vNod = nodArr[p];

        if (uNod > vNod) {

            swap(uNod, vNod);
        }

        edgSet.insert({uNod, vNod});
        long long w = distWt(rng);

        adjList[uNod].push_back({vNod, w});
        adjList[vNod].push_back({uNod, w});
    }

    // add extra random edges
    uniform_int_distribution<int> nodDist(0, numNod - 1);

    while (edgSet.size() < targetEdg) {

        int uNod = nodDist(rng);
        int vNod = nodDist(rng);

        if (uNod == vNod) {

            continue;
        }

        if (uNod > vNod) {

            swap(uNod, vNod);
        }

        if (edgSet.find({uNod, vNod}) == edgSet.end()) {

            edgSet.insert({uNod, vNod});
            long long w = distWt(rng);

            adjList[uNod].push_back({vNod, w});
            adjList[vNod].push_back({uNod, w});
        }
    }

    // write to file
    ofstream outF(fileLoc);

    if (!outF.is_open()) {

        cerr << "cant write to " << fileLoc << "\n";
        return;
    }

    outF << numNod << " " << edgSet.size() << "\n";

    for (int u = 0; u < numNod; u++) {

        outF << u << " " << adjList[u].size();

        for (int j = 0; j < adjList[u].size(); j++) {

            outF << " " << adjList[u][j].toNod << " " << adjList[u][j].wt;
        }

        outF << "\n";
    }

    outF.close();

    cout << "Generated: " << fileLoc << "\n";
}

int main() {

    // test cases for mst
    genGraph(10, 20, "assignment_03/tests/mst_10.txt");
    genGraph(100, 250, "assignment_03/tests/mst_100.txt");
    genGraph(10000, 35000, "assignment_03/tests/mst_10000.txt");
    genGraph(50000, 180000, "assignment_03/tests/mst_50000.txt");
    genGraph(100000, 380000, "assignment_03/tests/mst_100000.txt");

    return 0;
}