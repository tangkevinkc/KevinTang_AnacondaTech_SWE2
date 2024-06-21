// C++ Libraries 
#include <string>
#include <iostream>

// User functions
#include "fileTesting.cpp"
#include "directoryTools.cpp"

using namespace std;

int main(){ 
    int directA_size = 50, A_name = 0xAB, A_mod = 0xF123ACBD;
    int directB_size = 50, B_name = 0x45, B_mod = 0x28691DEF;
    if(generateTestFiles(directA_size, A_name, A_mod, directB_size, B_name, B_mod)){
        cout << "SUCCESS: Created test files" << endl;
    }
    else{
        cout << "FAILED: Did not create test files" << endl;
        exit(0);
    }

    string filepath = "files";
    if(compareTwoDirect(filepath)){
        cout << "SUCCESS: common, a_only, and b_only files have been generated" << endl;
    }
    else{
        cout << "FAILED: Files were unable to be generated" << endl;
    }
    return 0;
}