//#include <sys/types.h>
//#include <stdio.h>
#include <fcntl.h>
//////////
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/stat.h>
////////
#include <string>
#include <unistd.h>
#include <vector>
#include <map>

#define DELIM ','
#define BUFFER_SIZE 25
#define OUTPUT_SIZE 100000

using namespace std; 

vector<string> split_str(string in){
    vector<string> out;
    size_t start;
    size_t end = 0;
    while ((start = in.find_first_not_of(DELIM, end)) != string::npos){
        end = in.find(DELIM, start);
        out.push_back(in.substr(start, end - start));
    }
    return out;
}

map<string, int> count_and_add_to_map(vector<string> keys){
    map<string, int> out;
    for(int i = 0; i < keys.size(); i++){
        if(out.find(keys[i]) == out.end()){
            int value = count(keys.begin(), keys.end(), keys[i]);
            out.insert(pair<string, int>(keys[i], value));
        }
    }
    return out;
}

void convert_to_string(map<string, int> in, char* out){
    map<string, int>::iterator itr;
    for (itr = in.begin(); itr != in.end(); itr++) {
        //cout << "   " << itr->first << "  :   " << itr->second << endl;
        sprintf(out, "%s%s:%d,", out, itr->first.c_str(), itr->second);
    }
}

int main(int argc, char* argv[]){
    //cout << argc << endl;
    //cout << "hello" << endl;
    //cout << argv[0] << endl;
    //cout << atoi(argv[1]) << endl;
    //cout << "hello" << endl;
    //int fd = open(argv[0], O_RDONLY);
    /* close the unused end of the pipe */
    close(atoi(argv[1]));
    char file_address[BUFFER_SIZE];
    /* read from the pipe */
    read(atoi(argv[0]), file_address, BUFFER_SIZE+1);
    /* close the read end of the pipe */
    close(atoi(argv[0]));

    ifstream in_file; 
    in_file.open(file_address);
    string data;
    in_file >> data;
    // close the opened file.
    in_file.close();

    vector<string> keys = split_str(data);
    map<string, int> out_map = count_and_add_to_map(keys);

    char out_str[OUTPUT_SIZE];
    convert_to_string(out_map, out_str);
    ////////////////////
    //cout << out_str << endl;
    //////////////
    mkfifo(argv[2], 0666);
    int fd = open(argv[2], O_WRONLY);
    write(fd, out_str, OUTPUT_SIZE);
    close(fd);
    //////////////////////
    // map<string, int>::iterator itr;
    // for (itr = out_map.begin(); itr != out_map.end(); itr++) {
    //     cout << '\t' << itr->first << " : " << itr->second << '\n';
    // }
    // cout << endl;
    // for(int i = 0; i < keys.size(); i++){
    //     cout << argv[0] << " : " << keys[i] << endl;
    // } 
    //cout << data << endl; 
 
    //exit(1);
    return 0;
}