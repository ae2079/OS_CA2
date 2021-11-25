#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>

#define DELIM ','
#define OUTPUT_SIZE 100000

using namespace std; 

map<string ,int> split_str(string in){
    map<string ,int> out;
    size_t start;
    size_t end = 0;
    while ((start = in.find_first_not_of(DELIM, end)) != string::npos){
        end = in.find(DELIM, start);
        string str = in.substr(start, end - start);
        size_t delim = str.find(':');
        string key = str.substr(0, delim);
        int value;
        stringstream temp(str.substr(delim+1, end-start-delim-1));
        temp >> value;
        if(out.find(key) == out.end()){
            out.insert(pair<string ,int>(key, value));
        }
        else{
            int curr_value = out.find(key)->second;
            out.find(key)->second = curr_value+value;
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
        if(itr != in.end())
            strcat(out, ",");
    }
}

int main(int argc, char* argv[]){
    /* close the unused end of the pipe */
    close(atoi(argv[0]));

    char out[OUTPUT_SIZE];
    int num_of_maps = atoi(argv[3]);
    /* make named pipe */
    mkfifo(argv[2], 0666);
    sleep(0.5);
    /* open named pipe for reading */
    int fd = open(argv[2], O_RDONLY);
    for(int i = 0; i < num_of_maps; i++){
        char temp[OUTPUT_SIZE];
        /* read from the named pipe */
        while(read(fd, temp, OUTPUT_SIZE)<=0);
        strcat(out, temp);
    }
    /* close the named pipe */
    close(fd);

    map<string ,int> out_map = split_str(out);

    char output[OUTPUT_SIZE] = "";
    convert_to_string(out_map, output);
    
    /* write to the pipe */
    write(atoi(argv[1]), output, strlen(output)+1);
    /* close the write end of the pipe */
    close(atoi(argv[1]));
    
    return 0;
}