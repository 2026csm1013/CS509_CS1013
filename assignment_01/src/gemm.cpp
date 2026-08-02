#include  <iostream>
#include  <vector>
#include  <fstream>
#include  <string>
#include  <chrono>
#include  <algorithm>

using namespace std;

//simple GEMM

void simpleGEMM(int m,int k, int n,
                const vector<vector<int>>& matA,
               const vector<vector<int>>& matB,
               vector<vector<int>>& resC)  {

                for(int i=0; i<m; i++){

                    for(int j=0; j<n; j++) {
                        resC[i][j]= 0;
                        for(int p=0; p<k; p++) {

                            resC[i][j]= resC[i][j] + matA[i][p] * matB[p][j];
                        }
                    }
                }
                
               }