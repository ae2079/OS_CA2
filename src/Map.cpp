//#include <sys/types.h>
//#include <stdio.h>
//#include <fcntl.h>
//////////
#include <fstream>
#include <iostream>
////////
#include <string>
#include <unistd.h>
#include <vector>

#define DELIM ','

using namespace std; 

vector<string> split_str(string in){
    vector<string> out;
    int end = in.find(DELIM);
    while(end>0){

    }
}

int main(int argc, char* argv[]){
    //cout << argc << endl;

    //cout << argv[0] << endl;
    //cout << "hello" << endl;
    //int fd = open(argv[0], O_RDONLY);
    ifstream in_file; 
    in_file.open(argv[0]); 
    string data;
    in_file >> data; 
    //cout << data << endl; 

    // close the opened file.
    in_file.close();

    return 0;
}