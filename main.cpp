#include <stdio.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <filesystem>
#include <algorithm>
#include <fstream>

using namespace std;

// 1. generate hash values for directory 1 files and place into unordered_map<size_t, filepath>direct1_hash with its filename
// 2. iterate through directory 2 and generate hash value for each file to use in direct1_hash.find()
//    if true, there is a shared file, place into shared_files vector, and remove from unordered_map
//    if false, place current directory 2 file into direct2_only vector
// 3. all remaining values of direct1_hash are direct1_only, so move them into the vector and clear map
// 4. take shared_files, direct1_only, and direct2_only vectors and write to its corresponding new txt files

bool hashDirectOneFiles(string path, unordered_map<size_t, string> &hash_files){
    if(path != ""){
        filesystem::directory_iterator dir(filesystem::current_path() / "files" / path);
        for(const auto &it : dir){
            if(it.is_regular_file()){
                ifstream file(it.path().string());
                if(file.is_open()){
                    string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                    hash<string> hashKey;
                    size_t hashVal = hashKey(data);
                    hash_files.insert({hashVal, ("files/" + path + "/" + it.path().filename().string())});
                }
                else{
                    cout << "ERROR: could not open file" << endl;
                }
            }
            else{
                cout << "Not a valid file: " << path << "/" << it.path().filename().string() << endl;
            }
        }
        return true;
    }
    return false;
}

bool compareDirect(unordered_map<size_t, string> &direct1_hash, string path2, vector<string> &shared_files, vector<string> &direct2_only){
    if(path2 != ""){
        filesystem::directory_iterator dir2(filesystem::current_path() / "files" / path2);
        for(const auto &it : dir2){
            if(it.is_regular_file()){
                ifstream file(it.path().string());
                if(file.is_open()){
                    string data2((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                    hash<string> hashKey;
                    size_t hashVal2 = hashKey(data2);

                    if(direct1_hash.find(hashVal2) != direct1_hash.end()){
                        shared_files.push_back("D1: " + direct1_hash[hashVal2] + ", D2: " + path2 + "/" + it.path().filename().string());
                        direct1_hash.erase(hashVal2);
                    }
                    else{
                        direct2_only.push_back(path2 + "/" + it.path().filename().string());
                    }
                }
                else{
                    cout << "ERROR: could not open file" << endl;
                }
            }
            else{
                cout << "Not a valid file: " << path2 << "/" << it.path().filename().string() << endl;
            }
        }
        return true;
    }
    return false;
}

bool clearHashDirect(unordered_map<size_t, string> &direct_hash, vector<string> &direct_only){
    if(!direct_hash.empty()){
        for(const auto &pair : direct_hash){
            direct_only.push_back(pair.second);
        }
        direct_hash.clear();
        return true;
    }
    return false;
}

bool writeFiles(string filename, vector<string> &files){
    if(!files.empty()){
        ofstream output(filename);
        for(auto x : files){
            output << x << "\n";
        }
        return true;
    }
    return false;
}

int main(){ 
    vector<string> paths;
    filesystem::directory_iterator directPaths(filesystem::current_path() / "files");
    for(const auto &name : directPaths){
        if(name.is_directory()){
            paths.push_back(name.path().filename().string());
        }
    }
    if(paths.empty()){
        cout << "ERROR: There is no valid Directories" << endl;
        exit(0);
    }

    unordered_map<size_t, string> direct1_hash;

    if(hashDirectOneFiles(paths[0], direct1_hash))
        cout << "Success: Hash of Directory 1" << endl;
    else   
        cout << "Failed: Hash of Directory 1" << endl;

    // 0 = SHARED_FILES, 1 = DIRECT1_ONLY, 2 = DIRECT2_ONLY
    vector<vector<string>> sortedDirect(3);

    if(compareDirect(direct1_hash, paths[1], sortedDirect[0], sortedDirect[2]))
        cout << "Success: Compared all elements in Directory 2" << endl;
    else   
        cout << "Failed: Check direct1_hash, direct2_files, or either output vectors" << endl;

    if(clearHashDirect(direct1_hash, sortedDirect[1]))
        cout << "Success: Cleared unordered_map of Directory 1" << endl;
    else    
        cout << "Failed: Unable to clear unordered_map of Directory 1" << endl;

    vector<string> outputFiles = {"shared_files.txt", "direct1_only.txt", "direct2_only.txt"};

    for(int i = 0; i < outputFiles.size(); i++){
        if(writeFiles(outputFiles[i], sortedDirect[i]))
            cout << "Success: Files have been generate for " << outputFiles[i] << endl;
        else    
            cout << "Failed: Files cannot be generated for " << outputFiles[i] << endl;
    }

    return 0;
}