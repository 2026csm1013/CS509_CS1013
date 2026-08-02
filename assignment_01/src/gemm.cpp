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

 
//Tiled GEMM

void tiledGEMM(int m, int k, int n,
              const vector<vector<int>>& matA,
             const vector<vector<int>>& matB,
             vector<vector<int>>& resC,
             int blkSize =32 ) {

                //reset outp mat
                for(int r=0; r<m; r++) {
                    fill(resC[r].begin(), resC[r].end(), 0 );

                }

                //block level loop

                for(int bRow=0; bRow<m; bRow = bRow+blkSize){

                    for(int bCol= 0; bCol<n; bCol= bCol+blkSize){

                        for(int bDepth= 0; bDepth<k; bDepth= bDepth+blkSize){


                            //elemnt level loop within curr block
                            for(int i= bRow; i<min(bRow + blkSize, m); i++){

                                for(int p= bDepth; p< min(bDepth + blkSize, k); p++){

                                    for(int j=bCol; j<min(bCol + blkSize, n); j++) {
                                        resC[i][j] = resC[i][j] + matA[i][p] * matB[p][j];
                                    }
                                }
                            }
                        }
                    }
                }

             }

 
             
 // print res mat
 
 void printResultMat(const vector<vector<int>>& matrix) {

    int rows = matrix.size();
    if(rows == 0){
        return ;
    } 
    int cols = matrix[0].size();

    for(int r=0; r<rows; r++){

        for(int c=0; c<cols; c++) {
            cout<< matrix[r][c];
            if(c< cols-1){

                cout<<" ";
            }
        }
        cout<<endl;
    }
 }



 int main(int argc, char* argv[]){

    if(argc <2) {
        cerr << "input file path not provide.\n";
        return 1;
    }


    string testFile = argv[1];
    ifstream fin(testFile);

    if(!fin.is_open()) {
        cerr << " file not opening "<< testFile<<endl;
        return 1;
    }


    // M,K,N dimension Load
    int M,K,N;
    if(!(fin >> M >> K >> N)) {
        cerr <<" invalid file content"<<endl;
        return 1;
    }

    //Allocate mem for mat A,B and outp c

    vector<vector<int>> A(M, vector<int>(K));
    vector<vector<int>> B(K, vector<int>(N));
    vector<vector<int>> C1(M, vector<int>(N,0));
    vector<vector<int>> C2(M, vector<int>(N, 0));

    
  //mat A read
  for(int i=0; i<M; i++){

    for(int j=0; j<K; j++){

        fin >> A[i][j];
    }
  }

  //read mat B
  for(int i=0; i<K; i++) {
    for(int j=0; j<N; j++) {

        fin >> B[i][j];
    }
  }

  fin.close();


  //exe time of Simple GEMM
  auto t1_start = chrono::steady_clock::now();

  simpleGEMM(M,K,N,A,B,C1);
  auto t1_end = chrono::steady_clock::now();

  //convt mirco to milisec
  double time1 = chrono::duration_cast<chrono::microseconds>(t1_end - t1_start).count()/1000.0;


  //exe time of Blocking GEMM
  auto t2_start = chrono::steady_clock::now();
  tiledGEMM(M,K,N,A,B,C2,32);
  auto t2_end = chrono::steady_clock::now();

  double time2= chrono::duration_cast<chrono::microseconds>(t2_end - t2_start).count()/1000.0;

//output

cout<<"Algorithm: GEMM Simple\n";
cout<<"Result matrix:\n";
printResultMat(C1);
cout<<"Execution time: " <<time1 <<" ms\n\n";

cout<<"Algorithm: GEMM Blocking\n";
cout<<"Result matrix:\n";
printResultMat(C2);
cout<<"Execution time: "<<time2<<"ms\n";

 }

 
 