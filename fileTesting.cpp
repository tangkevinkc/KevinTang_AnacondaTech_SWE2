// C++ Libraries
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

void removeCurrDirect(){
    filesystem::path dir(filesystem::current_path() / "files");
    if(filesystem::exists(dir) && filesystem::is_empty(dir)){
        filesystem::remove_all(dir);
        cout << "SUCCESS: Removed all current directories" << endl;
        return;
    }
    cout << "FAILED: Did not remove current directories or it was empty" << endl;
    return;
}

bool generateTestFiles(int direct1_size, int direct2_size){
    return false;
}