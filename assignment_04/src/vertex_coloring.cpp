#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <algorithm>
#include <iomanip>
#include "../../assignment_01/src/csr.hpp"

using namespace std;


struct NodDeg {

    int deg;
    int u;


};



bool compDeg(const NodDeg& a, const NodDeg& b) {

    if (a.deg != b.deg) {

        return a.deg > b.deg;
    }


    return a.u < b.u;
}




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

bool checkInputFile(const string& filePath) {

    ifstream fin(filePath);

    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        return false;


    }

    int n, m;

    if (!(fin >> n >> m)  ) {


        cerr << "invalid dimensions\n";
        return false;


    }

    string line;
    getline(fin, line);

    int lineCount = 0;

    while ( lineCount < n && getline(fin, line))   {



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

// graph to csr
csrGraph readUndirectedGraph(const string& filePath) {

    ifstream fin(filePath);

    if (!fin.is_open() ) {


        cerr << "file not opening " << filePath << "\n";
        exit(1);


    }

    int n, m;
    fin >> n >> m;

    csrGraph g;
    g.numNodes = n;
    g.numEdges = m;
    g.rowPtr.resize(n + 1, 0);

    vector<vector<int>> adjList(n);
    string line;
    getline(fin, line);

    int lineCount = 0;

    while (lineCount < n && getline(fin, line ))  {


        if (line.empty()) continue;

        stringstream ss(line);
        int u, deg;
        ss >> u >> deg;


        for (int i = 0; i < deg; i++) {

            int v;
            if (ss >> v) {

                adjList[u].push_back(v);

            }
        }

        lineCount++;


    }

    fin.close();

    // build csr arrays
    int totalEdges = 0;

    for (int i = 0; i < n; i++)  {

        g.rowPtr[i] = totalEdges;

        for (int j = 0; j < adjList[i].size(); j++) {

            int v = adjList[i][j];
            g.colIndic.push_back(v);
            g.valList.push_back(1);
            totalEdges++;
        }


    }

    g.rowPtr[n] = totalEdges;
    return g;


}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        cerr << "file path missing\n";
        return 1;

    }

    string fileLoc = argv[1];

    if (!checkInputFile(fileLoc)) {

        return 1;
    }

   

    csrGraph g = readUndirectedGraph(fileLoc);

    int totalNod = g.numNodes;
    vector<int> col(totalNod, -1);
    int totalColors = 0;


    vector<NodDeg> degArr(totalNod);

    for (int u = 0; u < totalNod; u++) {

        int d = g.rowPtr[u + 1] - g.rowPtr[u];
        degArr[u] = {d, u};
    }

    

    sort(degArr.begin(), degArr.end(), compDeg);


    auto tStart = chrono::high_resolution_clock::now();

    // greedy coloring
    vector<bool> usedCol(totalNod, false);
    int highestColor = 0;

    for (int i = 0; i < totalNod; i++ )  {


        int u = degArr[i].u;

        int stIdx = g.rowPtr[u];
        int endIdx = g.rowPtr[u + 1];

        for (int j = stIdx; j < endIdx; j++) {

            int nbr = g.colIndic[j];

            if (col[nbr] != -1)  {



                usedCol[col[nbr]] = true;
            }
        }

        
        int assigned = 0;

        while (assigned < totalNod && usedCol[assigned]) {

            assigned++;
        }

        col[u] = assigned;

        if ( assigned > highestColor) {


            highestColor = assigned;

        }

      
        for (int j = stIdx; j < endIdx; j++) {

            int nbr = g.colIndic[j];

            if (col[nbr] != -1) {

                usedCol[col[nbr]] = false;
            }
        }


    }

    if (totalNod > 0) {

        totalColors = highestColor + 1;
    }

    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = tEnd - tStart;
    double totalTime = elapsed.count();

    bool isValid = verifyColor(g, col);

    // print output
    cout << "Algorithm: Greedy Vertex Coloring\n";
    cout << "Vertex colors:\n";

    for (int i = 0; i < totalNod; i++) {

        cout << i << " " << col[i] << "\n";
    }



    cout << "Colors used: " << totalColors << "\n";
    cout << "Valid: " << (isValid ? "Yes" : "No") << "\n";
    cout << fixed << setprecision(4);
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;

    
}