#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
#include "../../assignment_01/src/csr.hpp"

using namespace std;

// edg struct 
struct Edg {

    int u;
    int v;
    long long w;

    bool operator>( const Edg& other) const  {


        return w > other.w;

    }

};

int main( int argc, char* argv[])  {

    if ( argc < 2)  {


        cerr << "file path missing\n";
        return 1;

    }

    string fileLoc = argv[1];


    // read csr graph 
    csrGraph g = graphToCSR(fileLoc);
    int totalNod = g.numNodes;


    vector<bool> vis(totalNod, false);
    vector<Edg> mstEdgs;
    long long mstTWt = 0;


    // strt timer
    auto tStart = chrono::high_resolution_clock::now();

    // min priority queue 
    priority_queue<Edg, vector<Edg>, greater<Edg>> pq;

    // strt from 0 nod
    vis[0] = true;


    for (int i = g.rowPtr[0]; i < g.rowPtr[1]; i++) {

        int nbr = g.colIndic[i];
        long long wt = g.valList[i];
        pq.push({0, nbr, wt});


    }

    int pickEdg = 0;

    while ( !pq.empty()  && pickEdg  < totalNod - 1 )   {


        Edg cur = pq.top();
        pq.pop();

        int nxtNod = cur.v;

        if ( vis[nxtNod])   {


            continue;
        }



        vis[nxtNod] = true;
        mstEdgs.push_back(cur);
        mstTWt = mstTWt + cur.w;
        pickEdg++;

        if ( pickEdg == totalNod - 1)  {


            break;
        }



        // add outgoing edges
        for ( int i = g.rowPtr[nxtNod]; i < g.rowPtr[nxtNod + 1]; i++)  {


            int nbr = g.colIndic[i];
            long long wt = g.valList[i];


            if ( !vis[nbr])  {


                pq.push({nxtNod, nbr, wt});
            }

        }

    }


    auto tEnd = chrono::high_resolution_clock::now();

    double totalTime = chrono::duration_cast<chrono::microseconds>(tEnd - tStart).count() / 1000.0;

    

    cout << "Algorithm: Prim's MST\n";
    cout << "MST edges:\n";

    for ( int i = 0; i < mstEdgs.size(); i++)   {


        cout << mstEdgs[i].u << " " << mstEdgs[i].v << " " << mstEdgs[i].w << "\n";

    }



    cout << "Total MST weight: " << mstTWt << "\n";
    cout << "Execution time: " << totalTime << " ms\n";


    return 0;


}