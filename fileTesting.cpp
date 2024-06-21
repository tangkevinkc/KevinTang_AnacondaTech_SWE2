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
bool generateTestFiles(int direct1_size, int d1_name, int d1_mod, int direct2_size, int d2_name, int d2_mod){
    removeCurrDirect();
    if(direct1_size >= 0 && direct2_size >= 0){
        if(CreateDirectory("files/directory1", NULL) == -1){
            cout << "Error Creating directory 1" << endl;
        }
        if(CreateDirectory("files/directory2", NULL) == -1){
            cout << "Error Creating directory 2" << endl;
        }
        for(int64_t i = 0; i < direct1_size; i++){
            ofstream output("files/directory1/" + to_string(i*d1_name));
            output << i*d1_mod << "\n";
        }
        for(int64_t i = 0; i < direct2_size; i++){
            ofstream output("files/directory2/" + to_string(i*d2_name));
            output << i*d2_mod << "\n";
        }
        return true;
    }
    cout << "Direct 1 or 2 size is less than 0" << endl;
    return false;
}