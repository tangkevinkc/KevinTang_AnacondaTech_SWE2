#include <stdio.h>
#include <string>

using namespace std;

// assume directory trees can have up to 100,000 files

void readDirect(string filename, void *data){
    // read directory and place data into void pointer
}

void writeFile(string filename, void *data){
    // create common, a_only, and b_only files
    // write to files while going through directories
    // write from void *data to filename
}

void compareDirect(string file1, string file2){
    // read both directories, place into 2 void *data pointers
    // create common, a_only, and b_only files
    // compare both pointers and write to correlating files as we read the data
    // when reaching end of a file in a directory, automatically switch to new file 
}

int main(){
    // call necessary functions and tests for functions
    // create executable
    return 0;
}