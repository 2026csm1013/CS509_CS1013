#include "csr.hpp"

int main(int argc,char* argv[]) {

    if(argc <2) {
        cerr <<"Usage:"<< argv[0]<<"<input_file_path>\n";
        return 1;
    }

    string filePath = argv[1];

    //parse input file and output CSR 
    csrGraph g= graphToCSR(filePath);
    printCSR(g);

    return 0;
}