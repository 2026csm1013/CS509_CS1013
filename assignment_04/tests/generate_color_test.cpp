#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <algorithm>

using namespace std;

// generate undirected graph 
void genColorGraph(int V, int avgDeg, const string& outFile) {

    ofstream fout(outFile);

    if (!fout.is_open()) {

        cerr << "cannot open output file " << outFile << "\n";
        return;
    }

    // adj list using sets to avoid parallel edges and self-loops
    vector<set<int>> adj(V);
    int targetEdges = (V * avgDeg) / 2;
    int edgesAdded = 0;

    // ensure connectivity where possible
    for (int i = 1; i < V; i++) {

        int p = rand() % i;
        adj[i].insert(p);
        adj[p].insert(i);
        edgesAdded++;
    }

    // add random edges
    int attempts = 0;
    int maxAttempts = targetEdges * 10;

    while (edgesAdded < targetEdges && attempts < maxAttempts) {

        attempts++;
        int u = rand() % V;
        int v = rand() % V;

        if (u == v) continue;

        if (adj[u].find(v) == adj[u].end()) {

            adj[u].insert(v);
            adj[v].insert(u);
            edgesAdded++;
        }
    }

    // write header: V E
    fout << V << " " << edgesAdded << "\n";

    // write adj list: u deg v1 v2 ...
    for (int u = 0; u < V; u++) {

        fout << u << " " << adj[u].size();

        for (int v : adj[u]) {

            fout << " " << v;
        }

        fout << "\n";
    }

    fout.close();
    cout << "Generated: " << outFile << " (V=" << V << ", E=" << edgesAdded << ")\n";
}

int main() {

    srand(time(0));

    // required sizes from section 4.2
    genColorGraph(10, 3, "tests/color_10.txt");
    genColorGraph(100, 4, "tests/color_100.txt");
    genColorGraph(10000, 4, "tests/color_10000.txt");
    genColorGraph(50000, 4, "tests/color_50000.txt");
    genColorGraph(100000, 4, "tests/color_100000.txt");

    return 0;
}