// C++ Libraries
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <windows.h>

using namespace std;

// Removes all current content within the "files" directory 
void removeCurrDirect(){
    filesystem::path dir(filesystem::current_path() / "files");
    if(filesystem::exists(dir) && !filesystem::is_empty(dir)){
        for(const auto &file : filesystem::directory_iterator(dir)){
            filesystem::remove_all(file.path());
        }
        cout << "SUCCESS: Removed all current directories" << endl;
        return;
    }
    cout << dir << endl;
    cout << "FAILED: Did not remove current directories or it was empty" << endl;
    return;
}

// Generates two directories with input parameters for number of files, file names, amd file contents
bool generateTestFiles(int directA_size, int A_name, int A_mod, int directB_size, int B_name, int B_mod){
    removeCurrDirect();
    if(directA_size >= 0 && directB_size >= 0){
        if(CreateDirectory("files/directoryA", NULL) == -1){
            cout << "Error Creating directory A" << endl;
        }
        if(CreateDirectory("files/directoryB", NULL) == -1){
            cout << "Error Creating directory B" << endl;
        }
        for(int64_t i = 0; i < directA_size; i++){
            ofstream output("files/directoryA/" + to_string(i * A_name));
            output << i * A_mod << "\n";
        }
        for(int64_t i = 0; i < directB_size; i++){
            ofstream output("files/directoryB/" + to_string(i * B_name));
            output << i * B_mod << "\n";
        }
        return true;
    }
    cout << "Direct A or B size is less than 0" << endl;
    return false;
}