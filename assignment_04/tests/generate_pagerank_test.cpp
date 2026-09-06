#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

// generate directed 
void genPageRankGraph(int V, int avgDeg, const string& outFile) {

    ofstream fout(outFile);

    if (!fout.is_open()) {

        cerr << "cannot open output file " << outFile << "\n";
        return;
    }

    vector<set<int>> outAdj(V);
    int targetEdges = V * avgDeg;
    int edgesAdded = 0;

    // ensure basic chain connectivity
    for (int i = 0; i < V - 1; i++) {

        outAdj[i].insert(i + 1);
        edgesAdded++;
    }

    // add random directed edges
    int attempts = 0;
    int maxAttempts = targetEdges * 10;

    while (edgesAdded < targetEdges && attempts < maxAttempts) {

        attempts++;
        int u = rand() % V;
        int v = rand() % V;

        if (u == v) continue;

        if (outAdj[u].find(v) == outAdj[u].end()) {

            outAdj[u].insert(v);
            edgesAdded++;
        }
    }

    // write header: V E
    fout << V << " " << edgesAdded << "\n";

    // write outgoing adj 
    for (int u = 0; u < V; u++) {

        fout << u << " " << outAdj[u].size();

        for (int v : outAdj[u]) {

            fout << " " << v;
        }

        fout << "\n";
    }

    
    fout << "DAMPING 0.85\n";
    fout << "TOLERANCE 0.0001\n";
    fout << "MAX_ITERATIONS 100\n";

    fout.close();
    cout << "Generated: " << outFile << " (V=" << V << ", E=" << edgesAdded << ")\n";
}

int main() {

    srand(time(0));

    
    genPageRankGraph(10, 3, "tests/pagerank_10.txt");
    genPageRankGraph(100, 4, "tests/pagerank_100.txt");
    genPageRankGraph(1000, 4, "tests/pagerank_1000.txt");
    genPageRankGraph(10000, 4, "tests/pagerank_10000.txt");
    genPageRankGraph(50000, 4, "tests/pagerank_50000.txt");

    return 0;
}
