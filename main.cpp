#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

// assume directory trees can have up to 100,000 files
// 1. get file names from directories and place into vector<string>direct1, direct2
// 2. generate hash value for each file from direct1 and place into unordered_map<size_t, filename>D1_hash
// 3. iterate through direct2 and generate hash value for each file and D1_hash.find() to see if it exists
// 4. based on the return statement determine if file is placed into shared or direct2_only file
//    if it is shared make sure to remove from unordered_map
// 5. after finishing direct2, all remaining elements in D1_hash should be direct1_only file
// 6. iterate through D1_hash and get the key of each index and place into direct1_only file

bool getFiles(string direct, vector<string> &fileNames){
    // pull file names from directory and place into vector
    // return false if directory is invalid and return true if operation is done

    return false;
}



int main(){ 
    // call necessary functions and tests for functions
    // create executable
    return 0;
}