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

// 1. generate hash values for directory 1 files and place into unordered_map<size_t, filepath>direct1_hash with its filename
// 2. iterate through directory 2 and generate hash value for each file to use in direct1_hash.find()
//    if true, there is a shared file, place into shared_files vector, and remove from unordered_map
//    if false, place current directory 2 file into direct2_only vector
// 3. all remaining values of direct1_hash are direct1_only, so move them into the vector and clear map
// 4. take shared_files, direct1_only, and direct2_only vectors and write to its corresponding new txt files

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

bool compareTwoDirect(string filepath){
    vector<string> paths;
    if(!validPaths(filepath, paths)){
        return false;
    }

    if(!paths.empty()){
        // Create unordered_map<size_t, string> of Directory 1 with <hash value, file path>
        unordered_map<size_t, string> direct1_hash;
        if(paths[0] != ""){
            filesystem::directory_iterator dir1(filesystem::current_path() / "files" / paths[0]);
            for(const auto &it : dir1){
                if(it.is_regular_file()){
                    ifstream file(it.path().string());
                    if(file.is_open()){
                        string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                        hash<string> hashKey;
                        size_t hashVal = hashKey(data);
                        direct1_hash.insert({hashVal, ("files/" + paths[0] + "/" + it.path().filename().string())});
                    }
                    else{
                        cout << "ERROR: could not open file" << endl;
                    }
                }
                else{
                    cout << "Not a valid file: " << paths[0] << "/" << it.path().filename().string() << endl;
                }
            }
            cout << "SUCCESS: Hash of Directory 1" << endl;
        }
        else{
            cout << "FAILED: Hash of Directory 1" << endl;
            return false;
        }

        // Compare Directory 2 hash values to direct1_hash, and place according variables into shared_files or direct2_only
        vector<vector<string>> sortedDirect(3);
        if(paths[1] != ""){
            filesystem::directory_iterator dir2(filesystem::current_path() / "files" / paths[1]);
            for(const auto &it : dir2){
                if(it.is_regular_file()){
                    ifstream file(it.path().string());
                    if(file.is_open()){
                        string data2((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
                        hash<string> hashKey;
                        size_t hashVal2 = hashKey(data2);

                        if(direct1_hash.find(hashVal2) != direct1_hash.end()){
                            sortedDirect[0].push_back("direct_1: " + direct1_hash[hashVal2] + ", direct_2: files/" + paths[1] + "/" + it.path().filename().string());
                            direct1_hash.erase(hashVal2);
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
            cout << "SUCCESS: Compared all elements in Directory 2" << endl;
        }
        else{
            cout << "FAILED: Check direct1_hash, direct2_files, or either output vectors" << endl;
            return false;
        }

        // Place remaining direct1_hash into direct1_only
        if(!direct1_hash.empty()){
            for(const auto &pair : direct1_hash){
                sortedDirect[1].push_back(pair.second);
            }
            direct1_hash.clear();
            cout << "SUCCESS: Cleared unordered_map of Directory 1 into its Vector" << endl;
        }
        else if(direct1_hash.size() == 0){
            cout << "WARNING: Direct1_hash size 0" << endl;
        }
        else{
            cout << "FAILED: Unable to clear unordered_map of Directory 1" << endl;
            return false;
        }

        // Write organized files into txt files
        vector<string> outputFiles = {"shared_files.txt", "direct1_only.txt", "direct2_only.txt"};
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

// bool hashDirectOneFiles(string path, unordered_map<size_t, string> &hash_files){
//     if(path != ""){
//         filesystem::directory_iterator dir(filesystem::current_path() / "files" / path);
//         for(const auto &it : dir){
//             if(it.is_regular_file()){
//                 ifstream file(it.path().string());
//                 if(file.is_open()){
//                     string data((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//                     hash<string> hashKey;
//                     size_t hashVal = hashKey(data);
//                     hash_files.insert({hashVal, ("files/" + path + "/" + it.path().filename().string())});
//                 }
//                 else{
//                     cout << "ERROR: could not open file" << endl;
//                 }
//             }
//             else{
//                 cout << "Not a valid file: " << path << "/" << it.path().filename().string() << endl;
//             }
//         }
//         return true;
//     }
//     return false;
// }

// bool compareDirect(unordered_map<size_t, string> &direct1_hash, string path2, vector<string> &shared_files, vector<string> &direct2_only){
//     if(path2 != ""){
//         filesystem::directory_iterator dir2(filesystem::current_path() / "files" / path2);
//         for(const auto &it : dir2){
//             if(it.is_regular_file()){
//                 ifstream file(it.path().string());
//                 if(file.is_open()){
//                     string data2((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
//                     hash<string> hashKey;
//                     size_t hashVal2 = hashKey(data2);

//                     if(direct1_hash.find(hashVal2) != direct1_hash.end()){
//                         shared_files.push_back("direct_1: " + direct1_hash[hashVal2] + ", direct_2: files/" + path2 + "/" + it.path().filename().string());
//                         direct1_hash.erase(hashVal2);
//                     }
//                     else{
//                         direct2_only.push_back("files/" + path2 + "/" + it.path().filename().string());
//                     }
//                 }
//                 else{
//                     cout << "ERROR: could not open file" << endl;
//                 }
//             }
//             else{
//                 cout << "Not a valid file: " << path2 << "/" << it.path().filename().string() << endl;
//             }
//         }
//         return true;
//     }
//     return false;
// }

// bool clearHashDirect(unordered_map<size_t, string> &direct_hash, vector<string> &direct_only){
//     if(!direct_hash.empty()){
//         for(const auto &pair : direct_hash){
//             direct_only.push_back(pair.second);
//         }
//         direct_hash.clear();
//         return true;
//     }
//     return false;
// }

// bool writeFiles(string filename, vector<string> &files){
//     if(filesystem::remove(filename) == false){
//         cout << "FAILED: To removed " << filename << endl;
//     }
//     sort(files.begin(), files.end());
//     ofstream output(filename);
//     output << filename << " files: \n";
//     for(auto x : files){
//         output << x << "\n";
//     }
//     return true;
// }