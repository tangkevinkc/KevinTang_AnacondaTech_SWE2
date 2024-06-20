#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <algorithm>

using namespace std;

// 1. get file names from directories and place into vector<string>direct1, direct2

// 2. generate hash value for each file from direct1 and place into unordered_map<size_t, filename>D1_hash
// 3. iterate through direct2 and generate hash value for each file and D1_hash.find() to see if it exists
// 4. based on the return statement determine if file is placed into shared or direct2_only file
//    if it is shared make sure to remove from unordered_map
// 5. after finishing direct2, all remaining elements in D1_hash should be direct1_only file
// 6. iterate through D1_hash and get the key of each index and place into direct1_only file

bool getDirectFiles(vector<string> &fileNames1, vector<string> &fileNames2){
    vector<string> paths;
    filesystem::directory_iterator directPaths(filesystem::current_path() / "files");
    for(const auto &name : directPaths){
        if(name.is_directory()){
            paths.push_back(name.path().filename().string());
        }
    }

    if(!paths.empty()){
        for(int i = 0; i < paths.size(); i++){
            filesystem::directory_iterator dir(filesystem::current_path() / "files" / paths[i]);
            for(const auto &file: dir){
                if(file.is_regular_file()){
                    if(i == 0)
                        fileNames1.push_back(file.path().filename().string());
                    if(i == 1)
                        fileNames2.push_back(file.path().filename().string());
                }
            }
        }
        return true;
    }
    return false;
}

bool hashDirectFiles(vector<string> &fileNames, unordered_map<size_t, string> &hash_files){
    return false;
}

bool compareDirect(unordered_map<size_t, string> &direct1_hash, vector<string> &direct2, 
                   vector<string> &shared_files, vector<string> &direct2_only){
    return false;
}

bool clearHashDirect(unordered_map<size_t, string> &direct_hash, vector<string> &direct_only){
    return false;
}

bool writeFiles(string filename, vector<string> &files){
    return false;
}

int main(){ 
    vector<string> direct1_files, direct2_files;
    
    if(getDirectFiles(direct1_files, direct2_files))
        cout << "Success: retrieving Directory files" << endl;
    else
        cout << "Failed: to retrieve Directory files" << endl;

    // unordered_map<size_t, string> direct1_hash;

    // if(hashDirectFiles(direct1_files, direct1_hash))
    //     cout << "Success: Hash of Directory 1" << endl;
    // else   
    //     cout << "Failed: Hash of Directory 1" << endl;


    // vector<string> shared_files, direct2_only;

    // if(compareDirect(direct1_hash, direct2_files, shared_files, direct2_only))
    //     cout << "Success: Compared all elements in Directory 2" << endl;
    // else   
    //     cout << "Failed: Check direct1_hash, direct2_files, or either output vectors" << endl;

    
    // vector<string> direct1_only;

    // if(clearHashDirect(direct1_hash, direct1_only))
    //     cout << "Success: Cleared unordered_map of Directory 1" << endl;
    // else    
    //     cout << "Failed: Unable to clear unordered_map of Directory 1" << endl;


    // vector<string> outputFiles = {"shared_files", "direct1_only", "direct2_only"};

    // if(writeFiles(outputFiles[0], shared_files))
    //     cout << "Success: Files have been written to shared files" << endl;
    // else    
    //     cout << "Failed: Files cannot be written to shared files" << endl;

    // if(writeFiles(outputFiles[1], direct1_only))
    //     cout << "Success: Files have been written to Directory 1" << endl;
    // else    
    //     cout << "Failed: Files cannot be written to Directory 1" << endl;
    
    // if(writeFiles(outputFiles[2], direct2_only))
    //     cout << "Success: Files have been written to Directory 2" << endl;
    // else    
    //     cout << "Failed: Files cannot be written to Directory 2" << endl;

    return 0;
}