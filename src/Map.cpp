#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/stat.h>
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
        strcat(out, itr->first.c_str());
        strcat(out, ":");
        strcat(out, to_string(itr->second).c_str());
        strcat(out, ",");
    }
}

int main(int argc, char* argv[]){
    char file_address[BUFFER_SIZE];
    /* close the unused end of the pipe */
    close(atoi(argv[1]));
    /* read from the pipe */
    read(atoi(argv[0]), file_address, BUFFER_SIZE+1);
    /* close the read end of the pipe */
    close(atoi(argv[0]));

    string data;
    ifstream in_file; 
    /* open testcase file */
    in_file.open(file_address);
    /* read from file */
    in_file >> data;
    /* close the opened file */
    in_file.close();

    vector<string> keys = split_str(data);
    map<string, int> out_map = count_and_add_to_map(keys);

    char out_str[OUTPUT_SIZE];
    convert_to_string(out_map, out_str);

    /* make named pipe */
    mkfifo(argv[2], 0666);
    /* open named pipe for writing */
    int fd = open(argv[2], O_WRONLY);
    /* wirte into the named pipe */
    write(fd, out_str, OUTPUT_SIZE);
    /* close the named pipe */
    close(fd);

    return 0;
}