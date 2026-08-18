#ifndef CSR_HPP
#define CSR_HPP

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;



struct csrGraph {


    int numNodes = 0;
    int numEdges = 0;

    //store indx offest
    vector<int> rowPtr;


    //store col or neigbr
    vector<int> colIndic;


    //stor edge weigt
    vector<int> valList;
};



inline csrGraph graphToCSR(const string& inputFile) {

    ifstream file(inputFile);

    if (!file.is_open()) {

        cerr << " file not open " << inputFile << endl;
        exit(1);
    }

    int n, m;

    if ( !(file >> n >> m) )   {



        cerr << "not proper graph dimension to read" << endl;
        exit(1);
    }


    csrGraph graph;
    graph.numNodes = n;
    graph.numEdges = m;
    graph.rowPtr.resize(n + 1, 0);


    //temp adj list 
    vector<vector<pair<int, int>>> adj(n);
    string line;
    getline(file, line);

    int count = 0;

    while ( count < n && getline(file, line)) {

        if ( line.empty()) {



            continue;
        }


        stringstream ss(line);
        int srcNode, deg;
        ss >> srcNode >> deg;

        for ( int i = 0; i < deg; i++)   {

            int destNode;
            int wt = 1;


            ss >> destNode;

            //if weight is given

            if ( ss >> wt)  {


                adj[srcNode].push_back({destNode, wt});
            } 
            
            
            else {

                adj[srcNode].push_back({destNode, 1});
            }


        }

        count++;
    }

    file.close();


    //from adj list to CSR array
    int totalEdges = 0;

    for  ( int i = 0; i < n; i++)  {

        graph.rowPtr[i] = totalEdges;

        for ( auto& edge : adj[i]) {


            graph.colIndic.push_back(edge.first);
            graph.valList.push_back(edge.second);
            totalEdges++;

        }

    }

    //so last entry which hold total edg cont
    graph.rowPtr[n] = totalEdges;

    return graph;
}

//print

inline void printCSR( const csrGraph& graph)   {



    cout << "Vertices (V): " << graph.numNodes << endl;
    cout << "Edges (E): " << graph.numEdges << endl;

    cout << " row_ptr:";
    for ( size_t i = 0; i < graph.rowPtr.size( ); i++)  {

        cout << graph.rowPtr[i] << (i + 1 == graph.rowPtr.size() ? "" : " ");
    }


    cout << endl;

    cout << "col_idx: ";
    for ( size_t i = 0; i < graph.colIndic.size(); i++ )  {


        cout << graph.colIndic[i] << (i + 1 == graph.colIndic.size() ? "" : " ");
    }


    cout << endl;

    cout << "values: ";
    for (size_t i = 0; i < graph.valList.size(); i++) {

        cout << graph.valList[i] << (i + 1 == graph.valList.size() ? "" : " ");
    }
    cout << endl;
}

#endif 