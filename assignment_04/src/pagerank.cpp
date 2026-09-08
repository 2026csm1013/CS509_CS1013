//g++ -O3 assignment_04/src/pagerank.cpp -o assignment_04/driver/pagerank_runner.exe
//g++ -O3 assignment_04\src\vertex_coloring.cpp -o assignment_04\driver\vertex_coloring_runner.exe
//.\assignment_04\driver\vertex_coloring_runner.exe assignment_04\tests\color_10.txt

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <cmath>
#include <iomanip>
#include "../../assignment_01/src/csr.hpp"

using namespace std;


bool readConfig(const string& filePath, double& d, double& tol, int& maxIt) {

    ifstream fin(filePath);

    if (!fin.is_open()) {

        cerr << "file not opening " << filePath << "\n";
        return false;


    }


    string token;

    while (fin >> token) {


        if (token == "DAMPING") {

            fin >> d;
        } else if (token == "TOLERANCE") {

            fin >> tol;
        } else if (token == "MAX_ITERATIONS") {

            fin >> maxIt;
        }


    }

    fin.close();


    if (d <= 0.0 || d >= 1.0) {

        cerr << "invalid damping\n";
        return false;
    }

    if (tol <= 0.0) {

        cerr << "invalid tolerance\n";
        return false;

    }

    if (maxIt <= 0) {

        cerr << "invalid max iterations\n";
        return false;
    }

    return true;


}


csrGraph readDirectedGraph(const string& filePath )  {

    ifstream fin(filePath);


    if (!fin.is_open() )   {

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

    while (lineCount < n && getline(fin, line) )   {


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

 
    int totalEdges = 0;

    for (int i = 0; i < n; i++) {

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

    double d = 0.85;
    double tol = 0.0001;
    int maxIt = 100;

    if (!readConfig(fileLoc, d, tol, maxIt)) {

        cerr << "config reading failed\n";
        return 1;
    }

    
    csrGraph g = readDirectedGraph(fileLoc);

    int totalNod = g.numNodes;
    vector<double> curRk(totalNod, 1.0 / totalNod);
    vector<double> nxtRk(totalNod, 0.0);

    vector<int> outDeg(totalNod, 0);

    for (int u = 0; u < totalNod; u++) {

        outDeg[u] = g.rowPtr[u + 1] - g.rowPtr[u];



    }



    double baseScore = (1.0 - d) / totalNod;
    int iter = 0;
    bool isConv = false;


    // start timer
    auto tStart = chrono::high_resolution_clock::now();



    // pagerank loop
    while (iter < maxIt)   {

        iter++;

        //dangling nod
        double dangScore = 0.0;

        for (int u = 0; u < totalNod; u++) {

            if (outDeg[u] == 0) {

                dangScore = dangScore + curRk[u];
            }
        }

        double dangShare = (d * dangScore) / totalNod;



        // base rank init
        for (int i = 0; i < totalNod; i++) {

            nxtRk[i] = baseScore + dangShare;
        }

        // push ranks along csr edges
        for (int u = 0; u < totalNod; u++) {

            if (outDeg[u] > 0) {

                double contribution = (d * curRk[u]) / outDeg[u];
                int stIdx = g.rowPtr[u];
                int endIdx = g.rowPtr[u + 1];

                for (int idx = stIdx; idx < endIdx; idx++) {

                    int v = g.colIndic[idx];
                    nxtRk[v] = nxtRk[v] + contribution;
                }
            }


            
        }

  
        double totalChange = 0.0;

        for (int i = 0; i < totalNod; i++) {

            totalChange = totalChange + fabs(nxtRk[i] - curRk[i]);
            curRk[i] = nxtRk[i];
        }

        if (totalChange <= tol) {

            isConv = true;
            break;
        }


    }

    auto tEnd = chrono::high_resolution_clock::now();

    chrono::duration<double, milli> elapsed = tEnd - tStart;
    double totalTime = elapsed.count();

    
    double sumRk = 0.0;

    for (int i = 0; i < totalNod; i++) {

        sumRk = sumRk + curRk[i];
    }

    cout << "Algorithm: PageRank\n";
    cout << "Damping: " << d << "\n";
    cout << "Vertex ranks:\n";

    cout << fixed << setprecision(6);

    for (int i = 0; i < totalNod; i++) {

        cout << i << " " << curRk[i] << "\n";
    }

    cout << "Sum of ranks: " << sumRk << "\n";
    cout << "Iterations: " << iter << "\n";
    cout << "Converged: " << (isConv ? "true" : "false") << "\n";
    cout << "Execution time: " << totalTime << " ms\n";

    return 0;
}