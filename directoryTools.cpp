// C++ Libraries 
#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>
#include <cstdio>

using namespace std;

// 1. generate hash values for directory A files and place into unordered_map<size_t, filepath>directA_hash with its filename
// 2. iterate through directory B and generate hash value for each file to use in directAhash.find()
//    if true, there is a shared file, place into common vector, and remove from unordered_map
//    if false, place current directory B file into b_only vector
// 3. all remaining values of directA_hash are a_only, so move them into the vector and clear map
// 4. take common, a_only, and b_only vectors and write to its corresponding new txt files

// Checks if directory path is valid and places all directories into string vector
bool validPaths(string filepath, vector<string> &paths){ 
    filesystem::path dir(filesystem::current_path() / filepath);
    if(filesystem::exists(dir)){
        filesystem::directory_iterator directPaths(filesystem::current_path() / "files");
        for(const auto &name : directPaths){
            if(name.is_directory()){
                paths.push_back(name.path().filename().string());
            }
        }
        if(paths.size() != 2){
            cout << "ERROR: Directory requirements not met" << endl;
            return false;
        }
        cout << "SUCCESS: Retrieved all paths" << endl;
        return true;
    }
    cout << "ERROR: There is no valid directory path" << endl;
    return false;
}

// Compares only TWO Directories, based on the data within each file, 
// Creates a_only, b_only, and common
bool compareTwoDirect(string filepath){
    vector<string> paths;
    if(!validPaths(filepath, paths)){
        return false;
    }

    if(!paths.empty()){
        // Create unordered_map<size_t, string> of Directory 1 with <hash value, file path>
        unordered_map<size_t, string> directA_hash;
        if(paths[0] != ""){
            filesystem::directory_iterator dirA(filesystem::current_path() / "files" / paths[0]);
            for(const auto &it : dirA){
                if(it.is_regular_file()){
                    ifstream file(it.path().string());
                    if(file.is_open()){
                        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                        hash<string> hashKey;
                        size_t hashVal = hashKey(data);
                        directA_hash.insert({hashVal, ("files/" + paths[0] + "/" + it.path().filename().string())});
                    }
                    else{
                        cout << "ERROR: could not open file" << endl;
                    }
                }
                else{
                    cout << "Not a valid file: " << paths[0] << "/" << it.path().filename().string() << endl;
                }
            }
            cout << "SUCCESS: Hash of Directory A" << endl;
        }
        else{
            cout << "FAILED: Hash of Directory A" << endl;
            return false;
        }

        // Compare Directory 2 hash values to directA_hash, and place according variables into common or b_only
        vector<vector<string>> sortedDirect(3);
        if(paths[1] != ""){
            filesystem::directory_iterator dirB(filesystem::current_path() / "files" / paths[1]);
            for(const auto &it : dirB){
                if(it.is_regular_file()){
                    ifstream file(it.path().string());
                    if(file.is_open()){
                        string dataB((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                        hash<string> hashKey;
                        size_t hashValB = hashKey(dataB);

                        if(directA_hash.find(hashValB) != directA_hash.end()){
                            sortedDirect[0].push_back("a_file: " + directA_hash[hashValB] + ", b_file: files/" + paths[1] + "/" + it.path().filename().string());
                            directA_hash.erase(hashValB);
                        }
                        else{
                            sortedDirect[2].push_back("files/" + paths[1] + "/" + it.path().filename().string());
                        }
                    }
                    else{
                        cout << "ERROR: could not open file" << endl;
                    }
                }
                else{
                    cout << "Not a valid file: " << paths[1] << "/" << it.path().filename().string() << endl;
                }
            }
            cout << "SUCCESS: Compared all elements in Directory B" << endl;
        }
        else{
            cout << "FAILED: Check directA_hash, directB_files, or either output vectors" << endl;
            return false;
        }

        // Place remaining directA_hash into a_only
        if(!directA_hash.empty()){
            for(const auto &pair : directA_hash){
                sortedDirect[1].push_back(pair.second);
            }
            directA_hash.clear();
            cout << "SUCCESS: Cleared unordered_map of Directory A into its Vector" << endl;
        }
        else if(directA_hash.size() == 0){
            cout << "WARNING: DirectA_hash size 0" << endl;
        }
        else{
            cout << "FAILED: Unable to clear unordered_map of Directory A" << endl;
            return false;
        }

        // Write organized files into txt files
        vector<string> outputFiles = {"common.txt", "a_only.txt", "b_only.txt"};
        for(int i = 0; i < outputFiles.size() && i < sortedDirect.size() && i < 3; i++){
            if(filesystem::remove(outputFiles[i]) == false){
                cout << "FAILED: To removed " << outputFiles[i] << endl;
                return false;
            }
            sort(sortedDirect[i].begin(), sortedDirect[i].end());
            ofstream output(outputFiles[i]);
            output << outputFiles[i] << " files: \n";
            for(auto x : sortedDirect[i]){
                output << x << "\n";
            }
            cout << "SUCCESS: Files have been generate for " << outputFiles[i] << endl;
        }
        return true;
    }
    cout << "ERROR: Path Vector is empty" << endl;
    return false;
}