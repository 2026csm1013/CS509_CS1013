#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// run binary command on current os
void execCmd(const string& asgnDir, const string& exeName, const string& testPath) {

    #ifdef _WIN32
        string cmdStr = asgnDir + "\\driver\\" + exeName + " " + asgnDir + "\\" + testPath;
    #else
        string cmdStr = "./" + asgnDir + "/driver/" + exeName + " " + asgnDir + "/" + testPath;
    #endif

    cout << "\n==================================================\n";
    cout << " Executing via Common Wrapper\n";
    cout << " Command: " << cmdStr << "\n";
    cout << "==================================================\n\n";

    int retCode = system(cmdStr.c_str());

    if (retCode != 0) {

        cerr << "\ncommand failed with exit status: " << retCode << "\n";
    }
}

int main(int argc, char* argv[]) {

    // cli direct mode
    if (argc >= 4) {

        string asgnDir = argv[1];
        string exeName = argv[2];
        string testPath = argv[3];

        execCmd(asgnDir, exeName, testPath);
        return 0;
    }

    // menu mode
    int usrOpt;
    string testPath;

    while (true) {

        cout << "\n==================================================\n";
        cout << " CS509 INDIVIDUAL REPOSITORY COMMON WRAPPER       \n";
        cout << "==================================================\n";
        cout << " 1. Run GEMM (Simple & Blocking Implementation)\n";
        cout << " 2. Run CSR Graph Representation\n";
        cout << " 3. Run Bellman-Ford Shortest Path (CSR)\n";
        cout << " 4. Run Floyd-Warshall All-Pairs Shortest Path\n";
        cout << " 5. Run Kruskal's Minimum Spanning Tree (MST)\n";
        cout << " 6. Run Prim's Minimum Spanning Tree (MST)\n";
        cout << " 7. Exit Wrapper\n";
        cout << "==================================================\n";
        cout << "Enter your choice (1-7): ";

        if (!(cin >> usrOpt)) {

            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (usrOpt == 7) {

            cout << "Exiting Common Wrapper. Goodbye!\n";
            break;
        }

        switch (usrOpt) {

            case 1:
                cout << "Enter GEMM test file path (e.g., tests/gemm_test_01.txt): ";
                cin >> testPath;
                execCmd("assignment_01", "gemm_runner.exe", testPath);
                break;

            case 2:
                cout << "Enter Graph test file path (e.g., tests/csr_unweighted_07.txt): ";
                cin >> testPath;
                execCmd("assignment_01", "csr_runner.exe", testPath);
                break;

            case 3:
                cout << "Enter Bellman-Ford test file path (e.g., tests/bf_10.txt): ";
                cin >> testPath;
                execCmd("assignment_02", "bellman_ford_runner.exe", testPath);
                break;

            case 4:
                cout << "Enter Floyd-Warshall test file path (e.g., tests/fw_10.txt): ";
                cin >> testPath;
                execCmd("assignment_02", "floyd_warshall_runner.exe", testPath);
                break;

            case 5:
                cout << "Enter Kruskal test file path (e.g., tests/mst_10.txt): ";
                cin >> testPath;
                execCmd("assignment_03", "kruskal_runner.exe", testPath);
                break;

            case 6:
                cout << "Enter Prim's test file path (e.g., tests/mst_10.txt): ";
                cin >> testPath;
                execCmd("assignment_03", "prims_runner.exe", testPath);
                break;

            default:
                cout << "Invalid choice! Please select 1 to 7.\n";
                break;
        }
    }

    return 0;
}