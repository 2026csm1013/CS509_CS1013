#include "csr.hpp"

int main( int argc, char* argv[] )   {

    if ( argc < 2) {

        cerr << "input file path not provided.\n";
        return 1;
    }

    string fileLoc = argv[1];


    // pars inpt and outp CSR
    csrGraph g =  graphToCSR(fileLoc);
    printCSR(g);

    return 0;


}