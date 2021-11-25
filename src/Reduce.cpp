#include <fstream>
#include <iostream>
#include <bits/stdc++.h>
#include <sys/stat.h>
////////
#include <fcntl.h>
#include <string>
#include <unistd.h>
#include <vector>
#include <map>

#define DELIM ','
#define OUTPUT_SIZE 100000
//#define BUFFER_SIZE 25

using namespace std; 

vector<pair<string ,int>> split_str(string in){
    vector<pair<string ,int>> out;
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
        out.push_back(pair<string ,int>(key, value));
    }
    return out;
}

void convert_to_string(map<string, int> in, char* out){
    map<string, int>::iterator itr;
    for (itr = in.begin(); itr != in.end(); itr++) {
        sprintf(out, "%s%s:%d,", out, itr->first.c_str(), itr->second);
    }
}

void count_and_convert_to_csv(vector<pair<string ,int>> out_map, char* out_str){
    map<string, int> out;
    vector<string> keys;
    vector<int> values;
    for(int i = 0; i < out_map.size(); i++){
        keys.push_back(out_map[i].first);
        values.push_back(out_map[i].second);
    }
    for(int i = 0; i < keys.size(); i++){
        if(out.find(keys[i]) == out.end()){
            int value = values[i];
            for(int j = i; j < keys.size(); j++){
                if(keys[j] == keys[i]){
                    value += values[j];
                }
            }
            out.insert(pair<string, int>(keys[i], value));
        }
    }
    convert_to_string(out, out_str);
}

int main(int argc, char* argv[]){
    /* close the unused end of the pipe */
    close(atoi(argv[0]));

    string out;
    stringstream maps_out(out);
    //char out[OUTPUT_SIZE];
    int num_of_maps = atoi(argv[3]);
    mkfifo(argv[2], 0666);
    int fd = open(argv[2], O_RDONLY);
    for(int i = 0; i < num_of_maps; i++){
        char temp[OUTPUT_SIZE];
        read(fd, temp, OUTPUT_SIZE);
        cout << temp << endl;
        maps_out << temp;
        //sleep(1);
    }
    close(fd);
    //////////////
    cout << out << endl;
    /////////

    vector<pair<string ,int>> out_map = split_str(out);

    char output[OUTPUT_SIZE];
    count_and_convert_to_csv(out_map, output);

    /* write to the pipe */
    write(atoi(argv[1]), output, strlen(output)+1);
    /* close the write end of the pipe */
    close(atoi(argv[1]));
    return 0;
}