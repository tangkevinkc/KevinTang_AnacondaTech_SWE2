// C++ Libraries
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;

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

bool generateTestFiles(int direct1_size, int direct2_size){
    // if(direct1_size > 0 && direct2_size > 0){
    //     ofstream output
    // }
    cout << "Direct 1 or 2 size is less than or equal to 0" << endl;
    return false;
}

// if(!files.empty()){
//         ofstream output(filename);
//         for(auto x : files){
//             output << x << "\n";
//         }
//         return true;
//     }
//     return false;