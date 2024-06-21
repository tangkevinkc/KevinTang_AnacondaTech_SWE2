// C++ Libraries 
#include <string>
#include <iostream>

// User functions
#include "fileTesting.cpp"
#include "directoryTools.cpp"

using namespace std;

int main(){ 
    int direct1_size = 3, d1_name = 0xAA, d1_mod = 0x2;
    int direct2_size = 2, d2_name = 0x55, d2_mod = 0x2;
    if(generateTestFiles(direct1_size, d1_name, d1_mod, direct2_size, d2_name, d2_mod)){
        cout << "SUCCESS: Created test files" << endl;
    }
    else{
        cout << "FAILED: Did not create test files" << endl;
        exit(0);
    }

    string filepath = "files";
    if(compareTwoDirect(filepath)){
        cout << "SUCCESS: Common, Directory 1, and 2 only files have been generated" << endl;
    }
    else{
        cout << "FAILED: Files were unable to be generated" << endl;
    }
    return 0;
}