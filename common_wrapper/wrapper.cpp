#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

// helper function to run command based on OS
void runCommand(const string& assignmentDir, const string& executable, const string& testFile) {

    #ifdef _WIN32
        string command = assignmentDir + "\\driver\\" + executable + " " + assignmentDir + "\\" + testFile;
    #else
        string command = "./" + assignmentDir + "/driver/" + executable + " " + assignmentDir + "/" + testFile;
    #endif

    cout << "\n==================================================\n";
    cout << " Executing via Common Wrapper\n";
    cout << " Command: " << command << "\n";
    cout << "==================================================\n\n";

    int status = system(command.c_str());

    if (status != 0) {

        cerr << "\nExecution failed with error exit code: " << status << "\n";
    }
}

int main(int argc, char* argv[]) {

    // direct CLI argument mode
    if (argc >= 4) {

        string assignmentDir = argv[1];
        string executable = argv[2];
        string testFile = argv[3];

        runCommand(assignmentDir, executable, testFile);
        return 0;
    }

    // interactive menu mode
    int choice;
    string testFile;

    while (true) {

        cout << "\n==================================================\n";
        cout << " CS509 INDIVIDUAL REPOSITORY COMMON WRAPPER       \n";
        cout << "==================================================\n";
        cout << " 1. Run GEMM (Simple & Blocking Implementation)\n";
        cout << " 2. Run CSR Graph Representation\n";
        cout << " 3. Run Bellman-Ford Shortest Path (CSR)\n";
        cout << " 4. Run Floyd-Warshall All-Pairs Shortest Path\n";
        cout << " 5. Exit Wrapper\n";
        cout << "==================================================\n";
        cout << "Enter your choice (1-5): ";

        if (!(cin >> choice)) {

            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 5) {

            cout << "Exiting Common Wrapper. Goodbye!\n";
            break;
        }

        switch (choice) {

            case 1:
                cout << "Enter GEMM test file path (e.g., tests/gemm_test_01.txt): ";
                cin >> testFile;
                runCommand("assignment_01", "gemm_runner.exe", testFile);
                break;

            case 2:
                cout << "Enter Graph test file path (e.g., tests/bfs_10.txt): ";
                cin >> testFile;
                runCommand("assignment_01", "csr_runner.exe", testFile);
                break;

            case 3:
                cout << "Enter Bellman-Ford test file path (e.g., tests/bf_10.txt): ";
                cin >> testFile;
                runCommand("assignment_02", "bellman_ford_runner.exe", testFile);
                break;

            case 4:
                cout << "Enter Floyd-Warshall test file path (e.g., tests/fw_10.txt): ";
                cin >> testFile;
                runCommand("assignment_02", "floyd_warshall_runner.exe", testFile);
                break;

            default:
                cout << "Invalid choice! Please select 1 to 5.\n";
                break;
        }
    }

    return 0;
}